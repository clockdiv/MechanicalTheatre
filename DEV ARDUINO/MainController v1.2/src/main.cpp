/*
   Teensy 4.1

   Upload Blender Timeline:
   =======================
   send 'u' over serial to set the device into upload mode:
     the device reads 2 bytes at a time (lower byte first), e.g.:
     1 (DEC)
     00000001 00000000 (BIN)
     255 (DEC)
     11111111 00000000 (BIN)
     256 (DEC)
     00000000 00000001 (BIN)
     ...and stores it in exact the same way as binary data into a file on the SD-Card or the SPI Flash File System.
*/

#ifndef ARDUINO_ESP32_DEV
#error "ESP32 Development board needed for this project."
#endif

#include <Arduino.h>
#include <Wire.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include "UniversalTelegramBot.h"
#include "Bounce2.h"
#include "ESP32_tone.h"
#include "notes.h"

// local includes
#include "Configurations.h"
#include "StateMachine.h"
#include "i2cHandler.h"

// cross-project includes
#include "KeyframeProcess.h"
#include "pw.h"

const unsigned long messageScanInterval = 1000; // mean time between scan messages
WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);
unsigned long bot_lasttime = 0;   // last time messages' scan has been done
unsigned long wifiTimeout = 3000; // timeout for establishing WiFi connection
String chat_id = GROUP_ID;
String telegramMessage_tmp = "";

// communication between microcontrollers
i2cHandler i2chandler;

// coin slot
Bounce coinSlotSensor;
Bounce btnA, btnB;
Bounce dipswitch1, dipswitch2, dipswitch3, dipswitch4;

ESP32_tone toneBuzzer(0);

// timing
unsigned long millisOld = 0, millisCurrent; // meassuring time to get into the fps-rhythm
unsigned long millisIdle = 0;
uint16_t timesPlayed = 0;
bool testLEDstatus = true;

states state;
states stateOld;

bool repeatShow = true;
bool startFromTelegram = false;
uint16_t showCounter = 0;

// function declarations
void smRun();
void stateEnter();
void stateExit();
void __incoming_serial();
void __reset();
void __wait_for_motor_init();
void __wait_for_teensy();
void __idle();
void __play();
void __hardware_test();

void serialEvent();

void powerSuppliesOn();
void powerSuppliesOff();
void coinslotEnable();
void coinslotDisable();
void statusLEDOn();
void statusLEDOff();
void MediaControllerStart();
void MediaControllerStop();

void initWiFiAndTelegram();
void checkTelegramBot();
void handleNewTelegramMessages(int numNewMessages);
void sendTelegramMessage(String _message);

void buzzerTone(uint8_t signalID);

/* ------------------------------------ */
void setup()
{
  // Outputs
  pinMode(PIN_EXT_LED, OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_RELAIS_COINSLOT, OUTPUT);
  pinMode(PIN_RELAIS_POWERSUPPLIES, OUTPUT);
  pinMode(PIN_MEDIACONTROLLER_TRIGGER, OUTPUT);

  // Inputs
  coinSlotSensor.attach(PIN_COINSLOT_SENSOR, INPUT);
  btnA.attach(PIN_BTN_A, INPUT_PULLUP);
  btnB.attach(PIN_BTN_B, INPUT_PULLUP);
  dipswitch1.attach(PIN_DIPSWITCH_1, INPUT_PULLUP);
  dipswitch2.attach(PIN_DIPSWITCH_2, INPUT_PULLUP);
  dipswitch3.attach(PIN_DIPSWITCH_3, INPUT_PULLUP);
  dipswitch4.attach(PIN_DIPSWITCH_4, INPUT_PULLUP);

  btnA.interval(DEBOUNCE_TIME);
  btnB.interval(DEBOUNCE_TIME);
  dipswitch1.interval(DEBOUNCE_TIME);
  dipswitch1.interval(DEBOUNCE_TIME);
  dipswitch1.interval(DEBOUNCE_TIME);
  dipswitch1.interval(DEBOUNCE_TIME);
  coinSlotSensor.interval(DEBOUNCE_TIME);

  MediaControllerStop();
  powerSuppliesOff();
  coinslotDisable();
  statusLEDOff();

  if (btnA.read() == LOW)
  {
    state = __HARDWARE_TEST;
  }
  else
  {
    state = __RESET;
  }

  buzzerTone(BUZZER_POWER_ON);

  Serial.begin(115200);
  Serial.println(F("hello magdeburg!"));

  // initWiFiAndTelegram();

  // Initialize SD-Card
  if (!FileProcess::initFilesystem())
  {
    Serial.println(F("Initialization of FileSystem failed!"));
    while (true)
      ;
  }

  // Initialize i2c communication
  i2chandler.initI2C();


  stateOld = __UNDEFINED;

  millisOld = millis();
}

/* ------------------------------------ */
void loop()
{
  if (state != stateOld)
  {
    Serial.print(F("state:\t\t"));
    Serial.println(stateStrings[state]);

    stateExit();
    stateEnter();
  }
  millisCurrent = millis();

  if (Serial.available() >= 1)
  {
    serialEvent();
  }

  smRun();
}

/* ------------------------------------ */
void stateEnter()
{
  switch (state)
  {
  case __INCOMING_SERIAL:
    MediaControllerStop();
    // powerSuppliesOff();
    break;

  case __RESET:
    MediaControllerStop();
    powerSuppliesOn();
    break;

  case __WAIT_FOR_MOTOR_INIT:
    powerSuppliesOn();
    break;

  case __WAIT_FOR_TEENSY:
    powerSuppliesOn();
    break;

  case __IDLE:
    powerSuppliesOff();
    coinslotEnable();
    millisIdle = millis();
    break;

  case __PLAY:
    showCounter++;
    // telegramMessage_tmp = "playing Show #" + String(showCounter) + " (=" + String(showCounter * 2) + "€)";
    // sendTelegramMessage(telegramMessage_tmp);

    powerSuppliesOn();
    buzzerTone(BUZZER_START_SHOW);

    while (!i2chandler.requestStart()) // wait until Teensy is ready
    {
      delay(1000);
    };

    MediaControllerStart();
    break;

  case __HARDWARE_TEST:
    break;

  case __UNDEFINED:
    powerSuppliesOff();
    break;

  default:
    break;
  }
}

/* ------------------------------------ */
void stateExit()
{
  switch (stateOld)
  {
  case __INCOMING_SERIAL:
    break;

  case __RESET:
    break;

  case __WAIT_FOR_MOTOR_INIT:
    break;

  case __WAIT_FOR_TEENSY:
    break;

  case __IDLE:
    coinslotDisable();
    break;

  case __PLAY:
    break;

  case __HARDWARE_TEST:
    break;

  case __UNDEFINED:
    break;

  default:
    break;
  }
}

/* ------------------------------------ */
void smRun()
{
  stateOld = state;

  switch (state)
  {
  case __INCOMING_SERIAL:
    __incoming_serial();
    break;

  case __RESET:
    __reset();
    break;

  case __WAIT_FOR_MOTOR_INIT:
    __wait_for_motor_init();
    break;

  case __WAIT_FOR_TEENSY:
    __wait_for_teensy();
    break;

  case __IDLE:
    __idle();
    break;

  case __PLAY:
    __play();
    break;

  case __HARDWARE_TEST:
    __hardware_test();
    break;

  case __UNDEFINED:
    // checkTelegramBot();
    break;

  default:
    break;
  }
}

/* ------------------------------------ */
void serialEvent()
{
  state = __INCOMING_SERIAL;
}

/* ------------------------------------ */
void __incoming_serial()
{
  if (Serial.available() >= 1)
  {
    //char inChar = (char)Serial.read();
  }
  else
  {
    state = __IDLE;
  }
}

/* ------------------------------------ */
void __reset()
{
  //  keyframeIndex = 0;

  Serial.println(F("reseting all motors..."));

  state = __WAIT_FOR_MOTOR_INIT;
}

/* ------------------------------------ */
void __wait_for_motor_init()
{
}

/* ------------------------------------ */
void __wait_for_teensy()
{
  // block while teensy is not ready yet. always wait for your little sibling!
  while (!i2chandler.requestIdleState())
  {
    delay(1000);
  }

  state = __IDLE;
}

/* ------------------------------------ */
void __idle()
{
  coinSlotSensor.update();

  // update Telegram Messages
  // if (millis() - bot_lasttime >= messageScanInterval)
  // {
  //   Serial.println(F("checking Telegram Bot"));
  //   checkTelegramBot();
  //   bot_lasttime = millis();
  // }

  bool _play = false;

  // eventually start show
  if (coinSlotSensor.fallingEdge())
  {
    Serial.println("play show: coin sensor");
    _play = true;
  }
  else if (repeatShow && (millis() - millisIdle > 10000))
  {
    Serial.println("play show: repeatShow");
    _play = true;
  }
  else if (startFromTelegram)
  {
    Serial.println("play show: telegram message");
    _play = true;
    startFromTelegram = false;
  }

  if (_play)
  {
    state = __PLAY;
  }
}

/* ------------------------------------ */
void __play()
{
  /*
  if (millisCurrent - frameDuration > millisOld)
  {

    keyframeIndex++;

    for (int i = 0; i < UNIT_COUNT; i++)
    {
      steppers[i].moveToFramePosition(keyframeIndex);
      if (steppers[i].tooFast)
      {
        Serial.print("too fast: ");
        Serial.print(keyframeIndex);
        Serial.print(" Motor: ");
        Serial.println(steppers[i].motorName);
      }
    }

    // if animation finished...
    if (keyframeIndex == steppers[0].animationLength - 1)
    {
      buzzer_beep(1, 200);
      state = __RESET;
    }

    millisOld = millisCurrent;
  }

  for (int i = 0; i < UNIT_COUNT; i++)
  {
    steppers[i].update();
  }
  */
}

/* ------------------------------------ */
void __hardware_test()
{
  btnA.update();
  btnB.update();
  dipswitch1.update();
  dipswitch2.update();
  dipswitch3.update();
  dipswitch4.update();
  coinSlotSensor.update();

  if (btnA.fallingEdge())
    Serial.println("Button A pressed");
  else if (btnA.risingEdge())
    Serial.println("Button A released");
  
  if (btnB.fallingEdge())
  {
    Serial.println("Button B pressed");
    i2chandler.requestMotortest();
    MediaControllerStart();
  }
  else if (btnB.risingEdge())
    Serial.println("Button B released");

  if (dipswitch1.fallingEdge())
    Serial.println("DipSwitch 1 ON");
  else if (dipswitch1.risingEdge())
    Serial.println("DipSwitch 1 OFF");
  
  if (dipswitch2.fallingEdge())
    Serial.println("DipSwitch 2 ON");
  else if (dipswitch2.risingEdge())
    Serial.println("DipSwitch 2 OFF");
  
  if (dipswitch3.fallingEdge())
    Serial.println("DipSwitch 3 ON");
  else if (dipswitch3.risingEdge())
    Serial.println("DipSwitch 3 OFF");
  
  if (dipswitch4.fallingEdge())
    Serial.println("DipSwitch 4 ON");
  else if (dipswitch4.risingEdge())
    Serial.println("DipSwitch 4 OFF");

  if (millisCurrent - millisOld > 2000)
  {
    if (testLEDstatus)
    {
      powerSuppliesOn();
      coinslotEnable();
      statusLEDOn();
      buzzerTone(BUZZER_TEST);
    }
    else
    {
      powerSuppliesOff();
      coinslotDisable();
      statusLEDOff();
    }
    testLEDstatus = !testLEDstatus;
    millisOld = millisCurrent;
  }
}

/* ------------------------------------ */
void powerSuppliesOn()
{
  digitalWrite(PIN_RELAIS_POWERSUPPLIES, HIGH);
  //delay(1000);
}

/* ------------------------------------ */
void powerSuppliesOff()
{
  digitalWrite(PIN_RELAIS_POWERSUPPLIES, LOW);
  //delay(1000);
}

/* ------------------------------------ */
void MediaControllerStart()
{
  digitalWrite(PIN_MEDIACONTROLLER_TRIGGER, HIGH);
}

/* ------------------------------------ */
void MediaControllerStop()
{
  digitalWrite(PIN_MEDIACONTROLLER_TRIGGER, LOW);
}

/* ------------------------------------ */
void coinslotEnable()
{
  digitalWrite(PIN_RELAIS_COINSLOT, HIGH);
}

/* ------------------------------------ */
void coinslotDisable()
{
  digitalWrite(PIN_RELAIS_COINSLOT, LOW);
}

/* ------------------------------------ */
void statusLEDOn()
{
  digitalWrite(PIN_EXT_LED, HIGH);
}

/* ------------------------------------ */
void statusLEDOff()
{
  digitalWrite(PIN_EXT_LED, LOW);
}

/* ------------------------------------ */
void checkTelegramBot()
{
  if (!WiFi.isConnected())
  {
    initWiFiAndTelegram();
    return;
  }

  int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
  while (numNewMessages)
  {
    handleNewTelegramMessages(numNewMessages);
    numNewMessages = bot.getUpdates(bot.last_message_received + 1);
  }
}

/* ------------------------------------ */
void handleNewTelegramMessages(int numNewMessages)
{
  for (int i = 0; i < numNewMessages; i++)
  {
    chat_id = bot.messages[i].chat_id;
    String text = bot.messages[i].text;

    String from_name = bot.messages[i].from_name;
    if (from_name == "")
      from_name = "Guest";

    if (text == "/start" || text == "/play")
    {
      startFromTelegram = true;
      sendTelegramMessage("starting show...");
    }

    if (text == "/loop")
    {
      repeatShow = true;
      sendTelegramMessage("automatic show repeat on.");
    }

    if (text == "/stop")
    {
      repeatShow = false;
      sendTelegramMessage("stopping show...");
    }
  }
}

/* ------------------------------------ */
void initWiFiAndTelegram()
{
  Serial.print(F("Reconnect to WiFi"));
  unsigned long startUpTime = millis();
  WiFi.setAutoConnect(false);
  WiFi.setAutoReconnect(false);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  unsigned long beginWiFiInit = millis();
  while (WiFi.status() != WL_CONNECTED && beginWiFiInit + wifiTimeout > millis())
  {
    Serial.print(".");
    delay(500);
  }

  if (WiFi.isConnected())
  {
    configTime(0, 0, "pool.ntp.org");                    // get UTC time via NTP
    secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Add root certificate for api.telegram.org
    Serial.println("WiFi connected.");
    delay(500);
    telegramMessage_tmp = "Reconnected with IP ";
    telegramMessage_tmp += WiFi.localIP().toString();
    telegramMessage_tmp += "\nI'm working here now for ";
    telegramMessage_tmp += String(startUpTime);
    telegramMessage_tmp += "ms!";
    sendTelegramMessage(telegramMessage_tmp);
  }
  else
  {
    Serial.println(F("NOT connected."));
    repeatShow = true;
  }
}

/* ------------------------------------ */
void sendTelegramMessage(String _message)
{
  if (chat_id != "" && WiFi.isConnected())
  {
    bot.sendMessage(chat_id, _message);
    telegramMessage_tmp = "";
  }
}

/* ------------------------------------ */
void buzzerTone(uint8_t signalID)
{
  switch (signalID)
  {

  case BUZZER_TEST:
    toneBuzzer.tone(PIN_BUZZER, NOTE_A4);
    delay(200);
    toneBuzzer.tone(PIN_BUZZER, NOTE_A5);
    delay(200);
    toneBuzzer.noTone(PIN_BUZZER);
    break;

  case BUZZER_POWER_ON:
    toneBuzzer.tone(PIN_BUZZER, NOTE_C5);
    delay(200);
    toneBuzzer.tone(PIN_BUZZER, NOTE_B4);
    delay(150);
    toneBuzzer.tone(PIN_BUZZER, NOTE_E4);
    delay(400);
    toneBuzzer.tone(PIN_BUZZER, NOTE_F4);
    delay(400);
    toneBuzzer.noTone(PIN_BUZZER);
    break;
    break;
  }
}
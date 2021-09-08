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
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <AccelStepper.h>
#include "UniversalTelegramBot.h"
#include "Bounce2.h"
#include "ESP32_tone.h"
#include "notes.h"

// local includes
#include "Configurations.h"
#include "StateMachine.h"
#include "i2cHandler.h"
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
Bounce endswitchStopSign;

AccelStepper stepperStopSign;
uint16_t stepperStopsignUpPosition = 0;

ESP32_tone toneBuzzer(0);

// timing
unsigned long millisOld = 0, millisCurrent; // meassuring time to get into the fps-rhythm
unsigned long millisIdle = 0;
unsigned long teensyStateRequestInterval = 1000;
uint16_t timesPlayed = 0;

unsigned long millisOldStatusLED = 0;
unsigned long statusLEDBlinkFrequency = 1000;
bool statusLEDstate = false;

states state;
states stateOld;

bool startFromTelegram = false;
uint16_t showCounter = 0;

uint16_t i2cTestCounter = 0, i2cTestCounter2 = 0;

// function declarations
void smRun();
void stateEnter();
void stateExit();
void __incoming_serial();
void __wait_for_teensy();
void __play();
void __idle();
void __hardware_test();

void serialEvent();
int8_t requestTeensyState();

void powerSuppliesOn();
void powerSuppliesOff();

void coinslotEnable();
void coinslotDisable();

void statusLEDOn();
void statusLEDOff();
void statusLEDUpdate();

void stopsignUp();
void stopsignDown();

void MediaControllerStartStopTrigger();

void initWiFiAndTelegram();
void checkTelegramBot();
void handleNewTelegramMessages(int numNewMessages);
void sendTelegramMessage(String _message);

void buzzerTone(uint8_t signalID);

/* ------------------------------------ */
void setup()
{
  Serial.begin(115200);
  Serial.println(F("hello magdeburg!"));

  // Outputs
  pinMode(PIN_EXT_LED, OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_RELAIS_COINSLOT, OUTPUT);
  pinMode(PIN_RELAIS_POWERSUPPLIES, OUTPUT);
  pinMode(PIN_MEDIACONTROLLER_TRIGGER, OUTPUT);

  // Inputs
  coinSlotSensor.attach(PIN_COINSLOT_SENSOR, INPUT_PULLUP);
  btnA.attach(PIN_BTN_A, INPUT_PULLUP);
  btnB.attach(PIN_BTN_B, INPUT_PULLUP);
  dipswitch1.attach(PIN_DIPSWITCH_1, INPUT_PULLUP);
  dipswitch2.attach(PIN_DIPSWITCH_2, INPUT_PULLUP);
  dipswitch3.attach(PIN_DIPSWITCH_3, INPUT_PULLUP);
  dipswitch4.attach(PIN_DIPSWITCH_4, INPUT_PULLUP);
  endswitchStopSign.attach(STEPPER_13_ENDSWITCH_PIN, INPUT_PULLDOWN);

  btnA.interval(DEBOUNCE_TIME);
  btnB.interval(DEBOUNCE_TIME);
  dipswitch1.interval(DEBOUNCE_TIME);
  dipswitch1.interval(DEBOUNCE_TIME);
  dipswitch1.interval(DEBOUNCE_TIME);
  dipswitch1.interval(DEBOUNCE_TIME);
  coinSlotSensor.interval(DEBOUNCE_TIME);
  endswitchStopSign.interval(DEBOUNCE_TIME);

  stepperStopSign.setInterface(AccelStepper::DRIVER);
  stepperStopSign.setPins(STEPPER_13_PULSE_PIN, STEPPER_13_DIRECTION_PIN);
  stepperStopSign.setMinPulseWidth(50);
  stepperStopSign.setMaxSpeed(3000);
  stepperStopSign.setCurrentPosition(0);

  powerSuppliesOff();
  coinslotDisable();
  statusLEDOff();

  if (btnA.read() == LOW)
  {
    state = __HARDWARE_TEST;
  }
  else
  {
    state = __WAIT_FOR_TEENSY;
  }

  buzzerTone(BUZZER_POWER_ON);

  // initWiFiAndTelegram();

  // Initialize i2c communication
  i2chandler.initI2C();

  stateOld = __UNDEFINED;

  millisOld = millis();
}

/* ------------------------------------ */
void loop()
{
  btnA.update();
  btnB.update();
  dipswitch1.update();
  dipswitch2.update();
  dipswitch3.update();
  dipswitch4.update();
  coinSlotSensor.update();
  endswitchStopSign.update();

  millisCurrent = millis();

  if (state != stateOld)
  {
    Serial.print(F("state:\t\t"));
    Serial.println(stateStrings[state]);

    stateExit();
    stateEnter();
  }

  if (Serial.available() >= 1)
  {
    serialEvent();
  }

  statusLEDUpdate();
  smRun();
}

/* ------------------------------------ */
void stateEnter()
{
  switch (state)
  {
  case __INCOMING_SERIAL:
    // powerSuppliesOff();
    break;

  case __WAIT_FOR_TEENSY:
    powerSuppliesOn();
    statusLEDBlinkFrequency = 100;
    break;

  case __IDLE:
    stopsignUp();
    i2cTestCounter2 = 0;
    i2cTestCounter = 0;
    powerSuppliesOff();
    coinslotEnable();
    buzzerTone(BUZZER_IDLE);
    millisIdle = millis();
    break;

  case __PLAY:
    statusLEDBlinkFrequency = 1000;
    showCounter++;
    powerSuppliesOn();
    stopsignDown();
    // telegramMessage_tmp = "playing Show #" + String(showCounter) + " (=" + String(showCounter * 2) + "€)";
    // sendTelegramMessage(telegramMessage_tmp);

    buzzerTone(BUZZER_START_SHOW);

    while (true) // wait until Teensy is ready
    {
      if (i2chandler.requestStart())
        break;

      delay(1000);
    };
    Serial.println("starting to play");

    MediaControllerStartStopTrigger();
    delay(100);
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
  statusLEDBlinkFrequency = 0;
  statusLEDOff();
  switch (stateOld)
  {
  case __INCOMING_SERIAL:
    break;

  case __WAIT_FOR_TEENSY:
    break;

  case __IDLE:
    coinslotDisable();
    break;

  case __PLAY:
    MediaControllerStartStopTrigger();
    buzzerTone(BUZZER_STOP_SHOW);
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
int8_t requestTeensyState()
{
  int8_t teensyState = i2chandler.requestState();
  switch (teensyState)
  {
  case 1:
    Serial.println(F("Teensy is resetting all motors"));
    break;

  case 2:
    Serial.println(F("Teensy is waiting for it's motors to init"));
    break;

  case 3:
    Serial.println(F("Teensy is idle"));
    break;

  case 4:
    Serial.println(F("Teensy is playing the show"));
    break;

  case 5:
    Serial.println(F("Teensy is testing the hardware"));
    break;

  case 6:
    Serial.println(F("Teensy is in Error State :("));
    break;

  default:
    Serial.print(F("Teensy is in another state: "));
    Serial.println(teensyState);
    break;
  }

  return teensyState;
}

/* ------------------------------------ */
void __wait_for_teensy()
{
  if (millisCurrent - millisOld >= teensyStateRequestInterval)
  {
    millisOld = millisCurrent;
    int8_t teensyState = requestTeensyState();
    if (teensyState == 3) // Teensy is idle
    {
      state = __IDLE;
    }
    else if (teensyState == 4)
    {
      i2chandler.requestStop();
    }
  }
}

/* ------------------------------------ */
void __play()
{
  if (millisCurrent - millisOld >= teensyStateRequestInterval)
  {
    millisOld = millisCurrent;
    int8_t teensyState = requestTeensyState();
    if (teensyState == 1 || teensyState == 2 || teensyState == 3) // Teensy is idle
    {
      state = __WAIT_FOR_TEENSY;
    }
  }

  if (btnB.fallingEdge())
  {
    i2chandler.requestStop();
  }
}

/* ------------------------------------ */
void __idle()
{
  // update Telegram Messages
  // if (millis() - bot_lasttime >= messageScanInterval)
  // {
  //   Serial.println(F("checking Telegram Bot"));
  //   checkTelegramBot();
  //   bot_lasttime = millis();
  // }

  // test to see if i2c works fine. result: seems to work really fine.
  /*
  if (i2cTestCounter < 1000)
  {
    i2cTestCounter++;
    if (i2chandler.requestTest())
    {
      i2cTestCounter2++;
    }
    if (i2cTestCounter % 500 == 0)
    {
      Serial.print("\ntests sent: ");
      Serial.println(i2cTestCounter);
      Serial.print("correct answers: ");
      Serial.println(i2cTestCounter2);
    }
    delay(1);
  }
  */

  bool _play = false;
  bool _repeatShow = !dipswitch1.read();

  if (coinSlotSensor.fallingEdge() || btnA.fallingEdge())
  {
    _play = true;
  }
  else if (_repeatShow && (millis() - millisIdle > 5000))
  {
    _play = true;
  }
  else if (startFromTelegram)
  {
    _play = true;
    startFromTelegram = false;
  }

  if (_play)
  {
    state = __PLAY;
  }
}

/* ------------------------------------ */
void __hardware_test()
{
  if (btnA.fallingEdge())
  {
    Serial.println("Button A pressed");
    MediaControllerStartStopTrigger();
  }
  else if (btnA.risingEdge())
    Serial.println("Button A released");

  if (btnB.fallingEdge())
  {
    Serial.println("Button B pressed");
    //i2chandler.requestMotortest();
  }
  else if (btnB.risingEdge())
    Serial.println("Button B released");

  if (coinSlotSensor.fallingEdge())
  {
    Serial.println("CoinSlotSensor pressed");
  }
  else if (coinSlotSensor.risingEdge())
    Serial.println("CoinSlotSensor released");

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
    if (statusLEDstate)
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
    statusLEDstate = !statusLEDstate;
    millisOld = millisCurrent;
  }
}

/* ------------------------------------ */
void powerSuppliesOn()
{
  digitalWrite(PIN_RELAIS_POWERSUPPLIES, HIGH);
  delay(1000);
}

/* ------------------------------------ */
void powerSuppliesOff()
{
  if (dipswitch2.read() == LOW) // on-position
  {
    return;
  }

  digitalWrite(PIN_RELAIS_POWERSUPPLIES, LOW);
  delay(1000);
}

/* ------------------------------------ */
void MediaControllerStartStopTrigger()
{
  Serial.println("media controller start");
  digitalWrite(PIN_MEDIACONTROLLER_TRIGGER, HIGH);
  delay(20);
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
  statusLEDstate = HIGH;
  digitalWrite(PIN_EXT_LED, HIGH);
}

/* ------------------------------------ */
void statusLEDOff()
{
  statusLEDstate = LOW;
  digitalWrite(PIN_EXT_LED, LOW);
}

/* ------------------------------------ */
void statusLEDUpdate()
{
  if (statusLEDBlinkFrequency > 0)
  {
    if (millisCurrent - millisOldStatusLED >= statusLEDBlinkFrequency)
    {
      statusLEDstate ? statusLEDOff() : statusLEDOn();
      millisOldStatusLED = millisCurrent;
    }
  }
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

    if (text == "/stop")
    {
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
  if (dipswitch4.read()) // off-position
    return;

  switch (signalID)
  {

  case BUZZER_TEST:
    toneBuzzer.tone(PIN_BUZZER, NOTE_A4);
    delay(80);
    toneBuzzer.noTone(PIN_BUZZER);
    delay(40);
    toneBuzzer.tone(PIN_BUZZER, NOTE_A5);
    delay(200);
    toneBuzzer.noTone(PIN_BUZZER);
    break;

  case BUZZER_POWER_ON:
    toneBuzzer.tone(PIN_BUZZER, NOTE_C5);
    delay(80);
    toneBuzzer.noTone(PIN_BUZZER);
    delay(80);
    toneBuzzer.tone(PIN_BUZZER, NOTE_C5);
    delay(80);
    toneBuzzer.noTone(PIN_BUZZER);
    delay(400);

    toneBuzzer.tone(PIN_BUZZER, NOTE_E5);
    delay(80);
    toneBuzzer.noTone(PIN_BUZZER);
    delay(80);
    toneBuzzer.tone(PIN_BUZZER, NOTE_E5);
    delay(80);
    toneBuzzer.noTone(PIN_BUZZER);
    break;

  case BUZZER_START_SHOW:
    toneBuzzer.tone(PIN_BUZZER, NOTE_E6);
    delay(80);
    toneBuzzer.noTone(PIN_BUZZER);
    delay(80);
    toneBuzzer.tone(PIN_BUZZER, NOTE_F6);
    delay(80);
    toneBuzzer.noTone(PIN_BUZZER);
    break;

  case BUZZER_STOP_SHOW:
    toneBuzzer.tone(PIN_BUZZER, NOTE_F6);
    delay(80);
    toneBuzzer.noTone(PIN_BUZZER);
    delay(80);
    toneBuzzer.tone(PIN_BUZZER, NOTE_C5);
    delay(80);
    toneBuzzer.noTone(PIN_BUZZER);
    break;

  case BUZZER_IDLE:
    toneBuzzer.tone(PIN_BUZZER, NOTE_E6);
    delay(60);
    toneBuzzer.noTone(PIN_BUZZER);
    delay(60);
    toneBuzzer.tone(PIN_BUZZER, NOTE_D6);
    delay(60);
    toneBuzzer.noTone(PIN_BUZZER);
    delay(60);
    toneBuzzer.tone(PIN_BUZZER, NOTE_C6);
    delay(60);
    toneBuzzer.noTone(PIN_BUZZER);
    delay(60);
    toneBuzzer.tone(PIN_BUZZER, NOTE_F6);
    delay(60);
    toneBuzzer.noTone(PIN_BUZZER);
    delay(60);
    toneBuzzer.tone(PIN_BUZZER, NOTE_E6);
    delay(60);
    toneBuzzer.noTone(PIN_BUZZER);
    break;
  }
}

/* ------------------------------------ */
void stopsignUp()
{
  Serial.println("Hoch das Schild!");
  stepperStopSign.setSpeed(-100);
  endswitchStopSign.update();
  Serial.print(endswitchStopSign.read());
  while (!endswitchStopSign.read())
  {
    Serial.print(endswitchStopSign.read());
    stepperStopSign.runSpeed();
    endswitchStopSign.update();
  }

  stepperStopsignUpPosition = stepperStopSign.currentPosition();
}

/* ------------------------------------ */
void stopsignDown()
{
  Serial.println("Runter das Schild!");
  stepperStopSign.setAcceleration(1000);
  stepperStopSign.moveTo(0);
  while (stepperStopSign.distanceToGo() > 0)
  {
    stepperStopSign.run();
  }
}
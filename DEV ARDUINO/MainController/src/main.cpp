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

// local includes
#include "Configurations.h"
#include "CommonFunctions.h"
#include "StateMachine.h"
#include "i2cHandler.h"

// cross-project includes
#include "MotorUnit.h"
#include "KeyframeProcess.h"
//#include "ShowController.h"
#include "pw.h"

const unsigned long messageScanInterval = 1000; // mean time between scan messages
WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);
unsigned long bot_lasttime = 0;   // last time messages' scan has been done
unsigned long wifiTimeout = 3000; // timeout for establishing WiFi connection
String chat_id = GROUP_ID;
String telegramMessage_tmp = "";

// motor units
MotorUnit steppers[UNIT_COUNT];

// communication between microcontrollers
i2cHandler i2chandler;

// coin slot
Bounce coinSlotSensor;

// timing
unsigned long millisOld = 0, millisCurrent; // meassuring time to get into the fps-rhythm
unsigned long millisIdle = 0;
unsigned long frameDuration = 1000 / MotorUnit::fps; // duration of a frame in milliseconds
uint16_t keyframeIndex = 0;                 // current position of the timeline, used for playback
uint16_t timesPlayed = 0;

states state;
states stateOld;

bool repeatShow = false;
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

void serialEvent();
void powerSuppliesOn();
void powerSuppliesOff();
void LEDWallStart();
void LEDWallStop();
void coinslotEnable();
void coinslotDisable();

void initWiFiAndTelegram();
void checkTelegramBot();
void handleNewTelegramMessages(int numNewMessages);
void sendTelegramMessage(String _message);

/* ------------------------------------ */
void setup()
{
  pinMode(PIN_EXT_LED, OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_LEDWALL_TRIGGER, OUTPUT);

  pinMode(PIN_RELAIS_COINSLOT, OUTPUT);
  pinMode(PIN_RELAIS_POWERSUPPLIES, OUTPUT);

  LEDWallStop();
  powerSuppliesOff();
  coinslotDisable();

  buzzer_beep();

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

  // Connect Coin-Sensor
  coinSlotSensor.attach(PIN_COINSLOT_SENSOR, INPUT);
  coinSlotSensor.interval(25);

  // Initialize Motors
  for (int i = 0; i < UNIT_COUNT; i++)
  {
    steppers[i].initDriver(motornames[i],
                           steppersPinConfig[i][0],
                           steppersPinConfig[i][1],
                           steppersPinConfig[i][2],
                           steppersPinConfig[i][3],
                           steppersInitConfig[i][0],
                           steppersInitConfig[i][1]);
  }

  state = __RESET;
  stateOld = __UNDEFINED;

  // read all files and store curves in MotorUnits (stepper[])
  if (!FileProcess::read_all_files(filenames, steppers, UNIT_COUNT))
  {
    Serial.println(F("error while reading files during startup"));
    state = __UNDEFINED;
  }

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
    LEDWallStop();
    // powerSuppliesOff();
    break;
  case __RESET:
    LEDWallStop();
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
    buzzer_beep(4, 200);

    for (int i = 0; i < UNIT_COUNT; i++)
    {
      steppers[i].setPlay();
    }

    while (!i2chandler.requestStart())
    {
      delay(1000);
    };
    LEDWallStart();
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
    char inChar = (char)Serial.read();

    if (inChar == 'u')
    {
      buzzer_beep(1, 100);
      digitalWrite(PIN_EXT_LED, HIGH);

      int8_t receiveError = FileProcess::receive_keyframes(filenames, UNIT_COUNT);

      if (receiveError == -1)
      {
        // Error: Didn't receive as many bytes as expected
        buzzer_beep(1, 1000);
      }
      else if (receiveError == -2)
      {
        // Error: error while writing file
        buzzer_beep(2, 1000);
      }
      else if (receiveError == -3)
      {
        // Error: number of curves not equal to number of timelines
        buzzer_beep(3, 1000);
      }
      else if (receiveError == 1)
      {
        // No Error:
        digitalWrite(PIN_EXT_LED, LOW);
        buzzer_beep(2, 100);
        delay(200);

        // read all files after they are received and reset the animation
        FileProcess::read_all_files(filenames, steppers, UNIT_COUNT);
        keyframeIndex = 0;
        state = __RESET;
        return;
      }
      // Return with error:
      digitalWrite(PIN_EXT_LED, LOW);
      state = __RESET;
      delay(200);
    }
    else if (inChar == 'r')
    {
      FileProcess::read_all_files(filenames, steppers, UNIT_COUNT);
      state = __RESET;
    }
    else if (inChar == 'p')
    {
      state = __PLAY;
    }
  }
  else
  {
    state = __IDLE;
  }
}

/* ------------------------------------ */
void __reset()
{
  keyframeIndex = 0;

  Serial.println(F("reseting all motors..."));
  for (int i = 0; i < UNIT_COUNT; i++)
  {
    steppers[i].setReset();
  }

  state = __WAIT_FOR_MOTOR_INIT;
}

/* ------------------------------------ */
void __wait_for_motor_init()
{
  for (int i = 0; i < UNIT_COUNT; i++)
  {
    steppers[i].update();
  }

  bool allResetted = true;

  for (int i = 0; i < UNIT_COUNT; i++)
  {
    if (!steppers[i].isIdle())
    {
      allResetted = false;
    }
  }

  if (allResetted)
  { // if all motor units have resetted their position...
    state = __WAIT_FOR_TEENSY;
  }
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
}

/* ------------------------------------ */
void powerSuppliesOn()
{
  digitalWrite(PIN_RELAIS_POWERSUPPLIES, LOW);
  //delay(1000);
}

/* ------------------------------------ */
void powerSuppliesOff()
{
  digitalWrite(PIN_RELAIS_POWERSUPPLIES, HIGH);
  //delay(1000);
}

/* ------------------------------------ */
void LEDWallStart()
{
  digitalWrite(PIN_LEDWALL_TRIGGER, HIGH);
}

/* ------------------------------------ */
void LEDWallStop()
{
  digitalWrite(PIN_LEDWALL_TRIGGER, LOW);
}

/* ------------------------------------ */
void coinslotEnable() {
  digitalWrite(PIN_RELAIS_COINSLOT, LOW);
}

/* ------------------------------------ */
void coinslotDisable(){
  digitalWrite(PIN_RELAIS_COINSLOT, HIGH);
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

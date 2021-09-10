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

#include <Arduino.h>
#include "Configurations.h"
#include "StateMachine.h"
#include "i2cHandler.h"
#include "MotorUnit.h"
#include "FileProcess.h"

uint16_t errorCode = 0;

// motor units
MotorUnit steppers[UNIT_COUNT];

FileProcess fileProcess;
// communication
i2cHandler i2chandler;

// timing
unsigned long millisOld = 0, millisCurrent;          // meassuring time to get into the fps-rhythm
unsigned long frameDuration = 1000 / MotorUnit::fps; // duration of a frame in milliseconds
uint16_t keyframeIndex = 0;                          // current position of the timeline, used for playback

unsigned long millisOldStatusLED = 0;
unsigned long statusLEDBlinkFrequency = 0;
bool statusLEDstate = false;
// bool motorDebugSet = false;
// Bounce playRequest;

states state;
states stateOld;

std::map<states, String> stateStringsMap =
    {{__INCOMING_SERIAL, "INCOMING SERIAL"},
     {__RESET, "RESET"},
     {__WAIT_FOR_MOTOR_INIT, "WAIT FOR MOTOR INIT"},
     {__IDLE, "IDLE"},
     {__PLAY, "PLAY"},
     {__HARDWARE_TEST, "HARDWARE TEST"},
     {__ERROR, "ERROR"},
     {__UNDEFINED, "UNDEFINED"}};

elapsedMillis sinceDebugMessage, enterNextStateAfterMillis;

// function declarations
void smRun();
void stateEnter();
void stateExit();
String stateToString(states _state);
void __incoming_serial();
void __reset();
void __wait_for_motor_init();
void __idle();
void __play();
void __hardware_test();
void __error();

void statusLEDOn();
void statusLEDOff();
void statusLEDUpdate();

/* ------------------------------------ */
void setup()
{
  pinMode(PIN_EXT_LED, OUTPUT);

  // Initialize i2c communication
  i2cHandler::initI2C(&state);

  // Initialize Motors
  for (int i = 0; i < UNIT_COUNT; i++)
  {
    steppers[i].initDriver(motornames[i],
                           steppersPinConfig[i][0],
                           steppersPinConfig[i][1],
                           steppersPinConfig[i][2],
                           steppersPinConfig[i][3],
                           steppersInitConfig[i][0],
                           steppersInitConfig[i][1],
                           steppersInvertedEndswitch[i]);
  }

  // Set Motor Reset- and Emergency-Stop-Dependencies
  for (int i = 0; i < UNIT_COUNT; i++)
  {
    if (steppersResetDependencies[i] >= 0)
    {
      steppers[i].setResetDependency(&steppers[steppersResetDependencies[i]]);
    }
    
    if(steppersEmergencyStopDependencies[i] >= 0)
    {
      steppers[i].setEmergencyStopDependency(&steppers[steppersEmergencyStopDependencies[i]]);
    }
  }

  state = __RESET;
  stateOld = __UNDEFINED;

  // Initialize SD-Card
  if (!SD.begin(BUILTIN_SDCARD))
  {
    Serial.println(F("initialization of SD Card failed!"));
    errorCode = ERR_SD_FAILED;
    state = __ERROR;
    return;
  }

  // read all files and store curves in MotorUnits (stepper[])
  if (!fileProcess.read_all_files(filenames, steppers, UNIT_COUNT))
  {
    Serial.println(F("error while reading files during startup"));
    errorCode = ERR_READING_FILES;
    state = __ERROR;
    return;
  }

  millisOld = millis();
}

/* ------------------------------------ */
void loop()
{
  millisCurrent = millis();

  // if (sinceDebugMessage > 1000)
  // {
  //   sinceDebugMessage = 0;
  //   Serial.print(F("current State: "));
  //   Serial.print(state);
  //   Serial.println(stateStrings[state]);
  // }

  if (state != stateOld)
  {
    Serial.print(F("state:\t\t"));
    Serial.println(stateToString(state));

    stateExit();
    stateEnter();
  }

  statusLEDUpdate();
  smRun();

  if (i2chandler.stateChange)
  {
    state = i2chandler.stateNext;
    Serial.println(F("change state after i2c request"));
    i2chandler.stateChange = false;
  }
}

/* ------------------------------------ */
void stateEnter()
{
  enterNextStateAfterMillis = 0;

  switch (state)
  {
  case __RESET:
    // motorDebugSet = false;
    statusLEDBlinkFrequency = 100;
    break;

  case __WAIT_FOR_MOTOR_INIT:
    statusLEDBlinkFrequency = 100;
    break;

  case __IDLE:
    break;

  case __PLAY:
    keyframeIndex = 0;
    statusLEDBlinkFrequency = 1000;
    for (int i = 0; i < UNIT_COUNT; i++)
    {
      steppers[i].setPlay();
    }
    break;

  case __HARDWARE_TEST:
    for (int i = 0; i < UNIT_COUNT; i++)
    {
      steppers[i].setTestDrive();
    }
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

  case __IDLE:
    __idle();
    break;

  case __PLAY:
    __play();
    break;

  case __HARDWARE_TEST:
    __hardware_test();
    break;

  case __ERROR:
    __error();
    break;

  case __UNDEFINED:
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
    Serial.println("incoming serial");

    char inChar = (char)Serial.read();
    if (inChar == 'u')
    {
      statusLEDOn();
      fileProcess.deleteFiles(filenames, UNIT_COUNT);

      int8_t receiveError = fileProcess.receive_keyframes(filenames, UNIT_COUNT);
      if (receiveError == -1)
      {
        // did not receive as many bytes as expected
      }
      else if (receiveError == -2)
      {
        // error while writing file to sd-card
      }
      statusLEDOff();
      delay(1000);
      for (int i = 0; i < 3; i++)
      {
        statusLEDOn();
        delay(50);
        statusLEDOff();
        delay(250);
      }

      // read all files after they are received and reset the animation
      fileProcess.read_all_files(filenames, steppers, UNIT_COUNT);
      delay(100);
      state = __RESET;
    }
    else if (inChar == 'r')
    {
      fileProcess.read_all_files(filenames, steppers, UNIT_COUNT);
      state = __RESET;
    }
    else if (inChar == 'p')
    {
      for (int i = 0; i < UNIT_COUNT; i++)
      {
        steppers[i].setPlay();
      }
      state = __PLAY;
    }
  }
  else
  {
    Serial.print("idle after incoming serial");
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

  /* --------------------------------- */
  /* debug block begin */
  // if (enterNextStateAfterMillis >= 5000 && motorDebugSet == false)
  // {
  //   Serial.println("(WAIT_FOR_MOTOR_INIT) entering next state (->IDLE) after debug-timeout");
  //   for (int i = 0; i < UNIT_COUNT; i++)
  //   {
  //       steppers[i].setEndswitchPressed();
  //   }
  //   motorDebugSet = true;
  // }
  /* debug block end */
  /* --------------------------------- */

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
    state = __IDLE;
  }
}

/* ------------------------------------ */
void __idle()
{
  // for (int i = 0; i < UNIT_COUNT; i++)
  // {
  //   steppers[i].update();
  // }
}

/* ------------------------------------ */
void __play()
{
  // if (enterNextStateAfterMillis >= 10000)
  // {
  //   Serial.println("10s vorbei");
  //   state = __RESET;
  // }

  if (millisCurrent - frameDuration >= millisOld)
  {
    keyframeIndex++;

    if (keyframeIndex % 25 == 0)
    {
      Serial.print(keyframeIndex);
      Serial.print("\t");
    }

    for (int i = 0; i < UNIT_COUNT; i++)
    {
      steppers[i].moveToFramePosition(keyframeIndex);
      // if(steppers[i].tooFast) {
      //   Serial.print("too fast: ");
      //   Serial.print(keyframeIndex);
      //   Serial.print(" Motor: ");
      //   Serial.println(steppers[i].motorName);
      // }
    }

    if (keyframeIndex == steppers[0].animationLength - 1)
    {
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
void __hardware_test()
{
  for (int i = 0; i < UNIT_COUNT; i++)
  {
    steppers[i].update();
  }

  if (millisCurrent - millisOld > 2000)
  {
    if (statusLEDstate)
    {
      statusLEDOn();
    }
    else
    {
      statusLEDOff();
    }
    statusLEDstate = !statusLEDstate;
    millisOld = millisCurrent;
  }
}

/* ------------------------------------ */
void __error()
{
  if (errorCode <= 200)
  {
    errorCode = ERR_UNDEFINED;
  }

  uint8_t blinkCount = errorCode - 200;

  for (int i = 0; i < blinkCount; i++)
  {
    statusLEDOn();
    delay(50);
    statusLEDOff();
    delay(100);
  }
  delay(2000);
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

String stateToString(states _state)
{
  if (stateStringsMap.find(_state) != stateStringsMap.end())
  {
    return stateStringsMap[_state];
  }
  else
  {
    return "state does not have a name";
  }
}
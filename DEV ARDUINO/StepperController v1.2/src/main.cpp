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

#ifndef ARDUINO_TEENSY41
#error "teensy 4.1 needed for this project."
#endif

#include <Arduino.h>
#include "i2c_driver.h"
#include "i2c_driver_wire.h"

// local includes
#include "Configurations12.h"
#include "StateMachine.h"
#include "i2cHandler.h"

// cross-project includes
#include "MotorUnit.h"
#include "KeyframeProcess.h"

uint16_t errorCode = 0;

// motor units
MotorUnit steppers[UNIT_COUNT];

// communication
i2cHandler i2chandler;

// timing
long millisOld = 0, millisCurrent;          // meassuring time to get into the fps-rhythm
long frameDuration = 1000 / MotorUnit::fps; // duration of a frame in milliseconds
uint16_t keyframeIndex = 0;                 // current position of the timeline, used for playback

unsigned long millisOldStatusLED = 0;
unsigned long statusLEDBlinkFrequency = 0;
bool statusLEDstate = false;

states state;
states stateOld;

// function declarations
void smRun();
void stateEnter();
void stateExit();
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
  delay(2000);
  pinMode(PIN_EXT_LED, OUTPUT);

  // Initialize i2c communication
  i2chandler.initI2C(&state);

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

  // Set Motor Reset-Dependencies
  for (int i = 0; i < UNIT_COUNT; i++)
  {
    if (steppersResetDependencies[i] >= 0)
    {
      steppers[i].setResetDependency(&steppers[steppersResetDependencies[i]]);
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
  if (!FileProcess::read_all_files(filenames, steppers, UNIT_COUNT))
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

  if (state != stateOld)
  {
    Serial.print(F("state:\t\t"));
    Serial.println(stateStrings[state]);

    stateExit();
    stateEnter();
  }

  statusLEDUpdate();
  smRun();
}

/* ------------------------------------ */
void stateEnter()
{
  switch (state)
  {
  case __RESET:
    statusLEDBlinkFrequency = 100;
    break;

  case __WAIT_FOR_MOTOR_INIT:
    statusLEDBlinkFrequency = 100;
    break;

  case __PLAY:
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
      FileProcess::deleteFiles(filenames, UNIT_COUNT);

      int8_t receiveError = FileProcess::receive_keyframes(filenames, UNIT_COUNT);
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
      FileProcess::read_all_files(filenames, steppers, UNIT_COUNT);
      keyframeIndex = 0;
      state = __RESET;
    }
    else if (inChar == 'r')
    {
      FileProcess::read_all_files(filenames, steppers, UNIT_COUNT);
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
  if (millisCurrent - frameDuration >= millisOld)
  {

    keyframeIndex++;

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
      //buzzer_beep(1, 200);

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
    delay(100);
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

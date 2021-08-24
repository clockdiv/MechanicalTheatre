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
#include "Configurations10.h"
#include "CommonFunctions.h"
#include "StateMachine.h"
#include "i2cHandler.h"

// cross-project includes
#include "MotorUnit.h"
#include "KeyframeProcess.h"




bool repeatShow = true;

// motor units
MotorUnit steppers[UNIT_COUNT];

// communication
i2cHandler i2chandler;

// timing
long millisOld = 0, millisCurrent;          // meassuring time to get into the fps-rhythm
long frameDuration = 1000 / MotorUnit::fps; // duration of a frame in milliseconds
uint16_t keyframeIndex = 0;             // current position of the timeline, used for playback
uint16_t timesPlayed = 0;

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



/* ------------------------------------ */
void setup() {
  pinMode(PIN_EXT_LED, OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);

  buzzer_beep();

  Serial.begin(115200);
  delay(2000);
  Serial.println(F("hello magdeburg!"));

  // Initialize SD-Card
  if (!SD.begin(BUILTIN_SDCARD)) {
    Serial.println(F("initialization of SD Card failed!"));
    while(true);
  }

  // Initialize i2c communication
  i2chandler.initI2C(&state);
  

  // Initialize Motors
  for (int i = 0; i < UNIT_COUNT; i++) {
    steppers[i].initDriver(motornames[i], 
                          steppersPinConfig[i][0], 
                          steppersPinConfig[i][1], 
                          steppersPinConfig[i][2], 
                          steppersPinConfig[i][3],
                          steppersInitConfig[i][0],
                          steppersInitConfig[i][1]);
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


  // read all files and store curves in MotorUnits (stepper[])
  if (!FileProcess::read_all_files(filenames, steppers, UNIT_COUNT)) {
    Serial.println(F("error while reading files during startup"));
    buzzer_beep(1, 2000);
    state = __IDLE;
  }
    

  millisOld = millis();
}


/* ------------------------------------ */
void loop() {
  if (state != stateOld) {
    Serial.print(F("state:\t\t"));
    Serial.println(stateStrings[state]);

    stateExit();
    stateEnter();
  }
  millisCurrent = millis();

  smRun();
}


/* ------------------------------------ */
void stateEnter() {
  switch(state) {
    case __PLAY:
        for (int i = 0; i < UNIT_COUNT; i++) {
          steppers[i].setPlay();
        }
    break;
    default:
    break;
  }
}


/* ------------------------------------ */
void stateExit() {
  switch (stateOld) {
    default:
    break;
  }
}


/* ------------------------------------ */
void smRun() {
  stateOld = state; 
  
  switch (state) {
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
    
    case __UNDEFINED:
      break;

    default:
      break;
  }
}


/* ------------------------------------ */
void serialEvent() {
  state = __INCOMING_SERIAL;
}


/* ------------------------------------ */
void __incoming_serial() {
  if (Serial.available() >= 1) {
    Serial.println("incoming serial");

    char inChar = (char)Serial.read();
    if (inChar == 'u') {
      buzzer_beep(1, 100);

      digitalWrite(PIN_EXT_LED, HIGH);

      int8_t receiveError = FileProcess::receive_keyframes(filenames, UNIT_COUNT);
      if (receiveError == -1) {
        // did not receive as many bytes as expected
      } else if (receiveError == -2) {
        // error while writing file to sd-card
      }

      digitalWrite(PIN_EXT_LED, LOW);
      buzzer_beep(2, 100);
      delay(200);

      // read all files after they are received and reset the animation
      FileProcess::read_all_files(filenames, steppers, UNIT_COUNT);
      keyframeIndex = 0;
      state = __RESET;
    }
    else if (inChar == 'r') {
      FileProcess::read_all_files(filenames, steppers, UNIT_COUNT);
      state = __RESET;
    }
    else if (inChar == 'p') {
       for (int i = 0; i < UNIT_COUNT; i++) {
        steppers[i].setPlay();
       }
      state = __PLAY;
    }
  }   
  else {
    Serial.print("idle after incoming serial");
    state = __IDLE;
  }
}


/* ------------------------------------ */
void __reset() {
  keyframeIndex = 0;

  Serial.println(F("reseting all motors..."));
  for (int i = 0; i < UNIT_COUNT; i++) {
    steppers[i].setReset();
  }

  state = __WAIT_FOR_MOTOR_INIT;
}


/* ------------------------------------ */
void __wait_for_motor_init() {
  for (int i = 0; i < UNIT_COUNT; i++) {
    steppers[i].update();
  }

  bool allResetted = true;

  for (int i = 0; i < UNIT_COUNT; i++) {
    if(!steppers[i].isIdle()) {
      allResetted = false;
    }
  }

  if (allResetted) {  // if all motor units have resetted their position...
    state = __IDLE;
  }

}


/* ------------------------------------ */
void __idle() {
  for (int i = 0; i < UNIT_COUNT; i++) {
    steppers[i].update();
  }
}


/* ------------------------------------ */
void __play() {

  if (millisCurrent - frameDuration > millisOld) {  

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


    if (keyframeIndex == steppers[0].animationLength - 1) {
      buzzer_beep(1, 200);

      state = __RESET;
    }


    millisOld = millisCurrent;
  }

  for (int i = 0; i < UNIT_COUNT; i++) {
    steppers[i].update();
  }
}

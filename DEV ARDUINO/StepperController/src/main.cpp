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
#include "i2c_driver.h"
#include "i2c_driver_wire.h"

// local includes
#include "Configurations10.h"
#include "CommonFunctions.h"
#include "StateMachine.h"

// cross-project includes
#include "Communication.h"
#include "MotorUnit.h"
#include "KeyframeProcess.h"



#ifndef ARDUINO_TEENSY41
#error "teensy 4.1 needed for this project."
#endif

bool repeatShow = true;

// motor units
MotorUnit steppers[UNIT_COUNT];

// timing
long millisOld = 0, millisCurrent;          // meassuring time to get into the fps-rhythm
long frameDuration = 1000 / MotorUnit::fps; // duration of a frame in milliseconds
uint16_t keyframeIndex = 0;             // current position of the timeline, used for playback
uint16_t timesPlayed = 0;

states state;
states stateOld;

// function declarations
void smRun();
void __incoming_serial();
void __reset();
void __wait_for_motor_init();
void __idle();
void __play();

uint16_t plotTemp_pos, plotTemp_deltaPos, plotTemp_motorSpeed;


// i2c Communication functions
void respondToRequest() {
  Serial.print("incoming request, current state: ");
  Serial.println(stateStrings[state]);
  if(state == __IDLE) {
    Serial.println("sending okay to esp32");
    Wire.write(1);
  } else {
    Wire.write(0);
  }
}

void receiveEvent(int byteCount) {
  while(Wire.available()) {
    char c = Wire.read();
    Serial.println(c);
    if (c == 1 && state == __IDLE) {
        for (int i = 0; i < UNIT_COUNT; i++) {
          steppers[i].setPlay();
        }
        buzzer_beep(4, 200);
        Serial.println("playyyyyyy!!!");
        state = __PLAY;
    }
    else {
        buzzer_beep(7, 200);
    }
  }
}

void initPeripheral() {
  Wire.begin(TEENSY_I2C_ADDR);
  Wire.onRequest(respondToRequest);
  Wire.onReceive(receiveEvent);
}



/* ------------------------------------ */
void setup() {
  pinMode(PIN_EXT_LED, OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);
  buzzer_beep();

  Serial.begin(115200);
  Serial.println(F("hello magdeburg!"));

  // Initialize SD-Card
  if (!SD.begin(BUILTIN_SDCARD)) {
    Serial.println(F("initialization of SD Card failed!"));
    while(true);
  }

  // Set i2c communication events  
  // Communication::initPeripheral();
  initPeripheral();
  
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

  state = __RESET;
  stateOld = __UNDEFINED;


  // read all files and store curves in MotorUnits (stepper[])
  if (!FileProcess::read_all_files(filenames, steppers, UNIT_COUNT)) {
    Serial.println(F("error while reading files during startup"));
    buzzer_beep(1, 2000);
    state = __IDLE;
  }
    
  // p.Begin();
  // p.AddTimeGraph("Motor Schwaene tauchen", 250, "Frame", keyframeIndex, "Pos", plotTemp_pos, "Delta", plotTemp_deltaPos, "Speed", plotTemp_motorSpeed);

  millisOld = millis();
}


/* ------------------------------------ */
void loop() {
  if (state != stateOld) {
    Serial.print(F("state:\t\t"));
    Serial.println(stateStrings[state]);
  }
  millisCurrent = millis();

  smRun();
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

    for (int i = 0; i < UNIT_COUNT; i++) {
      steppers[i].moveToFramePosition(keyframeIndex);
      if(steppers[i].tooFast) {
        Serial.print("too fast: ");
        Serial.print(keyframeIndex);
        Serial.print(" Motor: ");
        Serial.println(steppers[i].motorName);
      }
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

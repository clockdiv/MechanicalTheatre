/*
   Teensy 4.1

   Current Features:
   =================
   send 'u' over serial to set the device into upload mode:
     the device reads 2 bytes at a time (lower byte first), e.g.:
     1 (DEC)
     00000001 00000000 (BIN)
     255 (DEC)
     11111111 00000000 (BIN)
     256 (DEC)
     00000000 00000001 (BIN)
     ...and stores it in exact the same way as binary data into a file (dumpFilename) on the SPI Flash File System.

   send 'r' over serial to read this file and send its content as 16-Bit Integers back to the Serial Monitor.

   Display Library from here, version 1.3.0
   https://github.com/mathertel/LiquidCrystal_PCF8574
*/



#include <Arduino.h>

// local includes
#include "Configurations4.h"
#include "CommonFunctions.h"
#include "StateMachine.h"

// cross-project includes
#include "Communication.h"
#include "MotorUnit.h"
#include "KeyframeProcess.h"


// motor units
MotorUnit steppers[UNIT_COUNT];

// timing
long millisOld = 0, millisCurrent;          // meassuring time to get into the fps-rhythm
long frameDuration = 1000 / MotorUnit::fps; // duration of a frame in milliseconds
uint16_t keyframeIndex = 0;             // current position of the timeline, used for playback


states state;
states state_old;
// function declarations
void smRun();
void __incoming_serial();
void __reset();
void __post_reset();
void __idle();
void __play();



/* ------------------------------------ */
void setup() {
  pinMode(PIN_EXT_LED, OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);
  buzzer_beep();

  Serial.begin(115200);
  while(!Serial) {}
  Serial.println(F("hello magdeburg!"));

  // Initialize SD-Card
  if (!SD.begin(BUILTIN_SDCARD)) {
    Serial.println(F("initialization of SD Card failed!"));
    while(true);
  }

  // Set i2c communication events
  //Communication::beginCommunication();
  
  Communication::beginCommunication();
  
  // FileProcess::listFiles();

  // Initialize Motors
  for (int i = 0; i < UNIT_COUNT; i++) {
    steppers[i].initDriver(motornames[i], steppersConfig[i][0], steppersConfig[i][1], steppersConfig[i][2], steppersConfig[i][3]);
  }

  // read all files and store curves in MotorUnits (stepper[])
  if (!FileProcess::read_all_files(filenames, steppers, UNIT_COUNT)) {
    Serial.println(F("error while reading files during startup"));
    state = __IDLE;
  } else {
    state = __RESET;
  }

  millisOld = millis();
}

/* ------------------------------------ */
void loop() {
  if (state != state_old) {
    Serial.print(F("state: "));
    Serial.println(stateStrings[state]);
  }
  millisCurrent = millis();

  smRun();
}


void smRun() {
  state_old = state; 
  
  switch (state) {
    case __INCOMING_SERIAL:
      __incoming_serial();
      break;
            
    case __RESET:
      __reset();
      break;
      
    case __POST_RESET:
      __post_reset();
      break;
      
    case __IDLE:
      __idle();
      break;
      
    case __PLAY:
      __play();
      break;
      
    default:
      break;
  }
}


void serialEvent() {
  state = __INCOMING_SERIAL;
}


void __incoming_serial() {
  if (Serial.available() >= 1) {
    Serial.println("incoming serial");

    char inChar = (char)Serial.read();
    if (inChar == 'u') {
      buzzer_beep(1, 100);

      //lcd.print(F("receive f. serial..."));
      digitalWrite(PIN_EXT_LED, HIGH);

      int8_t receiveError = FileProcess::receive_keyframes();
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
      //lcd.print(F("read from file..."));
      FileProcess::read_all_files(filenames, steppers, UNIT_COUNT);
      keyframeIndex = 0;
      //lcd.setCursor(0, 1);
      //lcd.print(stepper[0].animationLength);
      //lcd.print(F(" keyframes."));
    }
    else if (inChar == 'p') {
      //init_display();
      //lcd.print("play");
      state = __PLAY;
    }
  } 
  
  else {
    //lcd.print("idle");
    Serial.print("idle after incoming serial");
    state = __IDLE;
  }
}


void __reset() {
  uint8_t resettedCounter = 0;
  for (int i = 0; i < UNIT_COUNT; i++) {
    steppers[i].runToHomePosition();
    if (steppers[i].endswitchPressed == HIGH) {
      resettedCounter++;
    }
  }
  if (resettedCounter == UNIT_COUNT) {  // if all motor units have resetted their position...
    state = __POST_RESET;
    //buzzer_beep(2, 500);
  }
}


void __post_reset() {
  uint8_t resettedCounter = 0;
  for (int i = 0; i < UNIT_COUNT; i++) {
    if (steppers[i].postReset()) {
      resettedCounter++;
    }
  }
  if (resettedCounter == UNIT_COUNT) {
    state = __IDLE;
    //buzzer_beep(2, 500);
  }
}


void __idle() {
  Serial.println();
  Serial.println(F("___idle mode - checking end switches:___"));
  for (int i = 0; i < UNIT_COUNT; i++) {
    steppers[i].checkEndswitch();
  }
  //state = __PLAY;

  delay(3000);
}


void __play() {
  MotorUnit::tooFast = false;
  if (millisOld + frameDuration < millisCurrent) {
    for (int i = 0; i < UNIT_COUNT; i++) {
      steppers[i].moveToFramePosition(keyframeIndex);
    }

    digitalWrite(PIN_EXT_LED, MotorUnit::tooFast);

    keyframeIndex++;

    // repeat if end of timeline
    if (keyframeIndex == steppers[0].animationLength - 1) {
      buzzer_beep(1, 200);
      //timesPlayed++;
      //lcd.setCursor(15, 3);
      //lcd.print(timesPlayed);
      keyframeIndex = 0;
      //Serial.print("round: ");
      //Serial.println(timesPlayed);
      //while(true);
    }

    millisOld = millisCurrent;
  }

  for (int i = 0; i < UNIT_COUNT; i++) {
    if (!steppers[i].update()) {  // false if end-switch was pressed
      //lcd.setCursor(0,3);
      //lcd.print(MotorUnit::temp_switchPressedCounter);
    }
  }
}

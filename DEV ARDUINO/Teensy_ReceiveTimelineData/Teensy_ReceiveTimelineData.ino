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

#include <LiquidCrystal_PCF8574.h>
#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include "MotorUnit.h"



// external hardware
LiquidCrystal_PCF8574 lcd(0x27);        // set the LCD address to 0x27
const uint8_t pinLed = 13;
const uint8_t pinBuzzer = 23;

#define UNIT_COUNT 2
MotorUnit stepper[UNIT_COUNT];
String filenames[UNIT_COUNT] = {"CURVE0.DAT", "CURVE1.DAT"};
String motornames[UNIT_COUNT] = {"X-Axis", "Y-Axis"};

// Stepper-Motor Pins
const uint8_t pinsStepper[UNIT_COUNT][4] = {
  {33, 34, 35, 1},     /* End-Switch; Direction; Pulse; DirectionInvert */
  {36, 37, 38, 0}
};


DMAMEM char keyframeValuesBin[MAX_FRAMES * 2]; // the two-byte pairs of keyframes. assigned by receive_keyframes()
uint16_t keyframeIndex = 0;             // current position of the timeline, used for playback
uint16_t packageSize = 0;               // size of incoming data package
uint16_t curveCount = 0;                 // the number of curves/timelines to receive (each stepper one curve)

String dumpFilename = "/curve";
String fileExt = ".dat";

long millisOld = 0, millisCurrent;      // meassuring time to get into the fps-rhythm
long frameDuration = 1000 / MotorUnit::fps;        // duration of a frame in milliseconds
uint16_t timesPlayed = 0;               // counts many times the sequence was repeated

enum states { // State-Machine
  __INCOMING_SERIAL,
  __INIT_RESET,
  __POST_RESET,
  __IDLE,
  __RESET,
  __PLAY
} state;

/* ------------------------------------ */
/* Initializes the Display either full  */
/* or clears it only                    */
/* ------------------------------------ */
void init_display(bool full = false) {
  if (full) {
    lcd.begin(20, 4); // initialize the lcd
    lcd.setBacklight(255);
    lcd.home();
    lcd.clear();
    lcd.print("Hello World -");
    lcd.setCursor(0, 1);
    lcd.print("Hello Magdeburg!");
  }
  else {
    lcd.home();
    lcd.clear();
    lcd.setCursor(0, 0);
  }
}

/* ------------------------------------ */
/* blinks the LED n times               */
/* ------------------------------------ */
void led_blink(uint8_t _i = 3) {
  for (int i = 0; i < _i; i++) {
    digitalWrite(pinLed, HIGH);
    delay(200);
    digitalWrite(pinLed, LOW);
    delay(200);
  }
}

/* ------------------------------------ */
/* beep the BUZZER n times               */
/* ------------------------------------ */
void buzzer_beep(uint8_t _i = 3, uint16_t duration = 50) {
  for (int i = 0; i < _i; i++) {
    digitalWrite(pinBuzzer, HIGH);
    delay(duration);
    digitalWrite(pinBuzzer, LOW);
    delay(duration);
  }
}

/* ------------------------------------ */
/* lists all files in root directory    */
/* (we don't need sub-directories here) */
/* ------------------------------------ */
void listFiles() {
  File root = SD.open("/");
  while (true) {
    File entry = root.openNextFile();
    if (!entry) break; // no more files
    Serial.println(entry.name());
    entry.close();
  }
}

/* ------------------------------------ */
/* reads keyframes as high/low Byte pairs */
/* from Serial and stores them into a   */
/* char array.                          */
/* ------------------------------------ */
void receive_keyframes() {
  init_display();
  lcd.setCursor(0, 0);
  lcd.print("receiving data...");
  digitalWrite(pinLed, HIGH);


  // the first two bytes determine the number of _frames_ to receive
  // (number of _bytes_ to receive = number of _frames_ * 2)
  // (each frame is a unsigned 16-bit integer)
  char buf[2];
  Serial.readBytes(buf, 2);
  packageSize = ((buf[1] << 8) + buf[0]) * 2;


  // the next two bytes determine the number of curves/timelines to receive
  Serial.readBytes(buf, 2);
  curveCount =  ((buf[1] << 8) + buf[0]);


  // receive each curve and store it as a separate file
  for (int i = 0; i < curveCount; i++) {
    lcd.setCursor(0, 1);
    lcd.print("receiving curve #");
    lcd.setCursor(17, 1);
    lcd.print(i);

    // receive data according to the number of frames
    uint32_t index = 0;
    while (index < packageSize) {
      if (Serial.available()) {
        char ch = (char)Serial.read();
        keyframeValuesBin[index] = ch;
        index++;
      }
    }

    if (index != packageSize) {
      // Error. Didn't receive as many bytes as expected
      buzzer_beep(5, 250);
      lcd.setCursor(0, 1);
      lcd.print("ERROR               ");
      lcd.setCursor(0, 2);
      lcd.print("wrong packagesize!  ");
    } else {
      String filename = dumpFilename + String(i) + fileExt;
      lcd.setCursor(0, 2);
      lcd.print(filename);
      write_keyframes_to_file(filename);
    }
  }

  digitalWrite(pinLed, LOW);
  /*
    lcd.setCursor(6, 2);
    lcd.print("Bytes received");
    lcd.setCursor(0, 3);
    lcd.print(uint8_t(keyframeValuesBin[index - 2]));
    lcd.setCursor(3, 3);
    lcd.print(uint8_t(keyframeValuesBin[index - 1]));
    lcd.setCursor(6, 3);
    lcd.print("(last Bytes)");
  */

}

/* ------------------------------------ */
/* Writes the 2-byte keyframe pairs to  */
/* a binary file                        */
/* ------------------------------------ */
void write_keyframes_to_file(String dumpFilename) {
  char filename[dumpFilename.length() + 1];
  dumpFilename.toCharArray(filename, sizeof(filename));
  File file = SD.open(filename, FILE_WRITE | O_TRUNC);

  if (!file) {
    Serial.println(F("failed to open file for writing"));
    return;
  }
  for (uint16_t i = 0; i < packageSize; i++) {
    if (!file.write(keyframeValuesBin[i])) {
      Serial.println(F("error while writing keyframeValues to file"));
    }
  }
  file.close();
  lcd.setCursor(0, 0);
  lcd.print("> written to file < ");
}

/* ------------------------------------ */
/* Reads the 2-byte keyframe pairs from */
/* the binary file, turns them into     */
/* uint16_t values, stores them in an   */
/* array inside a MotorUnit object      */
/* ------------------------------------ */
bool read_keyframes_from_file(String dumpFilename, uint8_t motorIndex) {
  char filename[dumpFilename.length() + 1];
  dumpFilename.toCharArray(filename, sizeof(filename));
  File file = SD.open(filename);

  if (!file) {
    Serial.println(F("failed to open file for reading"));
    stepper[motorIndex].animationLength = 0;
    return false;
  }
  uint16_t index = 0;
  while (file.available()) {
    char byteLow = file.read();
    char byteHigh = file.read();
    uint16_t value = (byteHigh << 8) + byteLow;
    //Serial.print(index);
    //Serial.print(": ");
    //Serial.println(value);
    stepper[motorIndex].setKeyframeValue(index, value);
    index++;
  }
  stepper[motorIndex].animationLength = index;
  file.close();
  //Serial.println("Starting Animation");
  //Serial.println(stepper[motorIndex].animationLength);
  keyframeIndex = 0;  // restart sequence
  return true;
}


bool read_all_files() {
  bool allFilesRead = true;

  for (int i = 0; i < UNIT_COUNT; i++) {
    if (read_keyframes_from_file(filenames[i], i)) {
      Serial.println("read file: " + filenames[i]);
    } else {
      allFilesRead = false;
      break;
    }
  }

  if (allFilesRead) {
    Serial.println("all files read");
    return true;
  }
  else {
    Serial.println("error in reading files");
    return false;
  }
}

/* ------------------------------------ */
void setup() {
  pinMode(pinLed, OUTPUT);
  pinMode(pinBuzzer, OUTPUT);
  buzzer_beep();

  Serial.begin(115200);
  init_display(true);

  if (!SD.begin(BUILTIN_SDCARD)) {
    Serial.println("initialization of SD Card failed!");
    return;
  }

  listFiles();

  for (int i = 0; i < UNIT_COUNT; i++) {
    stepper[i].initDriver(motornames[i], pinsStepper[i][0], pinsStepper[i][1], pinsStepper[i][2], pinsStepper[i][3]);
  }

  read_all_files();

  state = __INIT_RESET;

  millisOld = millis();
}




/* ------------------------------------ */
void loop() {
  millisCurrent = millis();
  if (state == __INCOMING_SERIAL) {
    if (Serial.available() >= 1) {
      Serial.println("incoming serial");

      char inChar = (char)Serial.read();
      if (inChar == 'u') {
        buzzer_beep(1, 100);
        init_display();
        lcd.print(F("receive f. serial..."));
        receive_keyframes();
        delay(200);
        read_all_files();
        buzzer_beep(2, 100);
      }
      else if (inChar == 'r') {
        init_display();
        lcd.print(F("read from file..."));
        read_all_files();
        lcd.setCursor(0, 1);
        lcd.print(stepper[0].animationLength);
        lcd.print(F(" keyframes."));
      }
      else if (inChar == 'p') {
        init_display();
        lcd.print("play");
        state = __PLAY;
      }
    } else {
      lcd.setCursor(0,0);
      lcd.print("idle");
      Serial.print("idle after incoming serial");
      state = __IDLE;
    }
  }
  else if (state == __INIT_RESET) {
    Serial.println("Init Reset");

    for (int i = 0; i < UNIT_COUNT; i++) {
      stepper[i].resetPosition();
    }
    state = __RESET;
  }
  else if (state == __RESET) {
    uint8_t resettedCounter = 0;
    for (int i = 0; i < UNIT_COUNT; i++) {
      stepper[i].updateReset();
      if (stepper[i].endswitchPressed == LOW) {
        resettedCounter++;
      }
    }
    if (resettedCounter == UNIT_COUNT) {
      state = __POST_RESET;
      buzzer_beep(2, 500);
    }
  }
  else if (state == __POST_RESET) {
    uint8_t resettedCounter = 0;
    for (int i = 0; i < UNIT_COUNT; i++) {
      if(stepper[i].postReset()) {
        resettedCounter++;
      }
    }
    if (resettedCounter == UNIT_COUNT) {
      state = __IDLE;
      buzzer_beep(2, 500);
    }
    
  }
  else if (state == __IDLE) {
    delay(1000);
    state = __PLAY;
  }
  else if (state == __PLAY) {
    MotorUnit::tooFast = false;
    if (millisOld + frameDuration < millisCurrent) {
      for (int i = 0; i < UNIT_COUNT; i++) {
        stepper[i].moveToFramePosition(keyframeIndex);
      }

      digitalWrite(pinLed, MotorUnit::tooFast);

      keyframeIndex++;

      // repeat if end of timeline
      if (keyframeIndex == stepper[0].animationLength - 1) {
        buzzer_beep(1, 200);
        timesPlayed++;
        lcd.setCursor(15, 3);
        lcd.print(timesPlayed);
        keyframeIndex = 0;
        Serial.print("round: ");
        Serial.println(timesPlayed);
        //while(true);
      }

      millisOld = millisCurrent;
    }

    for (int i = 0; i < UNIT_COUNT; i++) {
      if(!stepper[i].update()) {
        lcd.setCursor(0,3);
        lcd.print(MotorUnit::temp_switchPressedCounter);
      }
    }
  }
}

void serialEvent() {
  state = __INCOMING_SERIAL;
}

#include "KeyframeProcess.h"


namespace FileProcess {

#if defined( ARDUINO_TEENSY41 )
  DMAMEM static char keyframeValuesBin[MAX_FRAMES * 2]; // the two-byte pairs of keyframes. assigned by receive_keyframes()
#elif defined( ARDUINO_ESP32_DEV )
  static char keyframeValuesBin[MAX_FRAMES * 2]; // the two-byte pairs of keyframes. assigned by receive_keyframes()
#endif

static uint16_t packageSize = 0;               // size of incoming data package
static uint16_t curveCount = 0;                 // the number of curves/timelines to receive (each stepper one curve)

static String dumpFilename = "/curve";
static String fileExt = ".dat";

bool initFilesystem() {
  #if defined( ARDUINO_TEENSY41 )
    return SD.begin(BUILTIN_SDCARD);
  #elif defined( ARDUINO_ESP32_DEV )
    return SPIFFS.begin(true);
  #endif
}

/* ------------------------------------ */
/* reads keyframes as high/low Byte pairs */
/* from Serial and stores them into a   */
/* char array.                          */
/* return values:                       */
/*  1 - received all                    */
/* -1 - did not receive as many bytes as expected */
/* -2 - error while writing file        */
/* 1 - good                             */
/* ------------------------------------ */
int8_t receive_keyframes() {

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
    //    lcd.print("receiving curve #");
    //    lcd.print(i);

    // receive data according to the number of frames
    uint32_t index = 0;
    while (index < packageSize) {
      if (Serial.available()) {
        char ch = (char)Serial.read();
        keyframeValuesBin[index] = ch;
        index++;
      }
    }

    if (index == packageSize) {
      String filename = dumpFilename + String(i) + fileExt;
      if(!write_keyframes_to_file(filename)) {
        // Error while writing file
        return -2;
      }
    } else {
      // Error. Didn't receive as many bytes as expected
      return -1;
    }
  }

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

  return 1;
}


/* ------------------------------------ */
/* lists all files in root directory    */
/* (we don't need sub-directories here) */
/* ------------------------------------ */
void listFiles() {
  #if defined(ARDUINO_TEENSY41)
    File root = SD.open("/");
  #elif defined(ARDUINO_ESP32_DEV)
    File root = SPIFFS.open("/");
  #endif

  while (true) {
    File entry = root.openNextFile();
    if (!entry) break; // no more files
    Serial.println(entry.name());
    entry.close();
  }
}


/* ------------------------------------ */
/* Writes the 2-byte keyframe pairs to  */
/* a binary file                        */
/* ------------------------------------ */
bool write_keyframes_to_file(String _filename) {
  char filename[_filename.length() + 1];
  _filename.toCharArray(filename, sizeof(filename));

  #if defined(ARDUINO_TEENSY41)
    File file = SD.open(filename, FILE_WRITE | O_TRUNC);
  #elif defined(ARDUINO_ESP32_DEV)
    File file = SPIFFS.open(_filename, FILE_WRITE);
  #endif

  if (!file) {
    //   Serial.println(F("failed to open file for writing"));
    return false;
  }
  for (uint16_t i = 0; i < packageSize; i++) {
    if (!file.write(keyframeValuesBin[i])) {
      //    Serial.println(F("error while writing keyframeValues to file"));
      return false;
    }
  }
  file.close();
  return true;
  //  lcd.setCursor(0, 0);
  //  lcd.print("> written to file < ");
}



/* ------------------------------------ */
/* Reads the 2-byte keyframe pairs from */
/* the binary file, turns them into     */
/* uint16_t values, stores them in an   */
/* array inside a MotorUnit object      */
/* ------------------------------------ */
bool read_keyframes_from_file(String _filename, MotorUnit &stepper, uint8_t motorIndex) {
  char filename[_filename.length() + 1];
  _filename.toCharArray(filename, sizeof(filename));;

  #if defined(ARDUINO_TEENSY41)
    File file = SD.open(filename);
  #elif defined(ARDUINO_ESP32_DEV)
    File file = SPIFFS.open(_filename);
  #endif


  if (!file) {
    //Serial.println(F("read_keyframes_from_file: failed to open file for reading"));
    stepper.animationLength = 0;
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
    stepper.setKeyframeValue(index, value);
    index++;
  }
  stepper.animationLength = index;
  file.close();
  //Serial.println("Starting Animation");
  //Serial.println(stepper[motorIndex].animationLength);
  Serial.print(F("read file: "));
  Serial.println(_filename);
  return true;
}



bool read_all_files(String filenames[], MotorUnit steppers[], uint8_t count) {
  for (int i = 0; i < count; i++) {
    if (!read_keyframes_from_file(filenames[i], steppers[i], i)) {
      Serial.println("error while reading file: " + filenames[i]);
      return false;
    }
  }
  return true;
}

}

#ifndef FileProcess_h
#define FileProcess_h

#if defined(ARDUINO_TEENSY41)
#include <SD.h>
#include <SPI.h>
#elif defined( ARDUINO_ESP32_DEV )
#include "SPIFFS.h"
#endif


#include "MotorUnit.h"

#define MAX_FRAMES 4000     // maximum number of frames, used to initialize the keyframeValues-array

namespace FileProcess {

/* ------------------------------------ */
/* inits file system on Teensy (SD-Card)*/
/* or ESP (SPIFFS)                      */
/* ------------------------------------ */
bool initFilesystem();

/* ------------------------------------ */
/* reads keyframes as high/low Byte pairs */
/* from Serial and stores them into a   */
/* char array.                          */
/* ------------------------------------ */
int8_t receive_keyframes();

/* ------------------------------------ */
/* lists all files in root directory    */
/* (we don't need sub-directories here) */
/* ------------------------------------ */
void listFiles();

/* ------------------------------------ */
/* Writes the 2-byte keyframe pairs to  */
/* a binary file                        */
/* ------------------------------------ */
bool write_keyframes_to_file(String dumpFilename);

/* ------------------------------------ */
/* Reads the 2-byte keyframe pairs from */
/* the binary file, turns them into     */
/* uint16_t values, stores them in an   */
/* array inside a MotorUnit object      */
/* ------------------------------------ */
bool read_keyframes_from_file(String dumpFilename, MotorUnit &stepper, uint8_t motorIndex);

bool read_all_files(String filenames[], MotorUnit steppers[], uint8_t count);

};
#endif

#ifndef FileProcess_h
#define FileProcess_h

#include <SD.h>
#include <SPI.h>

#include "MotorUnit.h"

#define MAX_FRAMES 7500     // maximum number of frames, used to initialize the keyframeValues-array

namespace FileProcess {

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
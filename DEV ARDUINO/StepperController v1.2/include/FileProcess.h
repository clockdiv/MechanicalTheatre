#ifndef FILEPROCESS_HS
#define FILEPROCESS_HS

#include <SD.h>
#include <SPI.h>
#include "MotorUnit.h"
#include "Configurations.h"

class FileProcess
{
private:
public:
    DMAMEM static char keyframeValuesBin[MAX_FRAMES * 2]; // the two-byte pairs of keyframes. assigned by receive_keyframes()
    static uint16_t packageSize; // size of incoming data package
    static uint16_t curveCount ;  // the number of curves/timelines to receive (each stepper one curve)

    FileProcess(){};
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
    int8_t receive_keyframes(const String filenames[UNIT_COUNT], uint8_t count);

    /* ------------------------------------ */
    /* lists all files in root directory    */
    /* (we don't need sub-directories here) */
    /* ------------------------------------ */
    void listFiles();
    void deleteFiles(const String filenames[UNIT_COUNT], uint8_t count);
    void deleteFile(String filename);
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

    bool read_all_files(const String filenames[UNIT_COUNT], MotorUnit steppers[UNIT_COUNT], uint8_t count);
};

#endif

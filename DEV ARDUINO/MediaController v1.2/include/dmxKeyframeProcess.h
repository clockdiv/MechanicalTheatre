#ifndef DMXKEYFRAMEPROCESS_H
#define DMXKEYFRAMEPROCESS_H

#include <SD.h>
#include <SPI.h>
#include "configurations.h"

class DMXKeyframeProcess
{
public:
    static uint16_t frameCount;   // size of incoming data package
    static uint16_t channelCount; // the number of curves/timelines to receive (each stepper one curve)
    static uint16_t dmxChannels[512];
    static File dmxFile;
    EXTMEM static uint8_t dmxData[MAX_FRAMES * 512];

    DMXKeyframeProcess();
    int8_t receive_keyframes(String _filename);
    int8_t openDMXFile(String _filename);
    bool readHeader();
    int8_t loadFile(String _filename);
    int8_t getDMXData(uint16_t channel, uint16_t _keyframe);

    void closeFile();
};

#endif

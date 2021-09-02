#ifndef DMXKEYFRAMEPROCESS_H
#define DMXKEYFRAMEPROCESS_H

#include <SD.h>
#include <SPI.h>

class DMXKeyframeProcess
{
public:
    static uint16_t frameCount;   // size of incoming data package
    static uint16_t channelCount; // the number of curves/timelines to receive (each stepper one curve)
    static uint16_t dmxChannels[512];
    static File dmxFile;
    static bool eof;

    int8_t receive_keyframes(String _filename);
    int16_t playDMXFile();
    bool loadFile(String _filename);
    bool initHeader();
    void closeFile();
};

#endif

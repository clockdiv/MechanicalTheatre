#include "dmxKeyframeProcess.h"

uint16_t DMXKeyframeProcess::frameCount = 0;   // size of incoming data package
uint16_t DMXKeyframeProcess::channelCount = 0; // the number of curves/timelines to receive (each stepper one curve)
uint16_t DMXKeyframeProcess::dmxChannels[] = {0};
char DMXKeyframeProcess::dmxValues[512] = {0};
File DMXKeyframeProcess::dmxFile;
bool DMXKeyframeProcess::eof = false;

int8_t DMXKeyframeProcess::receive_keyframes(String _filename)
{
    // Open file to write into
    char filename[_filename.length() + 1];
    _filename.toCharArray(filename, sizeof(filename));

    if (SD.exists(filename))
    {
      Serial.print("deleting ");
      Serial.println(filename);
      SD.remove(filename);
    }

    dmxFile = SD.open(filename, FILE_WRITE | O_TRUNC);
    if (!dmxFile)
    {
        Serial.println(F("failed to open file for writing"));
        return -1;
    }

    // HEADER BEGIN
    // ------------
    // the first two bytes determine the number of _frames_ to receive
    char buf[2];
    Serial.readBytes(buf, 2);
    frameCount = ((buf[1] << 8) + buf[0]);
    if (!dmxFile.write(buf[0]))
        return -1;
    if (!dmxFile.write(buf[1]))
        return -1;
    Serial.print("Package Size: ");
    Serial.println(frameCount);

    // the next two bytes determine the number of curves/timelines to receive
    Serial.readBytes(buf, 2);
    channelCount = ((buf[1] << 8) + buf[0]);
    if (!dmxFile.write(buf[0]))
        return -1;
    if (!dmxFile.write(buf[1]))
        return -1;
    Serial.print("Channel Count: ");
    Serial.println(channelCount);

    // next is a list of the channels that are used
    Serial.print("DMX-Channels used: ");
    uint16_t receivedChannelNumbers = 0;
    while (receivedChannelNumbers < channelCount)
    {
        Serial.readBytes(buf, 2);
        uint16_t channelNumber = ((buf[1] << 8) + buf[0]);
        if (!dmxFile.write(buf[0]))
            return -1;
        if (!dmxFile.write(buf[1]))
            return -1;
        Serial.print(channelNumber);
        Serial.print(" ");
        //dmxChannels[receivedChannelNumbers] = channelNumber; // so all channelnumber > 0 will be taken
        receivedChannelNumbers++;
    }
    Serial.println();
    // HEADER END
    // ----------

    // DATA BEGIN
    // ----------
    // receive all values for each frame:
    uint16_t dataIndex = 0;
    Serial.print("Avaiting packages: ");
    Serial.println(channelCount * frameCount);
    while (dataIndex < channelCount * frameCount)
    {
        if (Serial.available())
        {
            byte ch = (byte)Serial.read();
            if (!dmxFile.write(ch))
                return -1;
            Serial.print(ch);
            Serial.print(", ");
            dataIndex++;
        }
    }
    // DATA END
    // --------
    dmxFile.close();

    return 0;
}

bool DMXKeyframeProcess::loadFile(String _filename)
{
    // Open file to read from
    char filename[_filename.length() + 1];
    _filename.toCharArray(filename, sizeof(filename));

    dmxFile = SD.open(filename);
    if (!dmxFile || dmxFile.isDirectory())
    {
        Serial.println(F("failed to open file for reading."));
        return -1;
    }

    initHeader();
    return 1;
}

bool DMXKeyframeProcess::initHeader()
{
    // HEADER START
    char byteLow = dmxFile.read();
    char byteHigh = dmxFile.read();
    frameCount = (byteHigh << 8) + byteLow;
    Serial.print("framecount: ");
    Serial.println(frameCount);

    byteLow = dmxFile.read();
    byteHigh = dmxFile.read();
    channelCount = (byteHigh << 8) + byteLow;
    Serial.print("channelCount: ");
    Serial.println(channelCount);

    Serial.print("Channels used: ");
    for (int i = 0; i < channelCount; i++)
    {
        byteLow = dmxFile.read();
        byteHigh = dmxFile.read();
        dmxChannels[i] = (byteHigh << 8) + byteLow;
        Serial.print(dmxChannels[i]);
        Serial.print(", ");
    }
    Serial.println();
    // HEADER END

    eof = false;
    return 1;
}

int16_t DMXKeyframeProcess::playDMXFile()
{
    if (dmxFile.available())
    {
        dmxFile.readBytes(dmxValues, channelCount);
        //int16_t value = int16_t(dmxFile.read());
        return 0;
    }
    else
    {
        Serial.println(F("end of file"));
        eof = true;
        dmxFile.close();
        return -1;
    }
}

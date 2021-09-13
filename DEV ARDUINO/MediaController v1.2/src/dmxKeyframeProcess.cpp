#include "dmxKeyframeProcess.h"

uint16_t DMXKeyframeProcess::frameCount = 0;   // size of incoming data package
uint16_t DMXKeyframeProcess::channelCount = 0; // the number of curves/timelines to receive (each stepper one curve)
uint16_t DMXKeyframeProcess::dmxChannels[] = {0};
//char DMXKeyframeProcess::dmxValues[512] = {0};
File DMXKeyframeProcess::dmxFile;
EXTMEM uint8_t DMXKeyframeProcess::dmxData[MAX_FRAMES * 512] = { 0 };

/* ------------------------------ */
DMXKeyframeProcess::DMXKeyframeProcess()
{
    // Init Data in EXTMEM to zero
    for(int i = 0; i < MAX_FRAMES * 512; i++)
    {
        dmxData[i] = 0;
    }
}

/* ------------------------------ */
// Receives the data from serial in following format. Data is a long list containing
// the values of all channels in one frame, following the next frame
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
        return ERR_OPEN_FILE_FOR_WRITING;
    }

    // HEADER BEGIN
    // ------------
    // the first two bytes determine the number of _frames_ to receive
    char buf[2];
    Serial.readBytes(buf, 2);
    frameCount = ((buf[1] << 8) + buf[0]);
    if (!dmxFile.write(buf[0]))
        return ERR_WRITING_FILE;
    if (!dmxFile.write(buf[1]))
        return ERR_WRITING_FILE;
    Serial.print(F("Package Size: "));
    Serial.println(frameCount);

    // the next two bytes determine the number of curves/timelines to receive
    Serial.readBytes(buf, 2);
    channelCount = ((buf[1] << 8) + buf[0]);
    if (!dmxFile.write(buf[0]))
        return ERR_WRITING_FILE;
    if (!dmxFile.write(buf[1]))
        return ERR_WRITING_FILE;
    Serial.print(F("Channel Count: "));
    Serial.println(channelCount);

    // next is a list of the channels that are used
    Serial.print(F("DMX-Channels used: "));
    uint16_t receivedChannelNumbers = 0;
    while (receivedChannelNumbers < channelCount)
    {
        Serial.readBytes(buf, 2);
        uint16_t channelNumber = ((buf[1] << 8) + buf[0]);
        if (!dmxFile.write(buf[0]))
            return ERR_WRITING_FILE;
        if (!dmxFile.write(buf[1]))
            return ERR_WRITING_FILE;
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
    Serial.print(F("Avaiting packages: "));
    Serial.println(channelCount * frameCount);
    uint32_t dataIndex = 0;
    while (dataIndex < channelCount * frameCount)
    {
        if (Serial.available())
        {
            byte ch = (byte)Serial.read();
            if (!dmxFile.write(ch))
                return ERR_WRITING_FILE;
            dataIndex++;
        }
    }
    // DATA END
    // --------
    dmxFile.close();

    return INF_FILE_SUCCESSFUL_WRITTEN;
}

/* ------------------------------ */
int8_t DMXKeyframeProcess::openDMXFile(String _filename)
{
    // Open file to read from
    char filename[_filename.length() + 1];
    _filename.toCharArray(filename, sizeof(filename));

    dmxFile = SD.open(filename);
    if (!dmxFile || dmxFile.isDirectory())
    {
        Serial.println(F("failed to open file for reading."));
        return ERR_READING_FILE;
    }
    return 1;
}

/* ------------------------------ */
bool DMXKeyframeProcess::readHeader()
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

    return 1;
}

/* ------------------------------ */
// Reads the dmx-values for all channels from the next frame.
// note: the file is kept open. the file-pointer automatically goes to the
// next bunch of values.
// int8_t DMXKeyframeProcess::readNextFrameChannelvalues()
// {
//     if (dmxFile.available())
//     {
//         dmxFile.readBytes(dmxValues, channelCount); // read one frame with all dmx-channel-values
//         return 0;
//     }
//     else
//     {
//         Serial.println(F("end of file"));
//         dmxFile.close();
//         return INF_END_OF_FILE;
//     }
// }

/* ------------------------------ */
int8_t DMXKeyframeProcess::loadFile(String _filename)
{
    openDMXFile(_filename);
    readHeader();

    uint32_t i = 0;
    while (dmxFile.available()) // the file pointer is already at the correct position after reading the header
    {
        dmxData[i] = dmxFile.read();
        i++;
    }
    Serial.print("loaded all data, bytes read: ");
    Serial.println(i);

    //  load all data into dmxData-Array in Extmem

    dmxFile.close();

    return 0;
}

/* ------------------------------ */
int8_t DMXKeyframeProcess::getDMXData(uint16_t channel, uint16_t _keyframe)
{
    return 0;
}

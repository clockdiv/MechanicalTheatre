#include "FileProcess.h"

DMAMEM char FileProcess::keyframeValuesBin[MAX_FRAMES * 2]; // the two-byte pairs of keyframes. assigned by receive_keyframes()
uint16_t FileProcess::packageSize = 0;                      // size of incoming data package
uint16_t FileProcess::curveCount = 0;                       // the number of curves/timelines to receive (each stepper one curve)

bool FileProcess::initFilesystem()
{
  return SD.begin(BUILTIN_SDCARD);
}

/* ------------------------------------ */
/* reads keyframes as high/low Byte pairs */
/* from Serial and stores them into a   */
/* char array.                          */
/* return values:                       */
/*  1 - received all                    */
/* -1 - did not receive as many bytes as expected */
/* -2 - error while writing file        */
/* ------------------------------------ */
int8_t FileProcess::receive_keyframes(const String filenames[], uint8_t count)
{

  // the first two bytes determine the number of _frames_ to receive
  // (number of _bytes_ to receive = number of _frames_ * 2)
  // (each frame is a unsigned 16-bit integer)
  char buf[2];
  Serial.readBytes(buf, 2);
  packageSize = ((buf[1] << 8) + buf[0]) * 2;

  // the next two bytes determine the number of curves/timelines to receive
  Serial.readBytes(buf, 2);
  curveCount = ((buf[1] << 8) + buf[0]);

  if (curveCount != count)
  {
    // Error: number of curves not equal to number of timelines
    return -3;
  }

  // receive each curve and store it as a separate file
  for (int i = 0; i < curveCount; i++)
  {
    // receive data according to the number of frames
    uint32_t index = 0;
    while (index < packageSize)
    {
      if (Serial.available())
      {
        char ch = (char)Serial.read();
        keyframeValuesBin[index] = ch;
        index++;
      }
    }

    if (index == packageSize)
    {
      if (!write_keyframes_to_file(filenames[i]))
      {
        // Error: error while writing file
        return -2;
      }
    }
    else
    {
      // Error: Didn't receive as many bytes as expected
      return -1;
    }
  }

  return 1;
}

/* ------------------------------------ */
/* lists all files in root directory    */
/* (we don't need sub-directories here) */
/* ------------------------------------ */
void FileProcess::listFiles()
{
  Serial.println("list all Files...");
  File root = SD.open("/");

  while (true)
  {
    File entry = root.openNextFile();
    if (!entry)
      break; // no more files
    Serial.println(entry.name());
    entry.close();
  }
  Serial.println("done.");
}

void FileProcess::deleteFiles(const String filenames[], uint8_t count)
{
  for (int i = 0; i < count; i++)
  {
    char filename[filenames[i].length() + 1];
    filenames[i].toCharArray(filename, sizeof(filename));

    if (SD.exists(filename))
    {
      Serial.print("deleting ");
      Serial.println(filename);
      SD.remove(filename);
    }
  }
}

/* ------------------------------------ */
/* Writes the 2-byte keyframe pairs to  */
/* a binary file                        */
/* ------------------------------------ */
bool FileProcess::write_keyframes_to_file(String _filename)
{
  char filename[_filename.length() + 1];
  _filename.toCharArray(filename, sizeof(filename));
  File file = SD.open(filename, FILE_WRITE | O_TRUNC);

  if (!file)
  {
    Serial.println(F("failed to open file for writing"));
    return false;
  }
  for (uint16_t i = 0; i < packageSize; i++)
  {
    if (!file.write(keyframeValuesBin[i]))
    {
      Serial.println(F("error while writing keyframeValues to file"));
      return false;
    }
  }
  file.close();
  return true;
}

/* ------------------------------------ */
/* Reads the 2-byte keyframe pairs from */
/* the binary file, turns them into     */
/* uint16_t values, stores them in an   */
/* array inside a MotorUnit object      */
/* ------------------------------------ */
bool FileProcess::read_keyframes_from_file(String _filename, MotorUnit &stepper, uint8_t motorIndex)
{
  char filename[_filename.length() + 1];
  _filename.toCharArray(filename, sizeof(filename));

  File file = SD.open(filename);

  Serial.print(_filename);
  Serial.print(F("... "));

  if (!file || file.isDirectory())
  {
    Serial.println(F("failed to open file for reading."));
    stepper.animationLength = 0;
    return false;
  }

  uint16_t index = 0;
  while (file.available())
  {
    char byteLow = file.read();
    char byteHigh = file.read();
    uint16_t value = (byteHigh << 8) + byteLow;
    stepper.setKeyframeValue(index, value);
    index++;
  }
  stepper.animationLength = index;
  file.close();
  Serial.println(F("read file."));
  return true;
}

bool FileProcess::read_all_files(const String filenames[], MotorUnit steppers[], uint8_t count)
{
  for (int i = 0; i < count; i++)
  {
    if (!read_keyframes_from_file(filenames[i], steppers[i], i))
    {
      Serial.println("error while reading file: " + filenames[i]);
      return false;
    }
  }
  return true;
}

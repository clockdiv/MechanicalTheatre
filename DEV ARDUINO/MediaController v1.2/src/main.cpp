#ifndef ARDUINO_TEENSY41
#error "teensy 4.1 needed for this project."
#endif

#include <Arduino.h>

// includes for dmx:
#include <TeensyDMX.h> // https://github.com/ssilverman/TeensyDMX

// includes for audio:
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Bounce2.h>

// local includes
#include "configurations.h"
#include "pins.h"
#include "stateMachine.h"
#include "dmxKeyframeProcess.h"

// GUItool: begin automatically generated code
AudioPlaySdWav playSdWav1;    //xy=179,246
AudioPlaySdWav playSdWav2;    //xy=216,296
AudioOutputI2SQuad i2s_quad1; //xy=478,262
AudioConnection patchCord1(playSdWav1, 0, i2s_quad1, 0);
AudioConnection patchCord2(playSdWav1, 1, i2s_quad1, 1);
AudioConnection patchCord3(playSdWav2, 0, i2s_quad1, 2);
AudioConnection patchCord4(playSdWav2, 1, i2s_quad1, 3);
AudioControlSGTL5000 sgtl5000_1; //xy=304,390
AudioControlSGTL5000 sgtl5000_2; //xy=353,432
// GUItool: end automatically generated code

// dmx configs
qindesign::teensydmx::Sender dmxTx{Serial6};
DMXKeyframeProcess dmxPlayer;
String dmxFileName = "DMX.DAT";

// timing
const uint8_t fps = 25;
unsigned long millisOld = 0, millisCurrent; // meassuring time to get into the fps-rhythm
unsigned long frameDuration = 1000 / fps;   // duration of a frame in milliseconds
uint16_t keyframeIndex = 0;                 // current position of the timeline, used for playback

// status led
unsigned long millisOldStatusLED = 0;
unsigned long statusLEDBlinkFrequency = 1000;
bool statusLEDstate = false;

// fade out
float fadeoutMultiplier = 1.0f;    // to slowly dimm down the lights and audio
const float dimmSpeed = 1 / 100.0; // that's a small number.
float volume = 0.7;
bool showEnding = false;

Bounce startStopTrigger;

// state logic
states state, stateOld;
uint16_t errorCode = 0;

// function declarations
void smRun();
void stateEnter();
void stateExit();
void __idle();
void __play();
void __incoming_serial();
void __error();

void triggerISR();
void playAudioFile(const char *filename, AudioPlaySdWav &player);
void stopAudioFile(AudioPlaySdWav &player);

void statusLEDOn();
void statusLEDOff();
void statusLEDUpdate();
void allDMXChannelsOff();

/*-------------------------------*/
void setup()
{
  pinMode(PIN_EXT_LED, OUTPUT);
  startStopTrigger.attach(PIN_START_STOP_TRIGGER, INPUT_PULLDOWN);
  startStopTrigger.interval(5);

  dmxTx.begin();

  stateOld = __UNDEFINED;
  state = __IDLE;

  // Setup both Audio Shields
  AudioMemory(10);

  sgtl5000_1.setAddress(LOW);
  sgtl5000_1.enable();

  sgtl5000_2.setAddress(HIGH);
  sgtl5000_2.enable();

  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);

  // Initialize SD-Card
  if (!SD.begin(SDCARD_CS_PIN))
  {
    Serial.println(F("initialization of SD Card failed!"));
    errorCode = ERR_SD_FAILED;
    state = __ERROR;
  }

  dmxPlayer.loadFile(dmxFileName);

  //show first 10 frames of dmx data:

  // for (int i = dmxPlayer.frameCount-125; i < dmxPlayer.frameCount; i++)
  // {
  //   Serial.print("frame: ");
  //   Serial.print(i);
  //   Serial.print("\t");
  //   for (int j = 0; j < dmxPlayer.channelCount; j++)
  //   {
  //     Serial.print(dmxPlayer.dmxData[i * dmxPlayer.channelCount + j]);
  //     Serial.print(", ");
  //   }
  //   Serial.println();
  // }
}

/*-------------------------------*/
void loop()
{
  startStopTrigger.update();

  if (state != stateOld)
  {
    Serial.print(F("state:\t\t"));
    Serial.println(stateStrings[state]);

    stateExit();
    stateEnter();
  }

  millisCurrent = millis();
  statusLEDUpdate();
  smRun();
}

/* ----------------------------- */
void smRun()
{
  stateOld = state;

  switch (state)
  {
  case __INCOMING_SERIAL:
    __incoming_serial();
    break;

  case __IDLE:
    __idle();
    break;

  case __PLAY:
    __play();
    break;

  case __ERROR:
    __error();
    break;

  case __UNDEFINED:
    break;

  default:
    break;
  }
}

/* ----------------------------- */
void stateEnter()
{
  switch (state)
  {
  case __INCOMING_SERIAL:
    break;

  case __IDLE:
    break;

  case __PLAY:
    statusLEDBlinkFrequency = 1000;
    keyframeIndex = 0;
    fadeoutMultiplier = 1.0f;
    showEnding = false;

    sgtl5000_1.volume(volume);
    sgtl5000_2.volume(volume);

    delay(10);
    playAudioFile("TEST12.WAV", playSdWav1);
    playAudioFile("TEST34.WAV", playSdWav2);
    break;

  case __ERROR:
    break;

  case __UNDEFINED:
    break;

  default:
    break;
  }
}

/* ----------------------------- */
void stateExit()
{
  statusLEDBlinkFrequency = 0;
  statusLEDOff();

  switch (stateOld)
  {
  case __INCOMING_SERIAL:
    break;

  case __IDLE:
    break;

  case __PLAY:
    allDMXChannelsOff();
    stopAudioFile(playSdWav1);
    stopAudioFile(playSdWav2);
    Serial.print("Max Audio Memory Usage: ");
    Serial.println(AudioMemoryUsageMax());
    break;

  case __ERROR:
    break;

  case __UNDEFINED:
    break;

  default:
    break;
  }
}

/*-------------------------------*/
void playAudioFile(const char *filename, AudioPlaySdWav &player)
{
  if (player.isPlaying())
  {
    // Serial.println("player is already playing");
    return;
  }

  // Serial.print("Playing file: ");
  // Serial.println(filename);

  // Start playing the file.  This sketch continues to
  // run while the file plays.
  player.play(filename);

  // A brief delay for the library read WAV info
  delay(5);
  return;
  // Simply wait for the file to finish playing.
  while (player.isPlaying())
  {
  }
}

/*-------------------------------*/
void stopAudioFile(AudioPlaySdWav &player)
{
  player.stop();
}

/*-------------------------------*/
void allDMXChannelsOff()
{
  for (int i = 0; i < 512; i++)
  {
    dmxTx.set(i, 0);
  }
}

/*-------------------------------*/
void __idle()
{
  if (startStopTrigger.read() == HIGH)
  {
    state = __PLAY;
  }
}

/*-------------------------------*/
void __play()
{
  if (millisCurrent - frameDuration >= millisOld)
  {
    millisOld = millisCurrent;
    if (keyframeIndex < dmxPlayer.frameCount && fadeoutMultiplier > 0.0f)
    {
      keyframeIndex++;

      Serial.print("frame: ");
      Serial.print(keyframeIndex);
      Serial.print("\t");
      for (int channelIndex = 0; channelIndex < dmxPlayer.channelCount; channelIndex++)
      {
        uint8_t data = dmxPlayer.dmxData[keyframeIndex * dmxPlayer.channelCount + channelIndex];
        uint16_t channel = dmxPlayer.dmxChannels[channelIndex];
        Serial.print(data);
        Serial.print(", ");
        dmxTx.set(channel, data);
      }
      Serial.println();

      if (showEnding)
      {
        fadeoutMultiplier -= dimmSpeed;
        sgtl5000_1.volume(volume * fadeoutMultiplier);
        sgtl5000_2.volume(volume * fadeoutMultiplier);
      }
    }
    else
    {
      state = __IDLE;
    }
  }

  if (startStopTrigger.risingEdge())
  {
    Serial.println("show Ending");
    showEnding = true;
  }

}

/* ------------------------------------ */
void serialEvent()
{
  state = __INCOMING_SERIAL;
}

/* ------------------------------------ */
void __incoming_serial()
{
  if (Serial.available() >= 1)
  {
    Serial.print("incoming serial: ");

    byte inChar = (byte)Serial.read();
    Serial.println(inChar, DEC);

    if (inChar == 'u')
    {
      statusLEDOn();

      int8_t receiveError = dmxPlayer.receive_keyframes(dmxFileName);
      if (receiveError == INF_FILE_SUCCESSFUL_WRITTEN)
      {
        state = __IDLE;
      }
      else
      {
        errorCode = receiveError;
        state = __ERROR;
      }
    }
  }
}

/* ------------------------------------ */
void __error()
{
  if (errorCode <= 200)
    errorCode = ERR_UNDEFINED;
  uint8_t blinkCount = errorCode - 200;

  for (int i = 0; i < blinkCount; i++)
  {
    statusLEDOn();
    delay(100);
    statusLEDOff();
    delay(100);
  }
  delay(2000);
}

/* ------------------------------------ */
void statusLEDOn()
{
  statusLEDstate = HIGH;
  digitalWrite(PIN_EXT_LED, HIGH);
}

/* ------------------------------------ */
void statusLEDOff()
{
  statusLEDstate = LOW;
  digitalWrite(PIN_EXT_LED, LOW);
}

/* ------------------------------------ */
void statusLEDUpdate()
{
  if (statusLEDBlinkFrequency > 0)
  {
    if (millisCurrent - millisOldStatusLED >= statusLEDBlinkFrequency)
    {
      statusLEDstate ? statusLEDOff() : statusLEDOn();
      millisOldStatusLED = millisCurrent;
    }
  }
}

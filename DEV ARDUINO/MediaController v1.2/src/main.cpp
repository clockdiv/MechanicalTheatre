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

// local includes
#include "pins.h"
#include "stateMachine.h"

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
uint8_t data[3]{0x44, 0x88, 0xcc};

// timing
const uint8_t fps = 25;
long millisOld = 0, millisCurrent; // meassuring time to get into the fps-rhythm
long frameDuration = 1000 / fps;   // duration of a frame in milliseconds
uint16_t keyframeIndex = 0;        // current position of the timeline, used for playback

// state logic
states state, stateOld;
bool startShow = false, stopShow = false;

// function declarations
void smRun();
void stateEnter();
void stateExit();
void __play();

void triggerISR();
void setupAudioShields();
void playFile(const char *filename, AudioPlaySdWav &player);
void stopFile(AudioPlaySdWav &player);
void statusLEDOn();
void statusLEDOff();

/*-------------------------------*/
void setup()
{
  pinMode(PIN_START_STOP_TRIGGER, INPUT_PULLDOWN);
  pinMode(PIN_EXT_LED, OUTPUT);
  attachInterrupt(PIN_START_STOP_TRIGGER, triggerISR, CHANGE);

  dmxTx.begin();
  // dmxTx.set(1, 128);
  // dmxTx.set(10, data, 3);  
  setupAudioShields();

  state = __IDLE; 
}

/*-------------------------------*/
void loop()
{
  if (state != stateOld)
  {
    Serial.print(F("state:\t\t"));
    Serial.println(stateStrings[state]);

    stateExit();
    stateEnter();
  }
  millisCurrent = millis();

  smRun();
}

/* ----------------------------- */
void smRun()
{
  stateOld = state;

  switch (state)
  {
  case __INCOMING_SERIAL:
    //__incoming_serial();
    break;

  case __IDLE:
    break;

  case __PLAY:
    __play();
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
    statusLEDOff();
    break;

  case __PLAY:
    statusLEDOn();
    playFile("TEST12.WAV", playSdWav1);
    playFile("TEST34.WAV", playSdWav2);
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
  switch (stateOld)
  {
  case __INCOMING_SERIAL:
    break;

  case __IDLE:
    break;

  case __PLAY:
    stopFile(playSdWav1);
    stopFile(playSdWav2);
    break;

  case __UNDEFINED:
    break;

  default:
    break;
  }
}

/*-------------------------------*/
void setupAudioShields()
{
  float volume = 0.7;

  AudioMemory(10);

  sgtl5000_1.setAddress(LOW);
  sgtl5000_1.enable();
  sgtl5000_1.volume(volume);

  sgtl5000_2.setAddress(HIGH);
  sgtl5000_2.enable();
  sgtl5000_2.volume(volume);

  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN)))
  {
      Serial.println("Unable to access the SD card");
  }
}

/*-------------------------------*/
void playFile(const char *filename, AudioPlaySdWav &player)
{
  if (player.isPlaying())
    return;

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
void stopFile(AudioPlaySdWav &player)
{
  player.stop();
}

/*-------------------------------*/
void triggerISR()
{
  digitalReadFast(PIN_START_STOP_TRIGGER) ? state = __PLAY : state = __IDLE;
}

/*-------------------------------*/
void __play()
{
  if (millisCurrent - frameDuration > millisOld)
  {
    keyframeIndex++;

    double v = abs(sin(millisCurrent / 100.0));
    dmxTx.set(1, uint8_t(v * 255));

    millisOld = millisCurrent;
  }
}

/* ------------------------------------ */
void serialEvent() {
  state = __INCOMING_SERIAL;
}


/* ------------------------------------ */
void __incoming_serial() {
  // if (Serial.available() >= 1) {
  //   Serial.println("incoming serial");

  //   char inChar = (char)Serial.read();
  //   if (inChar == 'u') {
  //     buzzer_beep(1, 100);

  //     digitalWrite(PIN_EXT_LED, HIGH);

  //     int8_t receiveError = FileProcess::receive_keyframes(filenames, UNIT_COUNT);
  //     if (receiveError == -1) {
  //       // did not receive as many bytes as expected
  //     } else if (receiveError == -2) {
  //       // error while writing file to sd-card
  //     }

  //     digitalWrite(PIN_EXT_LED, LOW);
  //     buzzer_beep(2, 100);
  //     delay(200);

  //     // read all files after they are received and reset the animation
  //     FileProcess::read_all_files(filenames, steppers, UNIT_COUNT);
  //     keyframeIndex = 0;
  //     state = __RESET;
  //   }
  //   else if (inChar == 'r') {
  //     FileProcess::read_all_files(filenames, steppers, UNIT_COUNT);
  //     state = __RESET;
  //   }
  //   else if (inChar == 'p') {
  //      for (int i = 0; i < UNIT_COUNT; i++) {
  //       steppers[i].setPlay();
  //      }
  //     state = __PLAY;
  //   }
  // }   
  // else {
  //   Serial.print("idle after incoming serial");
  //   state = __IDLE;
  // }
}


/* ------------------------------------ */
void statusLEDOn()
{
  digitalWrite(PIN_EXT_LED, HIGH);
}

/* ------------------------------------ */
void statusLEDOff()
{
  digitalWrite(PIN_EXT_LED, LOW);
}
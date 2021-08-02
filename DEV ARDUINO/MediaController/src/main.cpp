#include <Arduino.h>

// includes for dmx:
#include <TeensyDMX.h> // https://github.com/ssilverman/TeensyDMX

// includes for audio:
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

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

// Use these with the Teensy Audio Shield
#define SDCARD_CS_PIN 10
#define SDCARD_MOSI_PIN 7
#define SDCARD_SCK_PIN 14


// dmx configs
qindesign::teensydmx::Sender dmxTx{Serial6};
uint8_t data[3]{0x44, 0x88, 0xcc};


// state logic
bool isRunning = false;


// function declarations
void triggerISR();
void setupAudioShields();
void playFile(const char *filename, AudioPlaySdWav &player);
void startShow();


void setup()
{

  dmxTx.begin();
  // dmxTx.set(1, 128);
  // dmxTx.set(10, data, 3);

  setupAudioShields();

  attachInterrupt(24, triggerISR, CHANGE);

}

void loop()
{
  double v = abs(sin(millis() / 1000.0));
  dmxTx.set(1, uint8_t(v * 255));
  delay(10);
}


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
    while (1)
    {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }
}


void playFile(const char *filename, AudioPlaySdWav &player)
{
  if(player.isPlaying()) return;
  
  Serial.print("Playing file: ");
  Serial.println(filename);

  // Start playing the file.  This sketch continues to
  // run while the file plays.
  player.play(filename);

  // A brief delay for the library read WAV info
  delay(5);
  return;
  // Simply wait for the file to finish playing.
  while (player.isPlaying()) {
    // uncomment these lines if you audio shield
    // has the optional volume pot soldered
    //float vol = analogRead(15);
    //vol = vol / 1024;
    // sgtl5000_1.volume(vol);
  }
}

void triggerISR() {
  isRunning = digitalReadFast(24);;
  if (isRunning) {
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }
}


void startShow() {
  playFile("TEST12.WAV", playSdWav1);
  playFile("TEST34.WAV", playSdWav2);
}



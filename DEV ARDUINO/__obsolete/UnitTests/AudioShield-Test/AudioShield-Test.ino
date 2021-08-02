#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioPlaySdWav           playSdWav1;     //xy=179,246
AudioPlaySdWav           playSdWav2;     //xy=216,296
AudioOutputI2SQuad       i2s_quad1;      //xy=478,262
AudioConnection          patchCord1(playSdWav1, 0, i2s_quad1, 0);
AudioConnection          patchCord2(playSdWav1, 1, i2s_quad1, 1);
AudioConnection          patchCord3(playSdWav2, 0, i2s_quad1, 2);
AudioConnection          patchCord4(playSdWav2, 1, i2s_quad1, 3);
AudioControlSGTL5000     sgtl5000_1;     //xy=304,390
AudioControlSGTL5000     sgtl5000_2;     //xy=353,432
// GUItool: end automatically generated code

// Use these with the Teensy Audio Shield
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

void setup() {
  // put your setup code here, to run once:
  
  AudioMemory(10);
  
  sgtl5000_1.setAddress(LOW);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.8);

  sgtl5000_2.setAddress(HIGH);
  sgtl5000_2.enable();
  sgtl5000_2.volume(0.8);


  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    // stop here, but print a message repetitively
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
 playFile("SDTEST1.WAV");
 playFile2("SDTEST2.WAV");
//delay(1000);
Serial.println("hello");
delay(1000);
}


void playFile(const char *filename)
{
  if(playSdWav1.isPlaying()) return;
  
  Serial.print("Playing file: ");
  Serial.println(filename);

  // Start playing the file.  This sketch continues to
  // run while the file plays.
  playSdWav1.play(filename);

  // A brief delay for the library read WAV info
  delay(5);
  return;
  // Simply wait for the file to finish playing.
  while (playSdWav1.isPlaying()) {
    // uncomment these lines if you audio shield
    // has the optional volume pot soldered
    //float vol = analogRead(15);
    //vol = vol / 1024;
    // sgtl5000_1.volume(vol);
  }
}

void playFile2(const char *filename)
{
  if(playSdWav2.isPlaying()) return;
  
  Serial.print("Playing file: ");
  Serial.println(filename);

  // Start playing the file.  This sketch continues to
  // run while the file plays.
  playSdWav2.play(filename);

  // A brief delay for the library read WAV info
  delay(5);

}

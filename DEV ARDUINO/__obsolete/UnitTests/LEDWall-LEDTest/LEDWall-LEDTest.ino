/*  OctoWS2811 Teensy4_PinList.ino - Demonstrate use of any pins
    http://www.pjrc.com/teensy/td_libs_OctoWS2811.html

  With Teensy 4.x, you can use any group of pins.  You are not limited
  to only 8 fixed pins as with Teensy 3.x.  This example shows how to
  use only 4 pins, which are the 4 pins of the Octo28 shield which do
  not conflict with the Audio shield.

  Required Connections
  --------------------
    pin 2:  LED Strip #1
    pin 14: LED strip #2
    pin 6:  LED strip #5
    pin 5:  LED strip #8
*/

#include <OctoWS2811.h>
#define LED 13
// Any group of digital pins may be used
const int numPins = 4;
byte pinList[numPins] = {28, 29, 30, 31};

const int ledsPerStrip = 300;

// These buffers need to be large enough for all the pixels.
// The total number of pixels is "ledsPerStrip * numPins".
// Each pixel needs 3 bytes, so multiply by 3.  An "int" is
// 4 bytes, so divide by 4.  The array is created using "int"
// so the compiler will align it to 32 bit memory.
DMAMEM int displayMemory[ledsPerStrip * numPins * 3 / 4];
int drawingMemory[ledsPerStrip * numPins * 3 / 4];

const int config = WS2811_GRB | WS2811_800kHz;

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config, numPins, pinList);

bool isRunning = false;
bool isBlack = true;

void triggerISR() {
  isRunning = digitalReadFast(24);
  
  if (isRunning) {
    digitalWrite(LED, HIGH);
    isBlack = false;
  } else {
    digitalWrite(LED, LOW);
  }
}


void setup() {
  pinMode(LED, OUTPUT);
  pinMode(24, INPUT);
  attachInterrupt(24, triggerISR, CHANGE);
  digitalWrite(LED, LOW);
  leds.begin();
}

#define RED    0xFF0000
#define GREEN  0x00FF00
#define BLUE   0x0000FF
#define YELLOW 0xFFFF00
#define PINK   0xFF1088
#define ORANGE 0xE05800
#define WHITE  0xFFFFFF
#define BLACK  0x000000

#define RED50    0x880000
#define GREEN50  0x008800
#define BLUE50   0x000088
#define WHITE50  0x888888

// Less intense...
/*
  #define RED    0x160000
  #define GREEN  0x001600
  #define BLUE   0x000016
  #define YELLOW 0x101400
  #define PINK   0x120009
  #define ORANGE 0x100400
  #define WHITE  0x101010
*/

void loop() {
  int microsec = 2000000 / leds.numPixels();  // change them all in 2 seconds

  if (isRunning) {
    colorWipe(RED50, microsec);
    colorWipe(WHITE50, microsec);
    colorWipe(GREEN50, microsec);
    colorWipe(WHITE50, microsec);
    colorWipe(BLUE50, microsec);
//    colorWipe(YELLOW, microsec);
//    colorWipe(PINK, microsec);
//    colorWipe(ORANGE, microsec);
    colorWipe(WHITE50, microsec);
  }
  else {
    if (!isBlack) {
      //black();
    }
  }

}

void black() {
  Serial.println("paint it black");
  for (int i = 0; i < leds.numPixels(); i++) {
    leds.setPixel(i, BLACK);
  }
  leds.show();
  isBlack = true;
}

void colorWipe(int color, int wait)
{
  if (!isRunning) {
    return;
  }
  for (int i = 0; i < leds.numPixels(); i++) {
    if (!isRunning) {
      break;
    }
    leds.setPixel(i, color);
    leds.show();
    delayMicroseconds(wait);
  }
}

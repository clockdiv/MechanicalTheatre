#include <Adafruit_NeoPixel.h>
#define PIN_WS2812B 6
#define RESOLUTION_X 30
#define RESOLUTION_Y 3

char buf[RESOLUTION_X * 3];

uint16_t pixelCount = RESOLUTION_X * RESOLUTION_Y;
uint16_t pixelCounter;
bool ledStat = false;
Adafruit_NeoPixel pixels(pixelCount, PIN_WS2812B, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(2000000);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  pixels.begin();
  pixels.setBrightness(50);
  pixels.clear();
  pixels.show();
  pixelCounter = 0;
}

void loop() {
  if (Serial.available() >= RESOLUTION_X) {
    Serial.readBytes(buf, RESOLUTION_X * 3);
    for(uint8_t i = 0; i < RESOLUTION_X * 3; i+=3){
      uint8_t r = buf[i];
      uint8_t g = buf[i+1];
      uint8_t b = buf[i+2];
      //Serial.write(r);
      //Serial.write(g);      
      //Serial.write(b);
      pixels.setPixelColor(pixelCounter, pixels.Color(r, g, b));
      pixelCounter++;
    }
    
    if (pixelCounter == pixelCount) {
      ledStat = !ledStat;
      digitalWrite(LED_BUILTIN, ledStat);

      pixels.show();
      pixelCounter = 0;
    }
  }
}

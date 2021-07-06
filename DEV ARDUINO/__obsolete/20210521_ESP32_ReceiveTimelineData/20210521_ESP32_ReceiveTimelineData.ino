// https://github.com/mathertel/LiquidCrystal_PCF8574 version 1.3.0
#include <LiquidCrystal_PCF8574.h>
#include <Wire.h>
#include "SPIFFS.h"

#define MAX_FRAMES 1000
#define MAX_CHAR 2000

LiquidCrystal_PCF8574 lcd(0x27); // set the LCD address to 0x27 for a 16 chars and 2 line display
const uint8_t ledPin = 2;

uint16_t keyframeValues[MAX_FRAMES];
uint16_t keyframeCount = 0;

char keyframeValuesBin[MAX_CHAR];
uint32_t keyframeBytes = 0;

String dumpFilename = "/keyframes.dat";


void initDisplay(bool full = false) {
  if (full) {
    lcd.begin(20, 4); // initialize the lcd
    lcd.setBacklight(255);
    lcd.home();
    lcd.clear();
    lcd.print("Hello World -");
    lcd.setCursor(0, 1);
    lcd.print("Hello Magdeburg!");
  }
  else {
    lcd.home();
    lcd.clear();
    lcd.setCursor(0, 0);
  }
}


void ledBlink(uint8_t _i = 3) {
  for (int i = 0; i < _i; i++) {
    digitalWrite(2, HIGH);
    delay(200);
    digitalWrite(2, LOW);
    delay(200);
  }
}

void setup() {
  pinMode(2, OUTPUT);
  Serial.begin(115200);
  initDisplay(true);

  // Init the SPI Flash File System
  if (!SPIFFS.begin(true)) {
    lcd.print("SPIFFS failed");
    Serial.println("SPIFFS failed");
    while (true);
  }
}

void loop() {
  if (Serial.available() >= 1) {
    char inChar = (char)Serial.read();
    if (inChar == 'u') {
      digitalWrite(ledPin, HIGH);
      initDisplay();
      lcd.print("receive f. serial...");
      receiveKeyframesFromSerialBinary();
      digitalWrite(ledPin, LOW);
    }
    else if (inChar == 'r') {
      initDisplay();
      lcd.print("read from file...");
      readKeyframeValuesFromFileBinary();
    }
  }
}


void receiveKeyframesFromSerialBinary() {
  uint32_t index = 0;
  while (Serial.available()) {
      char ch = (char)Serial.read();
      keyframeValuesBin[index] = ch;
      lcd.setCursor(0, 1);
      lcd.print(index);
      index++;
  }
  keyframeBytes = index;
  writeKeyframeValuesToFileBinary();

  lcd.setCursor(0, 1);
  lcd.print(keyframeBytes);
  lcd.setCursor(6, 1);
  lcd.print("Bytes");
}

void writeKeyframeValuesToFileBinary() {
  File file = SPIFFS.open(dumpFilename, FILE_WRITE);

  if (!file) {
    Serial.println("failed to open file for writing");
    return;
  }
  for (uint16_t i = 0; i < keyframeBytes; i++) {
    if (!file.write(keyframeValuesBin[i])) {
      Serial.println("error while writing keyframeValues to file");
    }
  }
  file.close();
  ledBlink();
  lcd.setCursor(0, 2);
  lcd.print("written to file!");
}

void readKeyframeValuesFromFileBinary() {
  File file = SPIFFS.open(dumpFilename);

  if (!file) {
    Serial.println("failed to open file for reading");
    return;
  }

  while (file.available()) {
    char byteLow = file.read();
    char byteHigh = file.read();
    uint16_t val = (byteHigh << 8) + byteLow;
    Serial.println(val);
  }
  file.close();
}

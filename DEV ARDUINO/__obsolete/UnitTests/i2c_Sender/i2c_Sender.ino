#include <Wire.h>

#define TEENSY_I2C_ADDR 0x42

void setup() {
  Serial.begin(115200);
  Wire.begin();
}

void loop() {
  Wire.beginTransmission(TEENSY_I2C_ADDR);
  Wire.write(1);
  Wire.endTransmission();

  Wire.requestFrom(TEENSY_I2C_ADDR, 1);
  while (Wire.available())
  {
    int c = Wire.read();
    Serial.println(c);
  }


  delay(1000);
}

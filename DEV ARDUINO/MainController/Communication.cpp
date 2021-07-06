#include <Arduino.h>
#include <Wire.h>
#include "Communication.h"

#define TEENSY_I2C_ADDR 0x10

namespace Communication {

static uint8_t teensyState = 255;


uint8_t teensyRequestState() {
  Wire.requestFrom(TEENSY_I2C_ADDR, 1);
  while (Wire.available()) {
    teensyState = Wire.read();
  }
  Serial.println(teensyState);
  return teensyState;
}


void sendRunCommand() {
  Wire.beginTransmission(TEENSY_I2C_ADDR);
  Wire.write('p');
  Wire.endTransmission();
}

}

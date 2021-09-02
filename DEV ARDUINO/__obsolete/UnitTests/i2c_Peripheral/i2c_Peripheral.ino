#include "i2c_driver.h"
#include "i2c_driver_wire.h"

#define I2C_ADDR 0x42

const int led = 13;

uint8_t opcode; // register

void receiveEvent(int bytes) {
  Serial.print("receive Event: ");
  Serial.println(bytes);

  opcode = Wire.read();
  // If there are more than 1 byte, then the master is writing to the slave
  if (bytes > 1) {
    switch (opcode) {
      case 0x00:
        break;

      case 0x01:
        break;

      //...

      default:
        break;
    }
  }
}

void requestEvent() {
  Serial.print("request Event: ");
  Serial.println(opcode);

  Wire.write(5); // sending YES to esp

  switch (opcode) {
    case 0x02:
      break;

    case 0x03:
      break;

    //...

    default:
      break;
  }
}

void setup() {
  pinMode(led, OUTPUT);

  Wire.begin(I2C_ADDR);
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);
}

void loop() {
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(100);               // wait for a second
}

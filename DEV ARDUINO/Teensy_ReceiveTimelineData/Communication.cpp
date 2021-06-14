#include "Communication.h"
#include "StateMachine.h"

#define TEENSY_I2C_ADDR 0x10

void beginCommunication() {
  Serial.println("begin communication");
  Wire.begin(TEENSY_I2C_ADDR);
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);
}


void requestEvent() {
  Serial.print("request coming in. ");
  Serial.print("State from requestEvent: ");
  Serial.println(state);
  Wire.write(state);
}

void receiveEvent(int count) {
  Serial.println("receive Event");
  while(Wire.available() > 0) {
    char c = Wire.read();
    Serial.println(c);
    if (c == 'p') {
      Serial.println("PLAY SHOW");
    }
  }
  state = __PLAY;
}

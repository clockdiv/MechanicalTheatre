#include "Communication.h"
//#include "StateMachine.h"

#define TEENSY_I2C_ADDR 0x10

namespace Communication {
  void beginCommunication() {
    Wire.begin(TEENSY_I2C_ADDR);
    Wire.onRequest(requestEvent);
    Wire.onReceive(receiveEvent);
  }


  void requestEvent() {
    Serial.println(F("requestEvent coming in. current State: "));
    //Serial.println(state);
    //Wire.write(state);
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
    //state = __PLAY;
  }
};
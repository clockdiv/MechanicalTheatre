#ifndef I2CHANDLER_H
#define I2CHANDLER_H

//#include "i2c_driver_wire.h"
#include <Wire.h>
#include "StateMachine.h"

#define TEENSY_I2C_ADDR 0x10
#define REQUEST_IDLESTATE 0x01
#define REQUEST_SHOWSTART 0x02
#define REQUEST_MOTORTEST 0x03

class i2cHandler
{
private:
    static int opcode;      // register
    static states* state;

public:
    i2cHandler(){ opcode = 0x00; };
    static void initI2C(states* _state);
    static void receiveEvent(int bytes);
    static void requestEvent();
};

#endif
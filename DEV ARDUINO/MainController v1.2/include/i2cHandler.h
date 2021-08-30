#ifndef I2CHANDLER_H
#define I2CHANDLER_H

#include "Wire.h"
#include "StateMachine.h"

#define TEENSY_I2C_ADDR 0x10
#define REQUEST_IDLESTATE 0x01
#define REQUEST_SHOWSTART 0x02
#define REQUEST_MOTORTEST 0x03

class i2cHandler
{
private:
    // static int opcode;      // register
    // static states* state;

public:
    i2cHandler(){};
    static void initI2C();
    bool requestIdleState();
    bool requestStart();
    bool requestMotortest();
};

#endif
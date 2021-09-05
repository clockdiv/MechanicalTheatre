#ifndef I2CHANDLER_H
#define I2CHANDLER_H

#include <Arduino.h>
#include "Wire.h"
#include "StateMachine.h"

#define TEENSY_I2C_ADDR 0x10
#define REQUEST_IDLESTATE 0x01
#define REQUEST_SHOWSTART 0x02
#define REQUEST_MOTORTEST 0x03
#define REQUEST_TEST_MSG 0x10

class i2cHandler
{
private:
    static int opcode;      // register

public:
    i2cHandler(){};
    static void initI2C();
    bool requestIdleState();
    bool requestStart();
    bool requestMotortest();
    bool requestTest();
};

#endif
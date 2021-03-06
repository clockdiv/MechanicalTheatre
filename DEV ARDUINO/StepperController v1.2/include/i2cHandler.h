#ifndef I2CHANDLER_H
#define I2CHANDLER_H

#include "i2c_driver_wire.h"
#include "StateMachine.h"

#define TEENSY_I2C_ADDR 0x10
#define REQUEST_STATE 0x01
#define REQUEST_SHOWSTART 0x02
#define REQUEST_MOTORTEST 0x03
#define REQUEST_TEST_MSG 0x10
#define REQUEST_SHOWSTOP 0x04

class i2cHandler
{
private:
    static int opcode; // register
    static states *state;

public:
    volatile static bool stateChange;
    volatile static states stateNext;

    i2cHandler() { opcode = 0x00; };
    static void initI2C(states *_state);
    static void receiveEvent(int bytes);
    static void requestEvent();
};


#endif
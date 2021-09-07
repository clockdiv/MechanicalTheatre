#include "i2cHandler.h"

int i2cHandler::opcode = 0x00;
states *i2cHandler::state = nullptr;
volatile states i2cHandler::stateNext = __UNDEFINED;
volatile bool i2cHandler::stateChange = false;

void i2cHandler::initI2C(states *_state)
{
    state = _state;
    Wire.begin(TEENSY_I2C_ADDR);
    Wire.onRequest(requestEvent);
    Wire.onReceive(receiveEvent);
}

void i2cHandler::receiveEvent(int bytes)
{
    opcode = 0x00;
    while (Wire.available())
    {
        opcode = Wire.read(); // set the register
    }
}

void i2cHandler::requestEvent()
{
    switch (opcode)
    {
    case REQUEST_STATE:
        Wire.write(*state);
        break;

    case REQUEST_SHOWSTART: // "Let's start the show together, or ain't you ready yet?"
        Wire.write(*state);

        if (*state == __IDLE)
        {
            stateChange = true;
            stateNext = __PLAY;
        }
        break;
        
    case REQUEST_SHOWSTOP:
        Wire.write(*state);
        if(*state == __PLAY)
        {
            stateChange = true;
            stateNext = __RESET;
        }
        break;

    case REQUEST_MOTORTEST:
        stateChange = true;
        stateNext = __HARDWARE_TEST;
        Wire.write(1);
        break;

    case REQUEST_TEST_MSG:
        Wire.write(33);
        break;

    default:
        break;
    }

    opcode = 0x00;
}
#include "i2cHandler.h"

int i2cHandler::opcode = 0x00;
states *i2cHandler::state;

void i2cHandler::initI2C(states *_state)
{
    state = _state;
    Wire.begin(TEENSY_I2C_ADDR);
    Wire.onRequest(requestEvent);
    Wire.onReceive(receiveEvent);
}

void i2cHandler::receiveEvent(int bytes)
{
    Serial.println("receive Event");
    Serial.println(bytes);
    // sets the register
    opcode = Wire.read();

    // If there are more than 1 byte, then the master is writing to the slave
    // (not needed here atm)
    if (bytes > 1)
    {
        switch (opcode)
        {
        case 0x00:
            break;

        case 0x01:
            break;

        case 0x02:
            break;

        case 0x03:
            break;

            //...

        default:
            break;
        }
    }
}

void i2cHandler::requestEvent()
{
    Serial.println("request Event");
    Serial.println(opcode);
    switch (opcode)
    {
    case REQUEST_IDLESTATE: // "Are you IDLE?"
        if (*state == __IDLE)
        {
            Wire.write(1); // sending YES to esp
        }
        else
        {
            Wire.write(0); // sending NO to esp
        }
        break;

    case REQUEST_SHOWSTART: // "Let's start the show together, or ain't you ready yet?"
        if (*state == __IDLE)
        {
            Wire.write(1); // sending YES I'M READY to esp
            *state = __PLAY;
        }
        else
        {
            Wire.write(0); // sending NOT READY YET to esp
        }
        break;

    case REQUEST_MOTORTEST:
        *state = __HARDWARE_TEST;
        Wire.write(1);
        break;

    default:
        break;
    }
    opcode = 0x00;
}
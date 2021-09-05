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
    // Serial.println("1) receive Event");
    // Serial.print("Bytes: ");
    // Serial.println(bytes);
    // sets the register
    opcode = 0x00;
    opcode = Wire.read();
    // Serial.print("OPCode: ");
    // Serial.println(opcode);

    // // If there are more than 1 byte, then the master is writing to the slave
    // // (not needed here atm)

    // if (bytes > 1)
    // {
    //     switch (opcode)
    //     {
    //     case 0x00:
    //         break;

    //     case 0x01:
    //         break;

    //     case 0x02:
    //         break;

    //     case 0x03:
    //         break;

    //         //...

    //     default:
    //         break;
    //     }
    // }
}

void i2cHandler::requestEvent()
{
    // Serial.println("2) Request");
    // Serial.print("already known opcode: ");
    // Serial.print(opcode);
    switch (opcode)
    {
    case REQUEST_IDLESTATE: // "Are you IDLE?"
        // Serial.print(" Request IdleState");
        if (*state == __IDLE)
        {
            // Serial.println(" yes, IDLE, answering with 1");
            Wire.write(1); // sending YES to esp
        }
        else if (*state == __RESET || *state == __WAIT_FOR_MOTOR_INIT)
        {
            Wire.write(2);
        }
        else
        {
            // Serial.println(" no, NOT IDLE, answering with 0");
            Wire.write(0); // sending NO to esp
        }
        break;

    case REQUEST_SHOWSTART: // "Let's start the show together, or ain't you ready yet?"
        // Serial.print(" Request ShowStart");
        if (*state == __IDLE)
        {
            // Serial.println(" show can start, answering with 1");
            Wire.write(1); // sending YES I'M READY to esp
            *state = __PLAY;
        }
        else
        {
            // Serial.println(" show cannont start, answering with 0");
            Wire.write(0); // sending NOT READY YET to esp
        }
        break;

    case REQUEST_MOTORTEST:
        *state = __HARDWARE_TEST;
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
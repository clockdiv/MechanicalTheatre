#include "i2cHandler.h"



void i2cHandler::initI2C()
{
    Wire.begin();
}

int8_t i2cHandler::requestState()
{   
    // checks if the teensy is in idle mode and is ready to play the show
    Serial.print(F("REQUEST STATE..."));
    // set i2c register
    Wire.beginTransmission(TEENSY_I2C_ADDR);
    Wire.write(REQUEST_STATE);
    Wire.endTransmission();

    // send request
    Wire.requestFrom(TEENSY_I2C_ADDR, 1);

    while (Wire.available())
    {
        int teensyState = Wire.read();
        Serial.print(" state=");
        Serial.println(teensyState);
        return teensyState;
    }
    return -1;
}

bool i2cHandler::requestStart()
{
    Serial.print(F("REQUEST STARRRRT... "));
    Wire.beginTransmission(TEENSY_I2C_ADDR);
    Wire.write(REQUEST_SHOWSTART);
    Wire.endTransmission();

    // send request
    Wire.requestFrom(TEENSY_I2C_ADDR, 1);
    
    while (Wire.available())
    {
        int teensyState = Wire.read();
        Serial.println(teensyState);
        if (teensyState == 3)   
        {
            return true;
        }
        else
        {
            Serial.print(F("Teensy can't start because it's in state "));
            Serial.println(teensyState);
            return false;
        }
    }
    return false;
}

bool i2cHandler::requestMotortest()
{
    // checks if the teensy is in idle mode and is ready to play the show

    // set i2c register
    Wire.beginTransmission(TEENSY_I2C_ADDR);
    Wire.write(REQUEST_MOTORTEST);
    Wire.endTransmission();

    // send request
    Wire.requestFrom(TEENSY_I2C_ADDR, 1);

    while (Wire.available())
    {
        int c = Wire.read();
        if (c == 1)
        {
            return true;
        }
        else
        {
            break;
        }
    }
    return false;
}

bool i2cHandler::requestTest()
{
    // send '1' to teensy to tell it to start
    Wire.beginTransmission(TEENSY_I2C_ADDR);
    Wire.write(REQUEST_TEST_MSG);
    Wire.endTransmission();

    Wire.requestFrom(TEENSY_I2C_ADDR, 1);

    while (Wire.available())
    {
        int c = Wire.read();
        if (c == 33)
        {
            return true;
        }
        else
        {
            break;
        }
    }
    return false;
}
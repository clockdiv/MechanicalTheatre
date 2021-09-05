#include "i2cHandler.h"



void i2cHandler::initI2C()
{
    Wire.begin();
}

bool i2cHandler::requestIdleState()
{   
    // checks if the teensy is in idle mode and is ready to play the show
    Serial.print("request idle state...");
    // set i2c register
    Wire.beginTransmission(TEENSY_I2C_ADDR);
    Wire.write(REQUEST_IDLESTATE);
    Wire.endTransmission();

    // send request
    Wire.requestFrom(TEENSY_I2C_ADDR, 1);
    while (Wire.available())
    {
        int c = Wire.read();
        Serial.println(c);
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

bool i2cHandler::requestStart()
{
    Serial.print("Request Start... ");
    // send '1' to teensy to tell it to start
    Wire.beginTransmission(TEENSY_I2C_ADDR);
    Wire.write(REQUEST_SHOWSTART);
    Wire.endTransmission();

    // send request
    Wire.requestFrom(TEENSY_I2C_ADDR, 1);
    while (Wire.available())
    {
        int c = Wire.read();
        Serial.println(c);
        if (c == 1)
        {
            return true;
        }
        else
        {
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
    Serial.print(".");
    // send '1' to teensy to tell it to start
    Wire.beginTransmission(TEENSY_I2C_ADDR);
    Wire.write(REQUEST_TEST_MSG);
    Wire.endTransmission();
    //delay(50);
    // send request
    Wire.requestFrom(TEENSY_I2C_ADDR, 1);
    //delay(50);
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
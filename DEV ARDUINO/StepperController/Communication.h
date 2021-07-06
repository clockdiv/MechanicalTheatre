#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <i2c_driver.h>
#include <i2c_driver_wire.h>
  
void beginCommunication();
void requestEvent() ;
void receiveEvent(int count);

#endif
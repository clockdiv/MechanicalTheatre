#ifndef STATEMACHINE_H
#define STATEMACHINE_H
#include <map>

enum states
{
  __INCOMING_SERIAL,
  __RESET,
  __WAIT_FOR_MOTOR_INIT,
  __IDLE,
  __PLAY,
  __HARDWARE_TEST,
  __ERROR,
  __UNDEFINED
};
extern states state;

#endif

#ifndef STATEMACHINE_H
#define STATEMACHINE_H

enum states {
  __INCOMING_SERIAL,
  __RESET,
  __WAIT_FOR_MOTOR_INIT,
  __WAIT_FOR_TEENSY,
  __IDLE,
  __PLAY,
  __UNDEFINED
};
extern states state;

static String stateStrings[] = {
  "INCOMING SERIAL",
  "RESET",
  "WAIT FOR MOTOR INIT",
  "WAIT FOR TEENSY",
  "IDLE",
  "PLAY",
  "UNDEFINED"
};

#endif

#ifndef STATEMACHINE_H
#define STATEMACHINE_H

enum states {
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

static String stateStrings[] = {
  "INCOMING SERIAL",
  "RESET",
  "WAIT FOR MOTOR INIT",
  "IDLE",
  "PLAY",
  "HARDWARE TEST",
  "ERROR",
  "UNDEFINED"
};

#endif

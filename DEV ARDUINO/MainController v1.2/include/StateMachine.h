#ifndef STATEMACHINE_H
#define STATEMACHINE_H

enum states {
  __INCOMING_SERIAL,
  __WAIT_FOR_TEENSY,
  __IDLE,
  __PLAY,
  __HARDWARE_TEST,
  __ERROR,
  __FEIERABEND,
  __UNDEFINED
};
extern states state;

static String stateStrings[] = {
  "INCOMING SERIAL",
  "WAIT FOR TEENSY",
  "IDLE",
  "PLAY",
  "HARDWARE TEST",
  "ERROR",
  "FEIERABEND",
  "UNDEFINED"
};

#endif

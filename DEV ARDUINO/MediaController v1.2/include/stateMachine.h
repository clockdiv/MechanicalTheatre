#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <Arduino.h>

enum states {
  __INCOMING_SERIAL,
  __IDLE,
  __PLAY,
  __ERROR,
  __UNDEFINED
};
extern states state;

static String stateStrings[] = {
  "INCOMING SERIAL",
  "IDLE",
  "PLAY",
  "ERROR",
  "UNDEFINED"
};

#endif

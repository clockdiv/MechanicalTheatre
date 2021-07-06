#ifndef STATEMACHINE_H
#define STATEMACHINE_H

enum states {
  __INCOMING_SERIAL,
  __RESET,
  __POST_RESET,
  __IDLE,
  __PLAY
};
extern states state;

static String stateStrings[] = {
  "INCOMING SERIAL",
  "RESET",
  "POST RESET",
  "IDLE",
  "PLAY"
};

#endif

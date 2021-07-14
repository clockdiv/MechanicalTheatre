#ifndef CONFIGURATIONS4_H
#define CONFIGURATIONS4_H
#include <Arduino.h>
#include "Pins.h"

// Number of stepper motors
#define UNIT_COUNT 4                

String filenames[UNIT_COUNT] = { "CURVE0.DAT", 
                                 "CURVE1.DAT",
                                 "CURVE2.DAT",
                                 "CURVE3.DAT" };

String motornames[UNIT_COUNT] = {   "Ufo_X-Axis", 
                                    "Ufo_Y-Axis", 
                                    "Schwaene_schwimmen", 
                                    "Schwaene_tauchen"};

const uint8_t steppersConfig[UNIT_COUNT][4] = {  // Stepper-Motor Pins
  {STEPPER_1_ENDSWITCH_PIN,  STEPPER_1_DIRECTION_PIN,  STEPPER_1_PULSE_PIN,  STEPPER_1_IS_INVERTED},     // End-Switch; Direction; Pulse; DirectionInvert
  {STEPPER_2_ENDSWITCH_PIN,  STEPPER_2_DIRECTION_PIN,  STEPPER_2_PULSE_PIN,  STEPPER_2_IS_INVERTED},
  {STEPPER_3_ENDSWITCH_PIN,  STEPPER_3_DIRECTION_PIN,  STEPPER_3_PULSE_PIN,  STEPPER_3_IS_INVERTED},     // End-Switch; Direction; Pulse; DirectionInvert
  {STEPPER_4_ENDSWITCH_PIN,  STEPPER_4_DIRECTION_PIN,  STEPPER_4_PULSE_PIN,  STEPPER_4_IS_INVERTED}
};

#endif
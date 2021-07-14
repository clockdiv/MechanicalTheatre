#ifndef CONFIGURATIONS2_H
#define CONFIGURATIONS2_H
#include <Arduino.h>
#include "Pins.h"

// Number of stepper motors
#define UNIT_COUNT 2                

String filenames[UNIT_COUNT] = { "CURVE0.DAT", 
                                 "CURVE1.DAT" };

String motornames[UNIT_COUNT] = {   "Ufo_X-Axis", 
                                    "Ufo_Y-Axis"};

const uint8_t steppersPinConfig[UNIT_COUNT][4] = {  // Stepper-Motor Pins
  {STEPPER_1_ENDSWITCH_PIN,  STEPPER_1_DIRECTION_PIN,  STEPPER_1_PULSE_PIN,  STEPPER_1_IS_INVERTED },     // End-Switch; Direction; Pulse; DirectionInvert
  {STEPPER_2_ENDSWITCH_PIN,  STEPPER_2_DIRECTION_PIN,  STEPPER_2_PULSE_PIN,  STEPPER_2_IS_INVERTED }
};

const uint16_t steppersInitConfig[UNIT_COUNT][2] = {
  {STEPPER_1_INIT_POS, STEPPER_1_RESET_SPEED },
  {STEPPER_2_INIT_POS, STEPPER_2_RESET_SPEED }
};

#endif
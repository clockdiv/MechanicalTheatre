#ifndef CONFIGURATIONS_H
#define CONFIGURATIONS_H
#include <Arduino.h>
#include "Pins.h"

// Number of stepper motors
#define UNIT_COUNT 4                

String filenames[UNIT_COUNT] = { "/CURVE11.DAT", 
                                 "/CURVE12.DAT",
                                 "/CURVE13.DAT",
                                 "/CURVE14.DAT"};

String motornames[UNIT_COUNT] = {   "Vorhang", 
                                    "Magd", 
                                    "Schild", 
                                    "Buehne"};

const uint8_t steppersPinConfig[UNIT_COUNT][4] = {  // Stepper-Motor Pins
  {STEPPER_11_ENDSWITCH_PIN,  STEPPER_11_DIRECTION_PIN,  STEPPER_11_PULSE_PIN,  STEPPER_11_IS_INVERTED},     // End-Switch; Direction; Pulse; DirectionInvert
  {STEPPER_12_ENDSWITCH_PIN,  STEPPER_12_DIRECTION_PIN,  STEPPER_12_PULSE_PIN,  STEPPER_12_IS_INVERTED},
  {STEPPER_13_ENDSWITCH_PIN,  STEPPER_13_DIRECTION_PIN,  STEPPER_13_PULSE_PIN,  STEPPER_13_IS_INVERTED},     // End-Switch; Direction; Pulse; DirectionInvert
  {STEPPER_14_ENDSWITCH_PIN,  STEPPER_14_DIRECTION_PIN,  STEPPER_14_PULSE_PIN,  STEPPER_14_IS_INVERTED}
};

const uint16_t steppersInitConfig[UNIT_COUNT][2] = {
  {STEPPER_11_INIT_POS, STEPPER_11_RESET_SPEED },
  {STEPPER_12_INIT_POS, STEPPER_12_RESET_SPEED },
  {STEPPER_13_INIT_POS, STEPPER_13_RESET_SPEED },
  {STEPPER_14_INIT_POS, STEPPER_14_RESET_SPEED } 
};


#endif
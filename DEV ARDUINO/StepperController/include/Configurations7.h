#ifndef CONFIGURATIONS7_H
#define CONFIGURATIONS7_H
#include <Arduino.h>
#include "Pins.h"

// Number of stepper motors
#define UNIT_COUNT 7              

String filenames[UNIT_COUNT] = { "CURVE0.DAT", 
                                 "CURVE1.DAT",
                                 "CURVE2.DAT",
                                 "CURVE3.DAT",
                                 "CURVE4.DAT",
                                 "CURVE5.DAT",
                                 "CURVE6.DAT" };

String motornames[UNIT_COUNT] = {   "Ufo_X-Axis", 
                                    "Ufo_Y-Axis", 
                                    "Schwaene_schwimmen", 
                                    "Schwaene_tauchen", 
                                    "Pferde_1",
                                    "Vorhang", 
                                    "Magd" };

const uint8_t steppersPinConfig[UNIT_COUNT][5] = {  // Stepper-Motor Pins
  {STEPPER_1_ENDSWITCH_PIN,  STEPPER_1_DIRECTION_PIN,  STEPPER_1_PULSE_PIN,  STEPPER_1_IS_INVERTED },     // End-Switch; Direction; Pulse; DirectionInvert
  {STEPPER_2_ENDSWITCH_PIN,  STEPPER_2_DIRECTION_PIN,  STEPPER_2_PULSE_PIN,  STEPPER_2_IS_INVERTED },
  {STEPPER_3_ENDSWITCH_PIN,  STEPPER_3_DIRECTION_PIN,  STEPPER_3_PULSE_PIN,  STEPPER_3_IS_INVERTED },
  {STEPPER_4_ENDSWITCH_PIN,  STEPPER_4_DIRECTION_PIN,  STEPPER_4_PULSE_PIN,  STEPPER_4_IS_INVERTED },
  {STEPPER_5_ENDSWITCH_PIN,  STEPPER_5_DIRECTION_PIN,  STEPPER_5_PULSE_PIN,  STEPPER_5_IS_INVERTED },

  {STEPPER_9_ENDSWITCH_PIN,  STEPPER_9_DIRECTION_PIN,  STEPPER_9_PULSE_PIN,  STEPPER_9_IS_INVERTED },
  {STEPPER_10_ENDSWITCH_PIN, STEPPER_10_DIRECTION_PIN, STEPPER_10_PULSE_PIN, STEPPER_10_IS_INVERTED },
  
};

const uint16_t steppersInitConfig[UNIT_COUNT][2] = {
  {STEPPER_1_INIT_POS, STEPPER_1_RESET_SPEED },
  {STEPPER_2_INIT_POS, STEPPER_2_RESET_SPEED },
  {STEPPER_3_INIT_POS, STEPPER_3_RESET_SPEED },
  {STEPPER_4_INIT_POS, STEPPER_4_RESET_SPEED },
  {STEPPER_5_INIT_POS, STEPPER_5_RESET_SPEED },

  {STEPPER_9_INIT_POS, STEPPER_9_RESET_SPEED },
  {STEPPER_10_INIT_POS, STEPPER_10_RESET_SPEED }
};


#endif
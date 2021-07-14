#ifndef CONFIGURATIONS10_H
#define CONFIGURATIONS10_H
#include <Arduino.h>
#include "Pins.h"

// Number of stepper motors
#define UNIT_COUNT 10                

String filenames[UNIT_COUNT] = { "CURVE0.DAT", 
                                 "CURVE1.DAT",
                                 "CURVE2.DAT",
                                 "CURVE3.DAT",
                                 "CURVE4.DAT",
                                 "CURVE5.DAT",
                                 "CURVE6.DAT",
                                 "CURVE7.DAT",
                                 "CURVE8.DAT",
                                 "CURVE9.DAT" };

String motornames[UNIT_COUNT] = {   "Ufo_X-Axis", 
                                    "Ufo_Y-Axis", 
                                    "Schwaene_schwimmen", 
                                    "Schwaene_tauchen", 
                                    "Pferde_1", 
                                    "Pferde_2",
                                    "Reiter_1", 
                                    "Reiter_2",
                                    "Halbkugel", 
                                    "Luftpumpe" };

const uint8_t steppersConfig[UNIT_COUNT][4] = {  // Stepper-Motor Pins
  {STEPPER_1_ENDSWITCH_PIN,  STEPPER_1_DIRECTION_PIN,  STEPPER_1_PULSE_PIN,  STEPPER_1_IS_INVERTED},     // End-Switch; Direction; Pulse; DirectionInvert
  {STEPPER_2_ENDSWITCH_PIN,  STEPPER_2_DIRECTION_PIN,  STEPPER_2_PULSE_PIN,  STEPPER_2_IS_INVERTED},
  {STEPPER_3_ENDSWITCH_PIN,  STEPPER_3_DIRECTION_PIN,  STEPPER_3_PULSE_PIN,  STEPPER_3_IS_INVERTED},     // End-Switch; Direction; Pulse; DirectionInvert
  {STEPPER_4_ENDSWITCH_PIN,  STEPPER_4_DIRECTION_PIN,  STEPPER_4_PULSE_PIN,  STEPPER_4_IS_INVERTED},
  {STEPPER_5_ENDSWITCH_PIN,  STEPPER_5_DIRECTION_PIN,  STEPPER_5_PULSE_PIN,  STEPPER_5_IS_INVERTED},     // End-Switch; Direction; Pulse; DirectionInvert
  {STEPPER_6_ENDSWITCH_PIN,  STEPPER_6_DIRECTION_PIN,  STEPPER_6_PULSE_PIN,  STEPPER_6_IS_INVERTED},
  {STEPPER_7_ENDSWITCH_PIN,  STEPPER_7_DIRECTION_PIN,  STEPPER_7_PULSE_PIN,  STEPPER_7_IS_INVERTED},     // End-Switch; Direction; Pulse; DirectionInvert
  {STEPPER_8_ENDSWITCH_PIN,  STEPPER_8_DIRECTION_PIN,  STEPPER_8_PULSE_PIN,  STEPPER_8_IS_INVERTED},
  {STEPPER_9_ENDSWITCH_PIN,  STEPPER_9_DIRECTION_PIN,  STEPPER_9_PULSE_PIN,  STEPPER_9_IS_INVERTED},     // End-Switch; Direction; Pulse; DirectionInvert
  {STEPPER_10_ENDSWITCH_PIN, STEPPER_10_DIRECTION_PIN, STEPPER_10_PULSE_PIN, STEPPER_10_IS_INVERTED}
};

#endif
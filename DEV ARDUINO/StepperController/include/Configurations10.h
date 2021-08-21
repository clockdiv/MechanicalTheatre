#ifndef CONFIGURATIONS10_H
#define CONFIGURATIONS10_H
#include <Arduino.h>
#include "Pins.h"

// Number of stepper motors
#define UNIT_COUNT 10

String filenames[UNIT_COUNT] = {"CURVE0.DAT",
                                "CURVE1.DAT",
                                "CURVE2.DAT",
                                "CURVE3.DAT",
                                "CURVE4.DAT",
                                "CURVE5.DAT",
                                "CURVE6.DAT",
                                "CURVE7.DAT",
                                "CURVE8.DAT",
                                "CURVE9.DAT"};

String motornames[UNIT_COUNT] = {"Ufo_X-Axis",
                                 "Ufo_Y-Axis",
                                 "Schwaene_schwimmen",
                                 "Schwaene_tauchen",
                                 "Pferde_1",
                                 "Pferde_2",
                                 "Reiter_1",
                                 "Reiter_2",
                                 "Luftpumpe",
                                 "Halbkugel"};

const int8_t steppersResetDependencies[UNIT_COUNT] = {-1,  // Ufo_X-Axis
                                                      0,   // Ufo_Y-Axis          // Y-Axis waits for X-Axis to reset
                                                      -1,  // Schwaene_schwimmen
                                                      -1,  // Schwaene_tauchen
                                                      -1,  // Pferde_1
                                                      -1,  // Pferde_2
                                                      -1,  // Reiter_1
                                                      -1,  // Reiter_2
                                                      -1,  // Luftpumpe
                                                      -1}; // Halbkugel

const uint8_t steppersPinConfig[UNIT_COUNT][4] = {                                                  // Stepper-Motor Pins
    {STEPPER_1_ENDSWITCH_PIN, STEPPER_1_DIRECTION_PIN, STEPPER_1_PULSE_PIN, STEPPER_1_IS_INVERTED}, // End-Switch; Direction; Pulse; DirectionInvert
    {STEPPER_2_ENDSWITCH_PIN, STEPPER_2_DIRECTION_PIN, STEPPER_2_PULSE_PIN, STEPPER_2_IS_INVERTED},
    {STEPPER_3_ENDSWITCH_PIN, STEPPER_3_DIRECTION_PIN, STEPPER_3_PULSE_PIN, STEPPER_3_IS_INVERTED}, // End-Switch; Direction; Pulse; DirectionInvert
    {STEPPER_4_ENDSWITCH_PIN, STEPPER_4_DIRECTION_PIN, STEPPER_4_PULSE_PIN, STEPPER_4_IS_INVERTED},
    {STEPPER_5_ENDSWITCH_PIN, STEPPER_5_DIRECTION_PIN, STEPPER_5_PULSE_PIN, STEPPER_5_IS_INVERTED}, // End-Switch; Direction; Pulse; DirectionInvert
    {STEPPER_6_ENDSWITCH_PIN, STEPPER_6_DIRECTION_PIN, STEPPER_6_PULSE_PIN, STEPPER_6_IS_INVERTED},
    {STEPPER_7_ENDSWITCH_PIN, STEPPER_7_DIRECTION_PIN, STEPPER_7_PULSE_PIN, STEPPER_7_IS_INVERTED}, // End-Switch; Direction; Pulse; DirectionInvert
    {STEPPER_8_ENDSWITCH_PIN, STEPPER_8_DIRECTION_PIN, STEPPER_8_PULSE_PIN, STEPPER_8_IS_INVERTED},
    {STEPPER_9_ENDSWITCH_PIN, STEPPER_9_DIRECTION_PIN, STEPPER_9_PULSE_PIN, STEPPER_9_IS_INVERTED}, // End-Switch; Direction; Pulse; DirectionInvert
    {STEPPER_10_ENDSWITCH_PIN, STEPPER_10_DIRECTION_PIN, STEPPER_10_PULSE_PIN, STEPPER_10_IS_INVERTED}};

const uint16_t steppersInitConfig[UNIT_COUNT][2] = {
    {STEPPER_1_INIT_POS, STEPPER_1_RESET_SPEED},
    {STEPPER_2_INIT_POS, STEPPER_2_RESET_SPEED},
    {STEPPER_3_INIT_POS, STEPPER_3_RESET_SPEED},
    {STEPPER_4_INIT_POS, STEPPER_4_RESET_SPEED},
    {STEPPER_5_INIT_POS, STEPPER_5_RESET_SPEED},
    {STEPPER_6_INIT_POS, STEPPER_6_RESET_SPEED},
    {STEPPER_7_INIT_POS, STEPPER_7_RESET_SPEED},
    {STEPPER_8_INIT_POS, STEPPER_8_RESET_SPEED},
    {STEPPER_9_INIT_POS, STEPPER_9_RESET_SPEED},
    {STEPPER_10_INIT_POS, STEPPER_10_RESET_SPEED}};

#endif
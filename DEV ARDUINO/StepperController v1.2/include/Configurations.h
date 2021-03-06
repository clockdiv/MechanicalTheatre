#ifndef CONFIGURATIONS_H
#define CONFIGURATIONS_H

#include <Arduino.h>
#include "Pins.h"

#define UNIT_COUNT 12   // Number of stepper motors
#define MAX_FRAMES 6000 // maximum number of frames

// Ufo X-Axis
#define STEPPER_1_INIT_POS 500
#define STEPPER_1_RESET_SPEED 1500
#define STEPPER_1_IS_INVERTED 0

// Ufo Y-Axis
#define STEPPER_2_INIT_POS 500
#define STEPPER_2_RESET_SPEED 3000
#define STEPPER_2_IS_INVERTED 1

// Schwäne schwimmen
#define STEPPER_3_INIT_POS 500
#define STEPPER_3_RESET_SPEED 1500
#define STEPPER_3_IS_INVERTED 0

// Schwäne tauchen
#define STEPPER_4_INIT_POS 500
#define STEPPER_4_RESET_SPEED 500
#define STEPPER_4_IS_INVERTED 1

// Pferde 1
#define STEPPER_5_INIT_POS 5000
#define STEPPER_5_RESET_SPEED 2500
#define STEPPER_5_IS_INVERTED 1

// Pferde 2
#define STEPPER_6_INIT_POS 500
#define STEPPER_6_RESET_SPEED 2500
#define STEPPER_6_IS_INVERTED 0

// Reiter 1
#define STEPPER_7_INIT_POS 150
#define STEPPER_7_RESET_SPEED 500
#define STEPPER_7_IS_INVERTED 0 // unknown yet

// Reiter 2
#define STEPPER_8_INIT_POS 150
#define STEPPER_8_RESET_SPEED 500
#define STEPPER_8_IS_INVERTED 0 // unknown yet

// Luftpumpe
#define STEPPER_9_INIT_POS 100
#define STEPPER_9_RESET_SPEED 500
#define STEPPER_9_IS_INVERTED 1

// Halbkugel
#define STEPPER_10_INIT_POS 600
#define STEPPER_10_RESET_SPEED 2000
#define STEPPER_10_IS_INVERTED 0

// Vorhang
#define STEPPER_11_INIT_POS 100
#define STEPPER_11_RESET_SPEED 1500
#define STEPPER_11_IS_INVERTED 1 // unknown yet

// Magd
#define STEPPER_12_INIT_POS 30 // 20 was good until we switch the power supply off?
#define STEPPER_12_RESET_SPEED 100
#define STEPPER_12_IS_INVERTED 1 // unknown yet

const String filenames[UNIT_COUNT] = {"CURVE0.DAT",
                                      "CURVE1.DAT",
                                      "CURVE2.DAT",
                                      "CURVE3.DAT",
                                      "CURVE4.DAT",
                                      "CURVE5.DAT",
                                      "CURVE6.DAT",
                                      "CURVE7.DAT",
                                      "CURVE8.DAT",
                                      "CURVE9.DAT",
                                      "CURVE10.DAT",
                                      "CURVE11.DAT"};

const String motornames[UNIT_COUNT] = {"Ufo_X-Axis",
                                       "Ufo_Y-Axis",
                                       "Schwaene_schwimmen",
                                       "Schwaene_tauchen",
                                       "Pferde_1",
                                       "Pferde_2",
                                       "Reiter_1",
                                       "Reiter_2",
                                       "Luftpumpe",
                                       "Halbkugel",
                                       "Vorhang",
                                       "Magd"};

const int8_t steppersResetDependencies[UNIT_COUNT] = {-1,  // Ufo_X-Axis
                                                      0,   // Ufo_Y-Axis          // Y-Axis waits for X-Axis to reset
                                                      3,   // Schwaene_schwimmen
                                                      -1,  // Schwaene_tauchen
                                                      -1,  // Pferde_1
                                                      -1,  // Pferde_2
                                                      -1,  // Reiter_1
                                                      -1,  // Reiter_2
                                                      -1,  // Luftpumpe
                                                      -1,  // Halbkugel
                                                      -1,  // Vorhang
                                                      -1}; // Magd

const int8_t steppersEmergencyStopDependencies[UNIT_COUNT] = {1,   // Ufo_X-Axis checks if Ufo_Y-Axis is okay
                                                              0,   // Ufo_Y-Axis checks if Ufo_X-Axis is okay
                                                              3,   // Schwaene_schwimmen checks if Schwaene_tauchen is okay
                                                              2,   // Schwaene_tauchen
                                                              5,   // Pferde_1
                                                              4,   // Pferde_2
                                                              -1,  // Reiter_1
                                                              -1,  // Reiter_2
                                                              -1,  // Luftpumpe
                                                              -1,  // Halbkugel
                                                              -1,  // Vorhang
                                                              -1}; // Magd


// const int8_t steppersInvertedEndswitch[UNIT_COUNT] = {1,  // Ufo_X-Axis
//                                                       0,  // Ufo_Y-Axis
//                                                       1,  // Schwaene_schwimmen
//                                                       1,  // Schwaene_tauchen
//                                                       1,  // Pferde_1
//                                                       1,  // Pferde_2
//                                                       1,  // Reiter_1
//                                                       1,  // Reiter_2
//                                                       0,  // Luftpumpe
//                                                       0,  // Halbkugel
//                                                       0,  // Vorhang
//                                                       0 };// Magd

const int8_t steppersInvertedEndswitch[UNIT_COUNT] = {1,  // Ufo_X-Axis
                                                      1,  // Ufo_Y-Axis
                                                      1,  // Schwaene_schwimmen
                                                      1,  // Schwaene_tauchen
                                                      1,  // Pferde_1
                                                      1,  // Pferde_2
                                                      1,  // Reiter_1
                                                      1,  // Reiter_2
                                                      1,  // Luftpumpe
                                                      1,  // Halbkugel
                                                      1,  // Vorhang
                                                      1}; // Magd

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
    {STEPPER_10_ENDSWITCH_PIN, STEPPER_10_DIRECTION_PIN, STEPPER_10_PULSE_PIN, STEPPER_10_IS_INVERTED},
    {STEPPER_11_ENDSWITCH_PIN, STEPPER_11_DIRECTION_PIN, STEPPER_11_PULSE_PIN, STEPPER_11_IS_INVERTED}, // End-Switch; Direction; Pulse; DirectionInvert
    {STEPPER_12_ENDSWITCH_PIN, STEPPER_12_DIRECTION_PIN, STEPPER_12_PULSE_PIN, STEPPER_12_IS_INVERTED}};

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
    {STEPPER_10_INIT_POS, STEPPER_10_RESET_SPEED},
    {STEPPER_11_INIT_POS, STEPPER_11_RESET_SPEED},
    {STEPPER_12_INIT_POS, STEPPER_12_RESET_SPEED}};

// Codes for LED:
// 101-199: info messages
// 201-299: error messages
#define ERR_SD_FAILED 201
#define ERR_READING_FILES 202
#define ERR_UNDEFINED 299

#endif
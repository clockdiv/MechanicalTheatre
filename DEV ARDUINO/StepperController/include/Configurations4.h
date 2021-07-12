#ifndef CONFIGURATIONS4_H
#define CONFIGURATIONS4_H
#include <Arduino.h>

// Number of stepper motors
#define UNIT_COUNT 4                

// external hardware
#define PIN_EXT_LED             13
#define PIN_BUZZER              23
#define PIN_ENDSWITCH_GLOBAL    14

// Ufo X-Axis
#define STEPPER_1_ENDSWITCH_PIN 33
#define STEPPER_1_DIRECTION_PIN 34
#define STEPPER_1_PULSE_PIN     35
#define STEPPER_1_IS_INVERTED   0

// Ufo Y-Axis
#define STEPPER_2_ENDSWITCH_PIN 36
#define STEPPER_2_DIRECTION_PIN 37
#define STEPPER_2_PULSE_PIN     38
#define STEPPER_2_IS_INVERTED   1

// Schwäne schwimmen
#define STEPPER_3_ENDSWITCH_PIN 39
#define STEPPER_3_DIRECTION_PIN 40
#define STEPPER_3_PULSE_PIN     41
#define STEPPER_3_IS_INVERTED   0   // unknown yet

// Schwäne tauchen
#define STEPPER_4_ENDSWITCH_PIN 15
#define STEPPER_4_DIRECTION_PIN 16
#define STEPPER_4_PULSE_PIN     17
#define STEPPER_4_IS_INVERTED   1   // unknown yet

// Halbkugeln
#define STEPPER_5_ENDSWITCH_PIN 20
#define STEPPER_5_DIRECTION_PIN 21
#define STEPPER_5_PULSE_PIN     22
#define STEPPER_5_IS_INVERTED   0   // unknown yet

// Pferdegruppe 1
#define STEPPER_6_ENDSWITCH_PIN 9
#define STEPPER_6_DIRECTION_PIN 8
#define STEPPER_6_PULSE_PIN     7
#define STEPPER_6_IS_INVERTED   0   // unknown yet

// Pferdegruppe 2
#define STEPPER_7_ENDSWITCH_PIN 12
#define STEPPER_7_DIRECTION_PIN 11
#define STEPPER_7_PULSE_PIN     10
#define STEPPER_7_IS_INVERTED   0   // unknown yet

// Reitergruppe 1
#define STEPPER_8_ENDSWITCH_PIN 26
#define STEPPER_8_DIRECTION_PIN 25
#define STEPPER_8_PULSE_PIN     24
#define STEPPER_8_IS_INVERTED   0   // unknown yet

// Reitergruppe 2
#define STEPPER_9_ENDSWITCH_PIN 29
#define STEPPER_9_DIRECTION_PIN 28
#define STEPPER_9_PULSE_PIN     27
#define STEPPER_9_IS_INVERTED   0   // unknown yet

// Männer an Luftpumpe
#define STEPPER_10_ENDSWITCH_PIN 32
#define STEPPER_10_DIRECTION_PIN 31
#define STEPPER_10_PULSE_PIN     30
#define STEPPER_10_IS_INVERTED   0   // unknown yet

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
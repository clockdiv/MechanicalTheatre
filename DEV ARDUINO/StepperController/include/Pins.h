#ifndef PINS_H
#define PINS_H


// external hardware
#define PIN_EXT_LED             13
#define PIN_BUZZER              23
#define PIN_ENDSWITCH_GLOBAL    14



// Ufo X-Axis
#define STEPPER_1_ENDSWITCH_PIN 33
#define STEPPER_1_DIRECTION_PIN 34
#define STEPPER_1_PULSE_PIN     35
#define STEPPER_1_IS_INVERTED   0

#define STEPPER_1_INIT_POS      500
#define STEPPER_1_RESET_SPEED   1500



// Ufo Y-Axis
#define STEPPER_2_ENDSWITCH_PIN 36
#define STEPPER_2_DIRECTION_PIN 37
#define STEPPER_2_PULSE_PIN     38
#define STEPPER_2_IS_INVERTED   1

#define STEPPER_2_INIT_POS      500
#define STEPPER_2_RESET_SPEED   1500



// Schwäne schwimmen
#define STEPPER_3_ENDSWITCH_PIN 39
#define STEPPER_3_DIRECTION_PIN 40
#define STEPPER_3_PULSE_PIN     41
#define STEPPER_3_IS_INVERTED   0 

#define STEPPER_3_INIT_POS      500
#define STEPPER_3_RESET_SPEED   1500



// Schwäne tauchen
#define STEPPER_4_ENDSWITCH_PIN 15
#define STEPPER_4_DIRECTION_PIN 16
#define STEPPER_4_PULSE_PIN     17
#define STEPPER_4_IS_INVERTED   1 

#define STEPPER_4_INIT_POS      500
#define STEPPER_4_RESET_SPEED   500



// Pferde 1
#define STEPPER_5_ENDSWITCH_PIN 20
#define STEPPER_5_DIRECTION_PIN 21
#define STEPPER_5_PULSE_PIN     22
#define STEPPER_5_IS_INVERTED   0   // unknown yet

#define STEPPER_5_INIT_POS      500
#define STEPPER_5_RESET_SPEED   500



// Pferde 2
#define STEPPER_6_ENDSWITCH_PIN 9
#define STEPPER_6_DIRECTION_PIN 8
#define STEPPER_6_PULSE_PIN     7
#define STEPPER_6_IS_INVERTED   0   // unknown yet

#define STEPPER_6_INIT_POS      500
#define STEPPER_6_RESET_SPEED   500



// Reiter 1
#define STEPPER_7_ENDSWITCH_PIN 12
#define STEPPER_7_DIRECTION_PIN 11
#define STEPPER_7_PULSE_PIN     10
#define STEPPER_7_IS_INVERTED   0   // unknown yet

#define STEPPER_7_INIT_POS      500
#define STEPPER_7_RESET_SPEED   500



// Reiter 2
#define STEPPER_8_ENDSWITCH_PIN 26
#define STEPPER_8_DIRECTION_PIN 25
#define STEPPER_8_PULSE_PIN     24
#define STEPPER_8_IS_INVERTED   0   // unknown yet

#define STEPPER_8_INIT_POS      500
#define STEPPER_8_RESET_SPEED   500



// Vorhang
#define STEPPER_9_ENDSWITCH_PIN 29
#define STEPPER_9_DIRECTION_PIN 28
#define STEPPER_9_PULSE_PIN     27
#define STEPPER_9_IS_INVERTED   1

#define STEPPER_9_INIT_POS      500
#define STEPPER_9_RESET_SPEED   500



// Magd
#define STEPPER_10_ENDSWITCH_PIN 32
#define STEPPER_10_DIRECTION_PIN 31
#define STEPPER_10_PULSE_PIN     30
#define STEPPER_10_IS_INVERTED   1

#define STEPPER_10_INIT_POS      100
#define STEPPER_10_RESET_SPEED   100

#endif
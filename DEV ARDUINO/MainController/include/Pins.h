#ifndef PINS_H
#define PINS_H

// Pin Configurations for ESP32 "Main Controller"

// external hardware
#define PIN_EXT_LED             0
#define PIN_BUZZER              23
#define PIN_ENDSWITCH_GLOBAL    34
#define PIN_COINSLOT_SENSOR     35
#define PIN_RELAIS_COINSLOT     2
#define PIN_RELAIS_POWERSUPPLIES 15
#define PIN_LEDWALL_TRIGGER 13




// Vorhang
#define STEPPER_11_ENDSWITCH_PIN 4
#define STEPPER_11_DIRECTION_PIN 16
#define STEPPER_11_PULSE_PIN     17
#define STEPPER_11_IS_INVERTED   1       // unknown yet

#define STEPPER_11_INIT_POS      500
#define STEPPER_11_RESET_SPEED   1500



// Magd
#define STEPPER_12_ENDSWITCH_PIN 5
#define STEPPER_12_DIRECTION_PIN 18
#define STEPPER_12_PULSE_PIN     19
#define STEPPER_12_IS_INVERTED   1       // unknown yet

#define STEPPER_12_INIT_POS      30         // 20 was good until we switch the power supply off?
#define STEPPER_12_RESET_SPEED   100



// Out-Of-Order Schild
#define STEPPER_13_ENDSWITCH_PIN 25
#define STEPPER_13_DIRECTION_PIN 33
#define STEPPER_13_PULSE_PIN     32
#define STEPPER_13_IS_INVERTED   0       // unknown yet 

#define STEPPER_13_INIT_POS      500
#define STEPPER_13_RESET_SPEED   500



// Bühnendrehung
#define STEPPER_14_ENDSWITCH_PIN 14
#define STEPPER_14_DIRECTION_PIN 27
#define STEPPER_14_PULSE_PIN     26
#define STEPPER_14_IS_INVERTED   0       // unknown yet

#define STEPPER_14_INIT_POS      500
#define STEPPER_14_RESET_SPEED   500


#endif
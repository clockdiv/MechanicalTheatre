#ifndef PINS_H
#define PINS_H

// Pin Configurations for ESP32 "Main Controller"

// outputs
#define PIN_EXT_LED                 2
#define PIN_BUZZER                  23
#define PIN_RELAIS_COINSLOT         16
#define PIN_RELAIS_POWERSUPPLIES    4
#define PIN_MEDIACONTROLLER_TRIGGER 13

// inputs
#define PIN_ENDSWITCH_GLOBAL    34
#define PIN_COINSLOT_SENSOR     35
#define PIN_BTN_A               26
#define PIN_BTN_B               27
#define PIN_DIPSWITCH_1         17 
#define PIN_DIPSWITCH_2         5
#define PIN_DIPSWITCH_3         18 
#define PIN_DIPSWITCH_4         19 

// stepper motor Out-Of-Order Schild
#define STEPPER_13_ENDSWITCH_PIN 25
#define STEPPER_13_DIRECTION_PIN 33
#define STEPPER_13_PULSE_PIN     32

#endif
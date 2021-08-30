#ifndef CONFIGURATIONS_H
#define CONFIGURATIONS_H
#include <Arduino.h>
#include "Pins.h"

#define TEENSY_I2C_ADDR 0x10

#define STEPPER_13_INIT_POS      500
#define STEPPER_13_RESET_SPEED   500

#define DEBOUNCE_TIME             25

// Signals for the Buzzer:

// 100-199: info messages
// 200-299: error messages
#define BUZZER_TEST         100
#define BUZZER_POWER_ON     101
#define BUZZER_START_SHOW   102

#endif
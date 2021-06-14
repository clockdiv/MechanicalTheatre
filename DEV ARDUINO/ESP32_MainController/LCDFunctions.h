#ifndef LCDFunctions_h
#define LCDFunctions_h

#include <LiquidCrystal_PCF8574.h>

namespace LCDFunctions {
void init_display();
void clear_display();
void print_display(String s, uint8_t x = 0, uint8_t y = 0);
}

#endif

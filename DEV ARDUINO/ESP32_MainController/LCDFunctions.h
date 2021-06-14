#ifndef CommonFunctions_h
#define CommonFunctions_h

#include <LiquidCrystal_PCF8574.h>

namespace LCDFunctions {
void init_display();
void clear_display();
void print(String s, uint8_t x = 0, uint8_t y = 0);
}
#endif

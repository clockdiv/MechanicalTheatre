#include "LCDFunctions.h"

namespace LCDFunctions {

// external hardware
LiquidCrystal_PCF8574 lcd(0x27);        // set the LCD address to 0x27

/* ------------------------------------ */
/* Initializes the Display   */
/* ------------------------------------ */
void init_display() {
  lcd.begin(20, 4); // initialize the lcd
  lcd.setBacklight(255);
  clear_display();
  lcd.print("Hello World -");
  lcd.setCursor(0, 1);
  lcd.print("Hello Magdeburg!");
}

/* ------------------------------------ */
/* Clears the Display   */
/* ------------------------------------ */
void clear_display() {
  lcd.home();
  lcd.clear();
  lcd.setCursor(0, 0);
}

void print_display(String s, uint8_t x, uint8_t y) {
  lcd.setCursor(x, y);
  lcd.print(s);
}
}

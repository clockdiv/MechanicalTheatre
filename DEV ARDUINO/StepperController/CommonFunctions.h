#ifndef CommonFunctions_h
#define CommonFunctions_h

/* ------------------------------------ */
/* beep the BUZZER n times               */
/* ------------------------------------ */
void buzzer_beep(uint8_t _i = 3, uint16_t duration = 50) {
  for (int i = 0; i < _i; i++) {
    digitalWrite(PIN_BUZZER, HIGH);
    delay(duration);
    digitalWrite(PIN_BUZZER, LOW);
    delay(duration);
  }
}


#endif

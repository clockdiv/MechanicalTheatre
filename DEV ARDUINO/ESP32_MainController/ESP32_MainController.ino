#include <LiquidCrystal_PCF8574.h>
#include <InputDebounce.h>

#define PIN_PROX_SENSOR 15
#define PIN_RELAIS 4
#define PIN_BUZZER 2

#define BUTTON_DEBOUNCE_DELAY   20   // [ms]

// external hardware
LiquidCrystal_PCF8574 lcd(0x27);        // set the LCD address to 0x27

bool relais_state;
static InputDebounce coinSlotInput;

volatile uint16_t counter;

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


void coinSlot_pressedCallback(uint8_t pinIn) {
  relais_state = !relais_state;
  digitalWrite(PIN_RELAIS, relais_state);

  Serial.println("high");
  Serial.println(pinIn);
  buzzer_beep(5, 50);
}

void coinSlot_releasedCallback(uint8_t pinIn) {}
void coinSlot_pressedDurationCallback(uint8_t pinIn, unsigned long duration) {}
void coinSlot_releasedDurationCallback(uint8_t pinIn, unsigned long duration) {}

void coinSlotISR() {
  counter++;
}



void setup() {
  Serial.begin(115200);

  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_RELAIS, OUTPUT);

  coinSlotInput.registerCallbacks(coinSlot_pressedCallback, coinSlot_releasedCallback, coinSlot_pressedDurationCallback, coinSlot_releasedDurationCallback);
  coinSlotInput.setup(PIN_PROX_SENSOR, BUTTON_DEBOUNCE_DELAY, InputDebounce::PIM_INT_PULL_UP_RES);
//  attachInterrupt(PIN_PROX_SENSOR, coinSlotISR, RISING);

  relais_state = false;
}

void loop() {

  unsigned long now = millis();

  coinSlotInput.process(now); // callbacks called in context of this function

//    delay(1000);
//  Serial.println(counter);

}

#include <LiquidCrystal_PCF8574.h>
#include <InputDebounce.h> // InputDebounce Library by Mario Ban Version 1.6

#define PIN_PROX_SENSOR     35
#define PIN_RELAIS_COINSLOT 2
#define PIN_RELAIS_5V24V    15
#define PIN_BUZZER          23

#define BUTTON_DEBOUNCE_DELAY   20   // [ms]

// external hardware
LiquidCrystal_PCF8574 lcd(0x27);        // set the LCD address to 0x27

bool relais_state;

static InputDebounce coinSlotInput;
volatile uint16_t counter;

// Timing
unsigned long currentMillis;

// State Machine
enum states {STARTUP, WAIT, START_SHOW, RUN};
String PROGMEM stateStrings[] = {"STARTUP", "WAIT", "START_SHOW", "RUN"};
uint8_t state = STARTUP;
uint8_t state_old = 255;
void smRun();

// Function Declarations
void buzzer_beep(uint8_t _i = 3, uint16_t duration = 50);

// Debounce-Libray Callbacks
void coinSlot_pressedCallback(uint8_t pinIn) { Serial.println(F("coin insert")); state = START_SHOW; }
void coinSlot_releasedCallback(uint8_t pinIn) {}
void coinSlot_pressedDurationCallback(uint8_t pinIn, unsigned long duration) {}
void coinSlot_releasedDurationCallback(uint8_t pinIn, unsigned long duration) {}

// Interrupt Service Routines
void coinSlotISR() { counter++; }

//
void enableSlotMachine(bool stat);

/* ------------------------------------ */
/* Setup                                */
/* ------------------------------------ */
void setup() {
  Serial.begin(115200);

  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_RELAIS_COINSLOT, OUTPUT);
  pinMode(PIN_RELAIS_5V24V, OUTPUT);

  coinSlotInput.registerCallbacks(coinSlot_pressedCallback, coinSlot_releasedCallback, coinSlot_pressedDurationCallback, coinSlot_releasedDurationCallback);
  coinSlotInput.setup(PIN_PROX_SENSOR, BUTTON_DEBOUNCE_DELAY, InputDebounce::PIM_INT_PULL_UP_RES);
  //  attachInterrupt(PIN_PROX_SENSOR, coinSlotISR, RISING);

  relais_state = false;

}


/* ------------------------------------ */
/* Main Loop                            */
/* ------------------------------------ */
void loop() {
  if (state != state_old) {
    Serial.print(F("new state: "));
    Serial.println(stateStrings[state]);
  }

  currentMillis = millis();
  smRun();


  //    delay(1000);
  //  Serial.println(counter);

}

/* ------------------------------------ */
/* State Machine Run                    */
/* ------------------------------------ */
void smRun() {
  state_old = state;

  switch (state) {
    case STARTUP:
      // check everything. if everything is fine:
      // 1) turn on relais at coin slot machine
      // 2) turn stepper motor with the info-sign
      enableSlotMachine(true);
      enableMainPower(false);
      state = WAIT;
      break;

    case WAIT:
      // check the coin slot machine. if coin is insert:
      // switch to state START_SHOW
      coinSlotInput.process(currentMillis); // callbacks called in context of this function
      break;


    case START_SHOW:
      // 1) turn on relais for main power supplies (5V + 24V)
      enableSlotMachine(false);
      enableMainPower(true);
      
      buzzer_beep(3, 50);
      state = RUN;
      

      break;


    case RUN:
      break;
    default:
      break;
  }
}


/* ------------------------------------ */
/* beep the BUZZER n times               */
/* ------------------------------------ */
void buzzer_beep(uint8_t _i, uint16_t duration) {
  for (int i = 0; i < _i; i++) {
    digitalWrite(PIN_BUZZER, HIGH);
    delay(duration);
    digitalWrite(PIN_BUZZER, LOW);
    delay(duration);
  }
}

void enableSlotMachine(bool stat) {
  digitalWrite(PIN_RELAIS_COINSLOT, stat);
}

void enableMainPower(bool stat) {
  digitalWrite(PIN_RELAIS_5V24V, stat);
}

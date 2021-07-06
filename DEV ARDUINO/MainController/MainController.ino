#include <InputDebounce.h> // InputDebounce Library by Mario Ban Version 1.6
#include <Wire.h>

#define PIN_PROX_SENSOR     35
#define PIN_RELAIS_COINSLOT 2
#define PIN_RELAIS_5V24V    15
#define PIN_BUZZER          23

//#include "/Users/julian/Buschcloud/02__PROJEKTE/20210901 Magdeburg Mechanisches Theater/MechanicalTheatre/DEV ARDUINO/Teensy_ReceiveTimelineData/MotorUnit.h"
#include "C:\Users\Julian\Desktop\MechanicalTheatre\DEV ARDUINO\Teensy_ReceiveTimelineData\MotorUnit.h"
#include "C:\Users\Julian\Desktop\MechanicalTheatre\DEV ARDUINO\Teensy_ReceiveTimelineData\CommonFunctions.h"
#include "LCDFunctions.h"
#include "Communication.h"

#define BUTTON_DEBOUNCE_DELAY   20   // [ms]


bool relais_state;

static InputDebounce coinSlotInput;
volatile uint16_t counter;

// i2c Communication
#define I2C_MEM_LEN 256
char i2cDatabuf[I2C_MEM_LEN];



// Timing
long millisOld = 0, millisCurrent;          // meassuring time to get into the fps-rhythm
long stateRequestInterval = 2000;           // interval on how often Teensy's state is requested
//long frameDuration = 1000 / MotorUnit::fps; // duration of a frame in milliseconds
uint16_t timesPlayed = 0;               // counts many times the sequence was repeated


// State Machine
enum states {STARTUP, WAIT, START_SHOW, RUN};
String PROGMEM stateStrings[] = {"STARTUP", "WAIT", "START_SHOW", "RUN"};
uint8_t state = STARTUP;
uint8_t state_old = 255;
void smRun();


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

  Wire.begin();

  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_RELAIS_COINSLOT, OUTPUT);
  pinMode(PIN_RELAIS_5V24V, OUTPUT);
  
  coinSlotInput.registerCallbacks(coinSlot_pressedCallback, coinSlot_releasedCallback, coinSlot_pressedDurationCallback, coinSlot_releasedDurationCallback);
  coinSlotInput.setup(PIN_PROX_SENSOR, BUTTON_DEBOUNCE_DELAY, InputDebounce::PIM_INT_PULL_UP_RES);
  //  attachInterrupt(PIN_PROX_SENSOR, coinSlotISR, RISING);

  LCDFunctions::init_display();
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

  millisCurrent = millis();
  smRun();
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
      //coinSlotInput.process(millisCurrent); // callbacks called in context of this function
      
      if(millisCurrent - millisOld > stateRequestInterval) {
        Serial.print(F("Teensy state: "));
        if (Communication::teensyRequestState() == 3) {  // IDLE-MODE
          state = START_SHOW;
        }
        millisOld = millisCurrent;
      }
      break;


    case START_SHOW:
      // 1) turn on relais for main power supplies (5V + 24V)
      enableSlotMachine(false);
      enableMainPower(true);
      Communication::sendRunCommand();
      
      buzzer_beep(3, 50);
      state = RUN;
      break;


    case RUN:
      // Send Command to Teensy to run the Show
      break;
    default:
      break;
  }
}


void enableSlotMachine(bool stat) {
  digitalWrite(PIN_RELAIS_COINSLOT, stat);
}

void enableMainPower(bool stat) {
  digitalWrite(PIN_RELAIS_5V24V, stat);
}

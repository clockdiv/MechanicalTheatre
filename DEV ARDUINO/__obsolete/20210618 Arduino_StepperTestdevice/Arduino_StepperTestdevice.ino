#include <InputDebounce.h> // InputDebounce Library by Mario Ban Version 1.6
#include "AccelStepper.h"

#define PIN_BTN1 2
#define PIN_BTN2 3

#define BUTTON_DEBOUNCE_DELAY   20   // [ms]

static InputDebounce btn1;
static InputDebounce btn2;

int16_t stepper1_dir = 1;
int16_t stepper2_dir = 1;


AccelStepper stepperA, stepperB; // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5



// Debounce-Libray Callbacks
void btn1_pressedCallback(uint8_t pinIn) {
  switch (pinIn)
  {
    case PIN_BTN1:
      stepper1_dir *= -1;
      break;
    case PIN_BTN2:
      stepper2_dir *= -1;
      break;
  }
}
void btn1_releasedCallback(uint8_t pinIn) {}
void btn1_pressedDurationCallback(uint8_t pinIn, unsigned long duration) {}
void btn1_releasedDurationCallback(uint8_t pinIn, unsigned long duration) {}


/* ------------------------------------ */
/* Setup                                */
/* ------------------------------------ */
void setup() {
  Serial.begin(115200);
  btn1.registerCallbacks(btn1_pressedCallback, btn1_releasedCallback, btn1_pressedDurationCallback, btn1_releasedDurationCallback);
  btn2.registerCallbacks(btn1_pressedCallback, btn1_releasedCallback, btn1_pressedDurationCallback, btn1_releasedDurationCallback);
  btn1.setup(PIN_BTN1, BUTTON_DEBOUNCE_DELAY, InputDebounce::PIM_INT_PULL_UP_RES );
  btn2.setup(PIN_BTN2, BUTTON_DEBOUNCE_DELAY, InputDebounce::PIM_INT_PULL_UP_RES );


  stepperA.setInterface(1);
  stepperA.setPins(4 /*step*/, 5 /*direction*/);
  stepperA.setMaxSpeed(6000);
  
  stepperB.setInterface(1);
  stepperB.setPins(6 /*step*/, 7 /*direction*/);
  stepperB.setMaxSpeed(6000);
}


/* ------------------------------------ */
/* Main Loop                            */
/* ------------------------------------ */
void loop() {

  unsigned long now = millis();

  btn1.process(now);
  btn2.process(now);

  int16_t pot1 = analogRead(A0) * stepper1_dir * 6;
  int16_t pot2 = analogRead(A1) * stepper2_dir * 6;
  
  stepperA.setSpeed(pot1);
  stepperA.runSpeed();
  
  stepperB.setSpeed(pot2);
  stepperB.runSpeed();
}

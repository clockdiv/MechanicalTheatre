
#include <AccelStepper.h>

const uint8_t pin_dir = 5;
const uint8_t pin_step = 6;
const uint8_t pin_poti = A0;
uint16_t v = 0;
uint16_t max_speed = 6000;

AccelStepper stepper(1, pin_step, pin_dir);

void setup() {
  stepper.setMaxSpeed(max_speed);  // steps per second
  stepper.setSpeed(max_speed);
}

void loop() {
  v = analogRead(A0);
  v = map(v, 0, 512, 0, max_speed);
  v = constrain(v, 0, max_speed);
  stepper.setSpeed(v); // steps per second
  
  stepper.runSpeed();
}

/*


*/
#include <AccelStepper.h>

const uint8_t pin_step_x = 2;
const uint8_t pin_step_y = 3;
const uint8_t pin_step_z = 4;
const uint8_t pin_dir_x = 5;
const uint8_t pin_dir_y = 6;
const uint8_t pin_dir_z = 7;
const uint8_t pin_stop_x = 9;
const uint8_t pin_stop_y = 10;
const uint8_t pin_stop_z = 11;


int16_t max_speed = 4000;
int16_t speed_x = max_speed;
int16_t speed_y = max_speed;
int16_t speed_z = max_speed;
bool direction_x = false;
bool direction_y = false;
bool direction_z = false;

uint8_t stop_x = false;
uint8_t stop_y = false;
uint8_t stop_z = false;

uint8_t pause_duration = 100;


AccelStepper stepperX(1, pin_step_x, pin_dir_x);
AccelStepper stepperY(1, pin_step_y, pin_dir_y);
AccelStepper stepperZ(1, pin_step_z, pin_dir_z);

void initZ() {
  Serial.println("init z");
  stepperZ.setSpeed(2000);
  while (digitalRead(pin_stop_z)) {
    stepperZ.runSpeed();
    //Serial.print("waiting for end stop \t");
    //Serial.println(stepperZ.currentPosition());
  }
  delay(1000);
  //stepperZ.setCurrentPosition(0);
  stepperZ.setAcceleration(1000000);
  stepperZ.move(-1000);
  while (stepperZ.distanceToGo() != 0) {
    //Serial.print("going back \t");
    //Serial.println(stepperZ.currentPosition());
    stepperZ.run();
  }
  delay(1000);
  stepperZ.setCurrentPosition(0);
  Serial.print("init z complete, current Pos: ");
  Serial.println(stepperZ.currentPosition());


}


void setup() {
  Serial.begin(115200);
  pinMode(pin_dir_x, OUTPUT);
  pinMode(pin_dir_y, OUTPUT);
  pinMode(pin_dir_z, OUTPUT);

  pinMode(pin_stop_x, INPUT_PULLUP);
  pinMode(pin_stop_y, INPUT_PULLUP);
  pinMode(pin_stop_z, INPUT_PULLUP);

  stepperX.setMaxSpeed(max_speed);  // steps per second
  stepperY.setMaxSpeed(max_speed);  // steps per second
  stepperZ.setMaxSpeed(max_speed);  // steps per second

  //  stepperX.setSpeed(0);
  //  stepperY.setSpeed(0);
  Serial.println("start");

  initZ();
}

void loop() {
  if (stepperZ.isRunning()) {
  //  Serial.print("dist. to go: ");
  //  Serial.println(stepperZ.distanceToGo());
  }
  
  if (stepperZ.distanceToGo() == 0)
  {
  //  Serial.print("current Pos: ");
  //  Serial.println(stepperZ.currentPosition());
  }
  
  stepperZ.run();

  
  /*
    stop_x = digitalRead(pin_stop_x);
    stop_y = digitalRead(pin_stop_y);
    stop_z = digitalRead(pin_stop_z);

    if (!stop_x || !stop_y) {
    stepperX.setSpeed(0); // steps per second
    stepperY.setSpeed(0);
    while (true);
    }


    stepperX.setSpeed(speed_x); // steps per second
    stepperX.runSpeed();

    stepperY.setSpeed(speed_y); // steps per second
    stepperY.runSpeed();
  */
}

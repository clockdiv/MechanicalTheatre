#include "MotorUnit.h"

uint8_t MotorUnit::fps = 25;
uint16_t MotorUnit::maxStepperSpeed = 4000;
bool MotorUnit::tooFast = false;
uint16_t MotorUnit::temp_switchPressedCounter = 0;


MotorUnit::MotorUnit() {
  //stepper = AccelStepper(1, 34, 35);
  animationLength = 0;
  pinDir = 0;
  pinStep = 1;
  pinEnd = 2;
  endswitchPressed = false;
  motorName = "";
  stepper.setMaxSpeed(maxStepperSpeed);
}


void MotorUnit::initDriver(String _name, uint8_t _pinEnd, uint8_t _pinDir, uint8_t _pinStep, bool directionInvert) {
  motorName = _name;
  stepper.setInterface(1);
  stepper.setPins( _pinStep, _pinDir);
  stepper.setPinsInverted(directionInvert);
  stepper.setMinPulseWidth(20);
  pinEnd = _pinEnd;
  pinMode(pinEnd, INPUT);
}

// return true: stopped at home position (end switch)
// return false: still running
bool MotorUnit::runToHomePosition() {
  if (checkEndswitch() == false) {    // run to home position; change to -2000
    Serial.print("0");
    stepper.setSpeed(-1000);
    stepper.runSpeed();
    return false;
  } 
  Serial.print("1");
  // if end switch is pressed, prepare for postReset (run 100 steps away from end-stop to create distance)
  stepper.setAcceleration(100);
  stepper.move(100);
  return true;
}



bool MotorUnit::postReset() {
  if (stepper.distanceToGo() != 0) {
    stepper.run();
    return false;
  }
  stepper.setCurrentPosition(0);
  return true;
}

void MotorUnit::setKeyframeValue(uint16_t index, uint16_t value) {
  keyframeValues[index] = value;
}


void MotorUnit::moveToFramePosition(uint16_t frame) {
  stepper.moveTo(keyframeValues[frame]);

  // calculate Speed with this keyframe and upcoming keyframe
  uint16_t deltaPos = abs( keyframeValues[frame] - keyframeValues[frame + 1]);
  uint16_t motorSpeed = deltaPos * fps;

  tooFast = motorSpeed > maxStepperSpeed;
  /*
    Serial.print(keyframeIndex);
    Serial.print(" - ");
    Serial.print("\tms: ");
    Serial.print(motorSpeed);
    Serial.print("\ti: ");
    Serial.print(keyframeIndex);
    Serial.print("\tcount: ");
    Serial.println(animationLength);
  */
  stepper.setSpeed(motorSpeed);
}

bool MotorUnit::update() {
  if (checkEndswitch()) 
    return false;
  
  stepper.runSpeedToPosition();
  return true;
}


// true: end switch pressed
// false: not pressed
bool MotorUnit::checkEndswitch() {
  endswitchPressed = digitalRead(pinEnd); // high if pressed

  if (endswitchPressed) {
    temp_switchPressedCounter++;
    //Serial.print("Endswitch pressed: ");
    //Serial.println(motorName);
    //Serial.print("\t#");
    //Serial.println(temp_switchPressedCounter);
    return true;
  }

  return false;

}
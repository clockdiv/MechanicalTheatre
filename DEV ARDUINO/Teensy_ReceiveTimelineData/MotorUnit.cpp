#include "MotorUnit.h"

uint8_t MotorUnit::fps = 25;
uint16_t MotorUnit::maxStepperSpeed = 4000;
bool MotorUnit::tooFast = false;
uint8_t MotorUnit::temp_switchPressedCounter = 0;


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
  pinMode(pinEnd, INPUT_PULLUP);
}


void MotorUnit::resetPosition() {
  //Serial.print("reset Position ");
  //Serial.println(motorName);
  stepper.setSpeed(-2000);


  /*
    Serial.println("stop detected");
    delay(1000);
    delay(1000);
    stepper.setCurrentPosition(0);
    Serial.print(motorName);
    Serial.print(" - init complete, current Pos: ");
    Serial.println(stepper.currentPosition());
  */
}

void MotorUnit::updateReset() {
  endswitchPressed = digitalRead(pinEnd);
  if (!endswitchPressed) {
    stepper.setAcceleration(10000);
    stepper.move(1000);
    return;
  }
  stepper.runSpeed();
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
  endswitchPressed = digitalRead(pinEnd);

  if (!endswitchPressed) {
    temp_switchPressedCounter++;
    Serial.print("Endswitch pressed: ");
    Serial.print(temp_switchPressedCounter);
    Serial.println(motorName);
    delay(1000);
    return false;
  }

  stepper.runSpeedToPosition();
  return true;
}

#include "MotorUnit.h"

uint8_t MotorUnit::fps = 25;
uint16_t MotorUnit::maxStepperSpeed = 4000;
bool MotorUnit::tooFast = false;


MotorUnit::MotorUnit() {
  //stepper = AccelStepper(1, 34, 35);
  animationLength = 0;
  pinDir = 0;
  pinStep = 1;
  pinEnd = 2;
  stepper.setMaxSpeed(maxStepperSpeed);
}


void MotorUnit::initDriver(uint8_t _pinEnd, uint8_t _pinDir, uint8_t _pinStep) {
  stepper.setInterface(1);
  stepper.setPins( _pinStep, _pinDir);
  pinEnd = _pinEnd;
}


void MotorUnit::resetPosition() {
  stepper.setCurrentPosition(0);
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

void MotorUnit::update() {
  stepper.runSpeedToPosition();
}

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
  pinMode(pinEnd, INPUT);
}


void MotorUnit::runToHomePosition() {
  //Serial.print("reset Position ");
  //Serial.println(motorName);

  endswitchPressed = digitalRead(pinEnd);
  if (endswitchPressed) {  // if end switch is pressed, prepare for postReset (run 1000 steps away from end-stop to create distance)
    stepper.setAcceleration(10000);
    stepper.move(100);
    return;
  }
  stepper.setSpeed(-500); // run to home position; change to -2000
  stepper.runSpeed();


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
  if (!checkEndswitch()) 
    return false;
  
  stepper.runSpeedToPosition();
  return true;
}

bool MotorUnit::checkEndswitch() {
  endswitchPressed = digitalRead(pinEnd);

  if (endswitchPressed) {
    temp_switchPressedCounter++;
    Serial.print("Endswitch pressed: ");
    Serial.print(motorName);
    Serial.print("\t#");
    Serial.println(temp_switchPressedCounter);
    return false;
  }

  return true;

}
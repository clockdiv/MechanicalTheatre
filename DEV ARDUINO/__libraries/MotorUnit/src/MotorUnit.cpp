#include "MotorUnit.h"

uint8_t MotorUnit::fps = 25;
uint16_t MotorUnit::maxStepperSpeed = 6000;

/* ------------------------------------ */
String MotorUnit::stateStrings[] = {
    "IDLE",
    "GOING TO END SWITCH",
    "ENDSWITCH PRESSED",
    "GOING TO INIT",
    "DRIVING SHOW",
    "ENDSWITCH ERROR"};

/* ------------------------------------ */
MotorUnit::MotorUnit()
{
  animationLength = 0;
  pinDir = 0;
  pinStep = 1;
  motorName = "";
  stepper.setMaxSpeed(maxStepperSpeed);
  motorState = __IDLE;
  motorStateOld = __UNDEFINED;
  initPosition = 0;
  temp_switchPressedCounter = 0;
}

/* ------------------------------------ */
void MotorUnit::initDriver(String _name, uint8_t _pinEnd, uint8_t _pinDir, uint8_t _pinStep, bool directionInvert, uint16_t _initPosition, uint16_t _resetSpeed, bool _invertedEndswitch)
{
  motorName = _name;
  initPosition = _initPosition;
  resetSpeed = _resetSpeed;
  motorResetDependency = nullptr;
  invertedEndswitch = _invertedEndswitch;

  stepper.setInterface(AccelStepper::DRIVER);
  stepper.setPins(_pinStep, _pinDir);
  stepper.setPinsInverted(directionInvert);
  stepper.setMinPulseWidth(15);

  invertedEndswitch ? endswitch.attach(_pinEnd, INPUT_PULLUP) : endswitch.attach(_pinEnd, INPUT_PULLDOWN);

  endswitch.interval(25);
}

/* ------------------------------------ */
// stores the timeline keyframe by keyframe
void MotorUnit::setKeyframeValue(uint16_t index, uint16_t value)
{
  keyframeValues[index] = value;
}

/* ------------------------------------ */
// sets the stepper's next position according to the timeline
// and calculates the speed
void MotorUnit::moveToFramePosition(uint16_t frame)
{
  long targetPosition = keyframeValues[frame];
  stepper.moveTo(targetPosition);

  // calculate Speed with this keyframe and upcoming keyframe
  // deltaPos = number of steps from the previous position to the current position
  long deltaPos = targetPosition - stepper.currentPosition();
  //long deltaPos = targetPosition - keyframeValues[frame - 1];
  if (motorName == "Ufo_Y-Axis")
    Serial.println(deltaPos);

  long motorSpeed = deltaPos * fps;

  tooFast = abs(motorSpeed) > maxStepperSpeed;
  stepper.setSpeed(motorSpeed);
}

/* ------------------------------------ */
// updates the endswitch and state-machine
void MotorUnit::update()
{
  if (motorState != motorStateOld)
  {
    printMessage(stateStrings[motorState]);
  }

  endswitch.update();
  smRun();
}

/* ------------------------------------ */
// switches state-machine
void MotorUnit::smRun()
{
  motorStateOld = motorState;

  switch (motorState)
  {
  case __IDLE:
    idle();
    break;

  case __GOING_TO_ENDSWITCH:
    goingToEndswitch();
    break;

  case __ENDSWITCH_PRESSED:
    endswitchPressed();
    break;

  case __GOING_TO_INIT:
    goingToInit();
    break;

  case __DRIVING_SHOW:
    drivingShow();
    break;

  case __TESTDRIVE:
    testDrive();
    break;

  case __ENDSWITCH_ERROR:
    break;

  case __UNDEFINED:
    break;
  }
}

/* ------------------------------------ */
void MotorUnit::idle()
{
  // if (endswitch.risingEdge())
  // {
  //   printMessage(F("Endswitch pressed"));
  // }
  // else if (endswitch.fallingEdge())
  // {
  //   printMessage(F("Endswitch released"));
  // }
}

/* ------------------------------------ */
void MotorUnit::goingToEndswitch()
{
  if (motorResetDependency == nullptr || motorResetDependency->motorState == __IDLE)
  {
    if (readEndswitch())
    {
      stepper.setCurrentPosition(0);
      motorState = __ENDSWITCH_PRESSED;
      return;
    }

    stepper.setSpeed(-resetSpeed);
    stepper.runSpeed();
  }
}

/* ------------------------------------ */
void MotorUnit::endswitchPressed()
{
  stepper.setAcceleration(150);
  stepper.move(initPosition);
  motorState = __GOING_TO_INIT;
}

/* ------------------------------------ */
void MotorUnit::goingToInit()
{
  if (stepper.distanceToGo() != 0)
  {
    stepper.run();
  }
  else
  {
    stepper.setCurrentPosition(0);
    motorState = __IDLE;
  }
}

/* ------------------------------------ */
void MotorUnit::drivingShow()
{
  if (readEndswitch())
  {
    printMessage(F("ERROR: Endswitch pressed while driving show."));
    motorState = __ENDSWITCH_ERROR;
    return;
  }

  stepper.runSpeedToPosition();
}

/* ------------------------------------ */
void MotorUnit::endswitchError() {}

/* ------------------------------------ */
void MotorUnit::printMessage(String msg)
{
  Serial.print(motorName);
  Serial.print("\t");
  Serial.println(msg);
}

/* ------------------------------------ */
void MotorUnit::setResetDependency(MotorUnit *_motorResetDependency)
{
  motorResetDependency = _motorResetDependency;
}

/* ------------------------------------ */
void MotorUnit::testDrive()
{
  if (!readEndswitch())
  {
    stepper.setSpeed(100);
    stepper.runSpeed();
  }
}

/* ------------------------------------ */
bool MotorUnit::readEndswitch()
{
  if (!invertedEndswitch)
  {
    if (endswitch.risingEdge() || endswitch.read() == true)
    {
      return true;
    }
  }
  else
  {
    if (endswitch.fallingEdge() || endswitch.read() == false)
    {
      return true;
    }
  }
  return false;
}
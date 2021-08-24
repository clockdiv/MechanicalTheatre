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
void MotorUnit::initDriver(String _name, uint8_t _pinEnd, uint8_t _pinDir, uint8_t _pinStep, bool directionInvert, uint16_t _initPosition, uint16_t _resetSpeed)
{
  motorName = _name;
  initPosition = _initPosition;
  resetSpeed = _resetSpeed;
  motorResetDependency = nullptr;

  stepper.setInterface(1);
  stepper.setPins(_pinStep, _pinDir);
  stepper.setPinsInverted(directionInvert);
  stepper.setMinPulseWidth(50);

  endswitch.attach(_pinEnd, INPUT_PULLDOWN);
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
uint16_t MotorUnit::moveToFramePosition(uint16_t frame)
{
  stepper.moveTo(keyframeValues[frame]);

  // calculate Speed with this keyframe and upcoming keyframe
  // deltaPos = number of steps from the previous position to the current position
  uint16_t deltaPos = abs(keyframeValues[frame] - keyframeValues[frame - 1]);

  uint16_t motorSpeed = deltaPos * fps;

  tooFast = motorSpeed > maxStepperSpeed;

  stepper.setSpeed(motorSpeed);
  return deltaPos;
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

  case __ENDSWITCH_ERROR:
    break;

  case __UNDEFINED:
    break;
  }
}

/* ------------------------------------ */
void MotorUnit::idle()
{
  if (endswitch.risingEdge())
  {
    printMessage(F("Endswitch pressed"));
  }
  else if (endswitch.fallingEdge())
  {
    printMessage(F("Endswitch released"));
  }
}

/* ------------------------------------ */
void MotorUnit::goingToEndswitch()
{
  if (motorResetDependency == nullptr || motorResetDependency->motorState == __IDLE)
  {
    if (endswitch.risingEdge() || endswitch.read() == true)
    {
      printMessage(F("\tEndswitch pressed"));
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
  if (endswitch.risingEdge() || endswitch.read() == true)
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
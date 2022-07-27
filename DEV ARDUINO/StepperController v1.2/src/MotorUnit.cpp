#include "MotorUnit.h"

uint8_t MotorUnit::fps = 25;
uint16_t MotorUnit::maxStepperSpeed = 6000;
std::map<MotorUnit::states, String> MotorUnit::stateStringsMap =
    {{__IDLE, "IDLE"},
     {__GOING_TO_ENDSWITCH, "GOING TO END SWITCH"},
     {__ENDSWITCH_PRESSED, "ENDSWITCH PRESSED"},
     {__GOING_TO_INIT, "GOING TO INIT"},
     {__GOING_TO_FRAME_ZERO, "GOING TO FRAME ZERO"},
     {__DRIVING_SHOW, "DRIVING SHOW"},
     {__TESTDRIVE, "TESTDRIVE"},
     {__ENDSWITCH_ERROR, "ENDSWITCH ERROR"},
     {__UNDEFINED, "UNDEFINED"}};

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
  motorEmergencyStopDependency = nullptr;
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
    // printMessage(stateStrings[motorState]);
    printMessage(stateToString(motorState));
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

  case __GOING_TO_FRAME_ZERO:
    goingToFrameZero();
    break;

  case __DRIVING_SHOW:
    drivingShow();
    break;

  case __TESTDRIVE:
    testDrive();
    break;

  case __ENDSWITCH_ERROR:
    endswitchError();
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
// Drives Motor back to Endswitch
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
// if endswitch pressed, go on to state GOING_TO_INIT
void MotorUnit::endswitchPressed()
{
  stepper.setAcceleration(150);
  stepper.move(initPosition);
  motorState = __GOING_TO_INIT;
}

/* ------------------------------------ */
// drive to Init-Position and set Position to 0
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
    // stepper.moveTo(keyframeValues[0]);  // move to Position of Frame 0
    // stepper.setSpeed(2500);
    // motorState = __GOING_TO_FRAME_ZERO;
  }
}

/* ------------------------------------ */
// go to the *position* of first frame, if reached set state to IDLE
void MotorUnit::goingToFrameZero()
{
  if (stepper.distanceToGo() != 0)
  {
    stepper.runSpeedToPosition();
  }
  else
  {
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

  if (motorEmergencyStopDependency == nullptr || motorEmergencyStopDependency->motorState != __ENDSWITCH_ERROR)
  {
    stepper.runSpeedToPosition();
  }
}

/* ------------------------------------ */
void MotorUnit::endswitchError()
{
}

/* ------------------------------------ */
void MotorUnit::printMessage(String msg)
{
  Serial.print(motorName);
  Serial.print("\t");
  Serial.println(msg);
}

/* ------------------------------------ */
String MotorUnit::stateToString(states _state)
{
  if (stateStringsMap.find(_state) != stateStringsMap.end())
  {
    return stateStringsMap[_state];
  }
  else
  {
    return "state does not have a name";
  }
}

/* ------------------------------------ */
void MotorUnit::setResetDependency(MotorUnit *_motorResetDependency)
{
  motorResetDependency = _motorResetDependency;
}

/* ------------------------------------ */
void MotorUnit::setEmergencyStopDependency(MotorUnit *_motorEmergencyStopDependency)
{
  motorEmergencyStopDependency = _motorEmergencyStopDependency;
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
#ifndef MotorUnit_h
#define MotorUnit_h

#include <Arduino.h>
#include <map>
#include "Bounce2.h"
#include "AccelStepper.h"
#include "Configurations.h"

class MotorUnit
{
private:
  enum states
  {
    __IDLE,
    __GOING_TO_ENDSWITCH,
    __ENDSWITCH_PRESSED,
    __GOING_TO_INIT,
    __GOING_TO_FRAME_ZERO,
    __DRIVING_SHOW,
    __TESTDRIVE,
    __ENDSWITCH_ERROR,
    __UNDEFINED
  };
  
  AccelStepper stepper;
  MotorUnit *motorResetDependency; // can be a motor that *this* motor waits for until it's resetting
  MotorUnit *motorEmergencyStopDependency;  // if that motor drive to the endswitch, *this* motor has to stop as well
  Bounce endswitch;
  static std::map<states, String> stateStringsMap;

  uint8_t pinDir;
  uint8_t pinStep;
  uint16_t initPosition; // the distance from end-switch to init-position
  uint16_t resetSpeed;
  static uint16_t maxStepperSpeed;
  uint16_t keyframeValues[MAX_FRAMES]; // all keyframes. assigned by read_keyframes_from_file()

  void smRun();
  void idle();
  void goingToEndswitch();
  void endswitchPressed();
  void goingToInit();
  void goingToFrameZero();
  void drivingShow();
  void endswitchError();
  void printMessage(String msg);
  String stateToString(states _state);

  bool invertedEndswitch;
  bool readEndswitch();

public:


  String motorName;
  states motorState, motorStateOld;
  bool tooFast;
  static uint8_t fps;       // frames per second for playback
  uint16_t animationLength; // number of keyframes. assigned by read_keyframes_from_file()
  uint16_t temp_switchPressedCounter;

  MotorUnit();
  void initDriver(String _name, uint8_t _pinEnd, uint8_t _pinDir, uint8_t _pinStep, bool directionInvert, uint16_t _initPosition, uint16_t _resetSpeed, bool _invertedEndswitch);
  void setResetDependency(MotorUnit *_motorResetDependency);
  void setEmergencyStopDependency(MotorUnit *_motorEmergencyStopDependency);
  void setReset() { motorState = __GOING_TO_ENDSWITCH; }
  void setPlay() { motorState = __DRIVING_SHOW; }
  void setEndswitchPressed()
  { // for debugging purpose only - to simulate the pressed endswitch after a specific amount of time
      stepper.setCurrentPosition(0);
    motorState = __ENDSWITCH_PRESSED;
  };
  states getState() {
    return motorState;
  };
  bool isIdle() { return motorState == __IDLE; }
  void setKeyframeValue(uint16_t index, uint16_t value);
  void moveToFramePosition(uint16_t frame);
  void update();
  void setTestDrive() { motorState = __TESTDRIVE; }
  void testDrive();
};

#endif

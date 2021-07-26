#ifndef MotorUnit_h
#define MotorUnit_h

#include <Arduino.h>
#include "Bounce2.h"
#include "AccelStepper.h"

#define MAX_FRAMES 3000     // maximum number of frames, used to initialize the keyframeValues-array

class MotorUnit {
  private:
    enum states {
      __IDLE,
      __GOING_TO_ENDSWITCH,
      __ENDSWITCH_PRESSED,
      __GOING_TO_INIT,
      __DRIVING_SHOW,
      __ENDSWITCH_ERROR,
      __UNDEFINED
    };

    AccelStepper stepper;
    Bounce endswitch;
    states motorState, motorStateOld;
    static String stateStrings[];
    uint8_t pinDir;
    uint8_t pinStep;
    uint16_t initPosition;  // the distance from end-switch to init-position
    uint16_t resetSpeed;
    static uint16_t maxStepperSpeed;
    uint16_t keyframeValues[MAX_FRAMES];    // all keyframes. assigned by read_keyframes_from_file()

    void smRun();
    void idle();
    void goingToEndswitch();
    void endswitchPressed();
    void goingToInit();
    void drivingShow();
    void endswitchError();
    void printMessage(String msg);

  public:
    String motorName;
    bool tooFast;
    static uint8_t fps;           // frames per second for playback
    uint16_t animationLength;     // number of keyframes. assigned by read_keyframes_from_file()
    uint16_t temp_switchPressedCounter;

    MotorUnit();
    void initDriver(String _name, uint8_t _pinEnd, uint8_t _pinDir, uint8_t _pinStep, bool directionInvert, uint16_t _initPosition, uint16_t _resetSpeed);
    void setReset() { motorState = __GOING_TO_ENDSWITCH; }
    void setPlay() { motorState = __DRIVING_SHOW; }
    bool isIdle() { return motorState == __IDLE; }
    void setKeyframeValue(uint16_t index, uint16_t value) ;
    void moveToFramePosition(uint16_t frame);
    void update();
};

#endif

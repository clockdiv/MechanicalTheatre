#ifndef MotorUnit_h
#define MotorUnit_h

#include "AccelStepper.h"

#define MAX_FRAMES 7500     // maximum number of frames, used to initialize the keyframeValues-array


class MotorUnit {
  private:
    AccelStepper stepper;
    uint8_t pinDir;
    uint8_t pinStep;
    uint8_t pinEnd;

    static uint16_t maxStepperSpeed;

    uint16_t keyframeValues[MAX_FRAMES];    // all keyframes. assigned by read_keyframes_from_file()

    bool endswitchPressed;

  public:
    static bool tooFast;
    static uint8_t fps;                      // frames per second for playback
    uint16_t animationLength;         // number of keyframes. assigned by read_keyframes_from_file()

    MotorUnit();
    void initDriver(uint8_t _pinEnd, uint8_t _pinDir, uint8_t _pinStep, bool directionInvert = false);
    void resetPosition();
    void setKeyframeValue(uint16_t index, uint16_t value) ;
    void moveToFramePosition(uint16_t frame);
    void update();

};

#endif

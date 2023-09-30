#ifndef Motor_h
#define Motor_h

#include "Arduino.h"
#include <inttypes.h>

class Motor {
  public:
    enum State {FORWARD, BACKWARD, FREEZE};
    enum Mode {ANALOG, DIGITAL};
    
  private:
    uint8_t _pinA, _pinB, _enablePin;
    enum State _state;
    enum Mode _mode;
    
  public:
    Motor(uint8_t pinA, uint8_t pinB, uint8_t enablePin, Mode mode=DIGITAL);
    bool goForward(uint8_t pwmValue=0); //Moves the motor forward.
    bool goBackward(uint8_t pwmValue=0); //Moves the motor BACKWARDward.
    bool freeze();   //Stops the motor.
    uint8_t getState();	//Gets state of the motor.
    uint8_t getMode(); //Gets mode of the motor.
};

#endif


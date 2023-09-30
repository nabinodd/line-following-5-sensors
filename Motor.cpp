#include "Motor.h"

Motor::Motor(uint8_t pinA, uint8_t pinB, uint8_t enablePin, Mode mode): _pinA(pinA), _pinB(pinB), _enablePin(enablePin), _mode(mode) {
  pinMode(_pinA,OUTPUT);
  pinMode(_pinB,OUTPUT);
  
  if (_mode == ANALOG) {
    pinMode(_enablePin, OUTPUT);
    digitalWrite(_pinA, HIGH);
    digitalWrite(_pinB, LOW);
  }
  _state=FREEZE;
}

bool Motor::goForward(uint8_t pwmValue) {
  _state = FORWARD;
  digitalWrite(_pinA, HIGH);
  digitalWrite(_pinB, LOW);
  if(_mode==ANALOG){
    //analogWrite(_pinA,pwmValue);
    //analogWrite(_pinB,LOW);
    analogWrite(_enablePin, pwmValue);
  }
  return true;
}

bool Motor::goBackward(uint8_t pwmValue) {
  _state = BACKWARD;
    digitalWrite(_pinA, LOW);
    digitalWrite(_pinB, HIGH);
  if(_mode == ANALOG) {
    //analogWrite(_pinA,LOW);
    //analogWrite(_pinB,pwmValue); 
    analogWrite(_enablePin, pwmValue);
  }
  return true;
}

bool Motor::freeze() {
  _state = FREEZE;
    digitalWrite(_pinA, LOW);
    digitalWrite(_pinB, LOW);
  if(_mode == ANALOG) {
    //analogWrite(_pinA,LOW);
    //analogWrite(_pinB,LOW); 
    analogWrite(_enablePin, LOW);
  }
  return true;
}

uint8_t Motor::getState() {
  return _state;
}

uint8_t Motor::getMode() {
  return _mode;
}

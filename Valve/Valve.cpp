#include "Valve.h"

Valve::Valve(const uint8_t &pin, int *state, int duration = 15000, bool debug = true)
{
  pinMode(pin, OUTPUT);
  _pin = pin;
  _pour_duration = duration;
  
  _state = state;
  _debug = debug;
}

void Valve::_openValve()
{
  logger("Opening Valve");
  digitalWrite(_pin, HIGH);
}

void Valve::_closeValve()
{
  logger("Closing Valve");
  digitalWrite(_pin, LOW);
}

void Valve::setValveDuration(int new_duration)
{
  logger("Setting valve duration to:");
  logger(new_duration);
  _pour_duration = new_duration;
}

void Valve::sm_valve()
{
  static long valveOpenedTime = 0;

  switch (*_state)
  {
  case 0: //Wait
    //Do nothing.  Only the top level loop can force us out of this state into state 2 "TURN ON"
    break;
  case 1: //Open valve
    valveOpenedTime = millis();
    _openValve();
    *_state = 2;
    break;
  case 2: //Pouring water
    if (millis() - valveOpenedTime >= _pour_duration)
    { //very small chance this breaks on rollover
      *_state = 3;
    }
    break;
  case 3: //Close valve
    _closeValve();
    *_state = 0;
    break;
  }
}

template <typename T>
void Valve::logger(T str)
{
  if (_debug)
  {
    Serial.println(str);
  }
}

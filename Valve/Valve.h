/*
  Valve.h - Controlloing watering valve
  Created by Kristof C, 8/18/20

*/

#ifndef Valve_h
#define Valve_h

#include "Arduino.h"

class Valve
{
public:
  Valve(const uint8_t &pin, int *state, int duration, bool debug);
  void setValveDuration(int new_duration);
  void sm_valve();

private:
  bool _debug;
  int _pin;
  int _pour_duration;
  int *_state;
  void _openValve();
  void _closeValve();
  template <typename T>
  void logger(T str);
};

#endif

/*
 JsonSerializer.h - Controlloing watering Soil Sensors
  Created by Kristof C, 8/24/20
*/

#ifndef JsonSerializer_h
#define JsonSerializer_h

#include "Arduino.h"
#include <string>

class JsonSerializer
{
public:
  JsonSerializer();
  String serialize(String);
private:
  int _retryCount;
  String _token;
  String _baseServer;
  bool _debug;
  template <typename T>
  void logger(T str);
};

#endif

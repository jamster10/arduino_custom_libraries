/*
  Soil Sensors.h - Controlloing watering Soil Sensors
  Created by Kristof C, 8/21/20

*/

#ifndef SoilSensors_h
#define SoilSensors_h

#include "Arduino.h"

class SoilSensors
{
public:
  SoilSensors(const uint8_t &MUXDriver1, const uint8_t &MUXDriver2, const uint8_t &MUXDriver3, const uint8_t &MUXControlAnalogPin, int *state, int wateringThreshold, int sampleCount, bool debug);
  bool shouldWater();
  // int *getSensorData();
  void sm_soil_sensors();
  void setWateringThreshold(int new_threshold);
  int _sensorDataArray[3];
private:
  bool _debug;
  int *_state;
  int _wateringThreshold;
  int _sampleCount;
  int _MUXDriver1;
  int _MUXDriver2;
  int _MUXDriver3;
  int _MUXControlOutputPin;
  void readSensors();
  template <typename T>
  void logger(T str);
};

#endif

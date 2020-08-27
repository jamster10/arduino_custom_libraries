#include "SoilSensors.h"

SoilSensors::SoilSensors(const uint8_t &MUXDriver1, const uint8_t &MUXDriver2, const uint8_t &MUXDriver3, const uint8_t &MUXControlOutputPin, int *state, int wateringThreshold = 700, int sampleCount = 10, bool debug = true) : _sensorDataArray{0, 0, 0}
{
  pinMode(MUXDriver1, OUTPUT);
  pinMode(MUXDriver2, OUTPUT);
  pinMode(MUXDriver3, OUTPUT);
  pinMode(MUXControlOutputPin, INPUT);

  _MUXDriver1 = MUXDriver1;
  _MUXDriver2 = MUXDriver2;
  _MUXDriver3 = MUXDriver3;
  _MUXControlOutputPin = MUXControlOutputPin;

  _sampleCount = sampleCount;
  _wateringThreshold = wateringThreshold;

  _state = state;
  _debug = debug;
};

boolean SoilSensors::shouldWater()
{
  for (int sensor = 0; sensor < sizeof(_sensorDataArray); sensor++)
  {
    if (_sensorDataArray[sensor] > _wateringThreshold)
    {
      return true;
    }
  }
  return false;
}

void SoilSensors::readSensors()
{
  for (int sensor = 0; sensor < 3; sensor++)
  {
    digitalWrite(_MUXDriver1, HIGH && (sensor & B00000001));
    digitalWrite(_MUXDriver2, HIGH && (sensor & B00000010));
    digitalWrite(_MUXDriver3, HIGH && (sensor & B00000100));
    _sensorDataArray[sensor] = _sensorDataArray[sensor] + analogRead(_MUXControlOutputPin);
  }
};

void SoilSensors::setWateringThreshold(int newThreshold)
{
  logger("Setting new threshold to: ");
  logger(newThreshold);
  _wateringThreshold = newThreshold;
}

void SoilSensors::sm_soil_sensors()
{
  static int interval = 500;
  static int currentSample = 0;
  static long lastMeasurementTime = 0;

  switch (*_state)
  {
  case 0: //Take Samples
    if ((currentSample < _sampleCount) && (millis() - lastMeasurementTime >= interval) || (lastMeasurementTime == 0))
    {
      currentSample++;
      readSensors();
      lastMeasurementTime = millis();
    }
    else if (currentSample == _sampleCount)
    {
      for (int sensor = 0; sensor < 3; sensor++)
      {
        _sensorDataArray[sensor] = _sensorDataArray[sensor] / _sampleCount;
      }
      *_state = 1;
    }

    break;
  case 1: //reset data
    lastMeasurementTime = 0;
    currentSample = 0;

    *_state = 2;
    break;
  case 2: //Do nothing
    break;
  }
}

template <typename T>
void SoilSensors::logger(T str)
{
  if (_debug)
  {
    Serial.println(str);
  }
}

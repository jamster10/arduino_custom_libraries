/*
  Connectivity.h - Controlloing wifi ability
  Created by Kristof C, 8/21/20

*/

#ifndef Connectivity_h
#define Connectivity_h

#include <ESP8266WiFi.h>
#include "Arduino.h"

class Connectivity
{
public:
  Connectivity(int *state, char *ssid, char *password, bool debug);
  void sm_connectivity();
  String macAddress();
  char *status;
private:
  char *_ssid;
  char *_password;
  int *_state;
  bool _debug;
  void _attemptConnection();

  template <typename T>
  void logger(T str);
};

#endif

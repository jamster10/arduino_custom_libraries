/*
 HttpHandler.h - Controlloing watering Soil Sensors
  Created by Kristof C, 8/21/20

*/

#ifndef HttpHandler_h
#define HttpHandler_h

#include "Arduino.h"
#include <ESP8266HTTPClient.h>

class HttpHandler
{
public:
  HttpHandler(String baseServer, String macAddress, bool debug);
  String post(String path, String data);
  String get(String path);

private:
  int _retryCount;
  String _token;
  String _baseServer;
  bool _debug;
  template <typename T>
  void logger(T str);
};

#endif

#include "Connectivity.h"

WiFiClient espClient;

Connectivity::Connectivity(int *state, char *ssid, char *password, bool debug = true)
{
  _ssid = ssid;
  _password = password;

  _state = state;
  _debug = debug;

  status = "CONNECTING";
}

void Connectivity::_attemptConnection()
{
  logger("Connecting to: ");
  logger(_ssid);
  logger("Establishing Connection");
  WiFi.begin(_ssid, _password);
}

void Connectivity::sm_connectivity()
{
  static long initialize_time = 0;
  static int failedAttempts = 0;

  if (failedAttempts > 4 && *_state != 3)
  {
    *_state = 3;
    logger("Unable to establish connection");
  }

  switch (*_state)
  {
  case 0: //Attempt connection
    *_state = 1;
    initialize_time = millis();
    _attemptConnection();
    break;
  case 1: //Check connection and attempts
    if (WiFi.status() != WL_CONNECTED && millis() - initialize_time > 5000)
    {
      failedAttempts++;
      *_state = 0;
    }
    else if (WiFi.status() == WL_CONNECTED)
    {
      status = "ENABLED";

      logger("Connection Established");
      logger("IP address: ");
      logger(WiFi.localIP());
      *_state = 2;
      failedAttempts = 0;
    }
    break;
  case 2:
    if (WiFi.status() != WL_CONNECTED)
    {
      logger("Connection Lost.");
      *_state = 0;
    }
    break;
  case 3: //Give up conecting
    if (status != "DISABLED")
    {
      status = "DISABLED";
    }
    break;
  }
}

String Connectivity::macAddress(){
  return WiFi.macAddress();
}

template <typename T>
void Connectivity::logger(T str)
{
  if (_debug)
  {
    Serial.println(str);
  }
}

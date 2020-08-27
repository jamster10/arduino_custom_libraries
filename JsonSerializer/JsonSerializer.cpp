#include "JsonSerializer.h"

// JsonSerializer::JsonSerializer()
// {
//   _token = "bearer " + macAddress;
//   _baseServer = baseServer;
//   _retryCount = 3;
//   _debug = debug;
// };

String JsonSerializer::serialize(String data)
{  
    
}

template <typename T>
void JsonSerializer::logger(T str)
{
  if (_debug)
  {
    Serial.println(str);
  }
}

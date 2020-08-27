#include "HttpHandler.h"

HTTPClient http;

HttpHandler::HttpHandler(String baseServer, String macAddress, bool debug = false)
{
  _token = "bearer " + macAddress;
  _baseServer = baseServer;
  _retryCount = 3;
  _debug = debug;
};

String HttpHandler::post(String path, String data)
{  
      String serverPath = _baseServer + path;

      http.begin(serverPath.c_str());
      http.addHeader("Authorization", _token);
      http.addHeader("Content-Type", "application/json");

      int httpResponseCode = http.POST(data);

      if (httpResponseCode > 0) {
        _retryCount = 0;

        const String payload = http.getString();
        
        http.end();
        return(payload);
      }
      else {
        if (_retryCount > 2){
          logger("Unable to contact server");
          http.end();
          return "0";
        };
        post(path, data);
      }     
}

String HttpHandler::get(String path)
{  
      String serverPath = _baseServer + path;

      http.begin(serverPath.c_str());
      http.addHeader("Authorization", _token);

      int httpResponseCode = http.GET();

      if (httpResponseCode > 0) {
        _retryCount = 0;

        const String payload = http.getString();
        
        http.end();
        return(payload);
      }
      else {
        if (_retryCount > 2){
          logger("Unable to contact server");
          http.end();
          return "0";
        };
        get(path);
      }     
}

template <typename T>
void HttpHandler::logger(T str)
{
  if (_debug)
  {
    Serial.println(str);
  }
}

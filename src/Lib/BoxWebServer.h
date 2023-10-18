#ifndef BOXWEBSERVER_H
#define BOXWEBSERVER_H

#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "Options.h"
#include <SPIFFS.h>
#include "SeaTalk.h"
#include "Commands.h"
#include "CommandStack.h"

class BoxWebServer {

    public:
      BoxWebServer(SeaTalk *seaTalk, Options *options);
      void ProcessCommands();

    private:
      SeaTalk *_seaTalk;
      Options *_options;
      CommandStack _commandStack= CommandStack();
      AsyncWebServer webserver = AsyncWebServer(80);
      void RemoteControlRequest(AsyncWebServerRequest *request);
      void GetOptions(AsyncWebServerRequest *request);
      void SetOptions(AsyncWebServerRequest *request);
      void SendCommand(AsyncWebServerRequest *request);

};

#endif
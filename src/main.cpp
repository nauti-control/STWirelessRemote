#include <Arduino.h>
#include "Lib\RemoteControl.h"
#include "Lib\SeaTalk.h"
#include "Lib\BoxWifi.h"
#include "Lib\BoxWebServer.h"
#include "Lib\Options.h"
#include <SPIFFS.h>

RemoteControl *_remoteControl = nullptr;
SeaTalk *_seaTalk = nullptr;
BoxWifi *_boxWifi = nullptr;
Options *_options = nullptr;

BoxWebServer *_boxWebServer = nullptr;

void setup()
{

  Serial.begin(9600); // Serial out put for function checks with PC
                      // Initialize SPIFFS
  if (!SPIFFS.begin(true))
  {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  _options = new Options();
  _seaTalk = new SeaTalk();
  _remoteControl = new RemoteControl(_seaTalk, _options);
  _boxWifi = new BoxWifi();
  _boxWebServer = new BoxWebServer(_seaTalk, _options);
}

void loop()
{
  _seaTalk->processMessages();
  _remoteControl->processRemote();
  _boxWebServer->ProcessCommands();
}
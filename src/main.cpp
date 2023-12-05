#include <Arduino.h>
#include "Lib\RemoteControl.h"
#include "Lib\SeaTalk.h"
#include "Lib\BoxWifi.h"
#include "Lib\BoxWebServer.h"
#include "Lib\Options.h"
#include "Lib\SignalManager.h"
#include <SPIFFS.h>

RemoteControl *_remoteControl = nullptr;
SeaTalk *_seaTalk = nullptr;
BoxWifi *_boxWifi = nullptr;
Options *_options = nullptr;
SeaTalkData *_seaTalkData=nullptr;
SignalManager *_signalManager = nullptr;
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
  _boxWifi = new BoxWifi();
  _seaTalkData= new SeaTalkData();
  _options = new Options();
  _signalManager= new SignalManager(_seaTalkData);
  _seaTalk = new SeaTalk(_signalManager);
  _remoteControl = new RemoteControl(_seaTalk, _options);
  _boxWebServer = new BoxWebServer(_seaTalk, _options);
}

void loop()
{
  _seaTalk->processMessages();
  _remoteControl->processRemote();
  _boxWebServer->ProcessCommands();
}
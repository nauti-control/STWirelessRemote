#include "BoxWebServer.h"

BoxWebServer::BoxWebServer(SeaTalk *seaTalk, Options *options)
{
    _seaTalk = seaTalk;
    _options = options;
    Serial.println("Settign Up WEb Server");
    webserver.on("/", HTTP_GET, [&](AsyncWebServerRequest *request)
                 {
                     request->send(SPIFFS, "/index.html", "text/html");
                     Serial.println("Index Sent"); });

    webserver.on("/index.html", HTTP_GET, [&](AsyncWebServerRequest *request)
                 {
                    
                      request->send(SPIFFS, "/index.html", "text/html");
                     Serial.println("Index Sent"); });

    webserver.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request)
                 {
                     request->send(SPIFFS, "/style.css", "text/css");
                     Serial.println("CSS Sent"); });

    webserver.on("/jquery-3.6.3.min.js", HTTP_GET, [](AsyncWebServerRequest *request)
                 {
                     request->send(SPIFFS, "/jquery-3.6.3.min.js", "application/javascript");
                     Serial.println("JS Sent"); });

    webserver.on("/GetOptions.json", HTTP_GET, [&](AsyncWebServerRequest *request)
                 { GetOptions(request); });

    webserver.on("/SetOptions.html", HTTP_POST, [&](AsyncWebServerRequest *request)
                 { SetOptions(request); });

    webserver.on("/SendCommand.html", HTTP_GET, [&](AsyncWebServerRequest *request)
                 { SendCommand(request); });
    webserver.serveStatic("/", SPIFFS, "/");
    webserver.begin();
}

void BoxWebServer::SetOptions(AsyncWebServerRequest *request)
{
    Serial.println("Set Web Options");
    WebOptions options = _options->GetWebOptions();

    if (request->hasParam("button1act", true))
    {
        AsyncWebParameter *p = request->getParam("button1act", true);
        options.button1 = p->value().toInt();
        Serial.println("Button1=");
        Serial.println(options.button1);
    }
    if (request->hasParam("button2act", true))
    {
        AsyncWebParameter *p = request->getParam("button2act", true);
        options.button2 = p->value().toInt();
        Serial.println("Button2=");
        Serial.println(options.button2);
    }
    if (request->hasParam("button3act", true))
    {
        AsyncWebParameter *p = request->getParam("button3act", true);
        options.button3 = p->value().toInt();
        Serial.println("Button3=");
        Serial.println(options.button3);
    }
    if (request->hasParam("button4act", true))
    {
        AsyncWebParameter *p = request->getParam("button4act", true);
        options.button4 = p->value().toInt();
    }
    if (request->hasParam("button5act", true))
    {
        AsyncWebParameter *p = request->getParam("button5act", true);
        options.button5 = p->value().toInt();
    }
    if (request->hasParam("button6act", true))
    {
        AsyncWebParameter *p = request->getParam("button6act", true);
        options.button6 = p->value().toInt();
    }
    if (request->hasParam("button7act", true))
    {
        AsyncWebParameter *p = request->getParam("button7act", true);
        options.button7 = p->value().toInt();
    }
    if (request->hasParam("button8act", true))
    {
        AsyncWebParameter *p = request->getParam("button8act", true);
        options.button8 = p->value().toInt();
    }
    if (request->hasParam("timermin", true))
    {
        AsyncWebParameter *p = request->getParam("timermin", true);
        options.timermin = p->value().toInt();
    }
    if (request->hasParam("timersec", true))
    {
        AsyncWebParameter *p = request->getParam("timersec", true);
        options.timersec = p->value().toInt();
    }

   
    _options->SaveWebOptions(options);
    Serial.println("Sending Response");
    request->send(200);
}

void BoxWebServer::GetOptions(AsyncWebServerRequest *request)
{
    WebOptions options = _options->GetWebOptions();
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    response->print("{  \n");
    response->printf("\"button1opt\": %d, \n", options.button1);
    response->printf("\"button2opt\": %d, \n", options.button2);
    response->printf("\"button3opt\": %d, \n", options.button3);
    response->printf("\"button4opt\": %d, \n", options.button4);
    response->printf("\"button5opt\": %d, \n", options.button5);
    response->printf("\"button6opt\": %d, \n", options.button6);
    response->printf("\"button7opt\": %d, \n", options.button7);
    response->printf("\"button8opt\": %d, \n", options.button8);
    response->printf("\"timermin\": %d, \n", options.timermin);
    response->printf("\"timersec\": %d, \n", options.timersec);
    response->print("}");

    request->send(response);
}

void BoxWebServer::SendCommand(AsyncWebServerRequest *request)
{
    // Check if GET parameter exists
    Serial.println(request->method());
    if (request->hasParam("action"))
    {

        AsyncWebParameter *p = request->getParam("action");
        Serial.println("Action Received");

        Serial.println(p->value());
        if (p->value() == "minus1")
        {
            _commandStack.push(minus_1);

            Serial.println("Minus one Web");
        }
        else if (p->value() == "plus1")
        {
            _commandStack.push(plus_1);
            Serial.println("Plus one Web");
        }
        else if (p->value() == "minus10")
        {
            _commandStack.push(minus_10);
            Serial.println("minus ten Web");
        }
        else if (p->value() == "plus10")
        {
            _commandStack.push(plus_10);
            Serial.println("plus ten Web");
        }
        else if (p->value() == "auto")
        {
            _commandStack.push(auto_but);
            Serial.println("auto");
        }
        else if (p->value() == "standby")
        {
            _commandStack.push(standby_but);
            Serial.println("standby");
        }
        else if (p->value() == "starttimer")
        {
            _commandStack.push(start_timer);
            Serial.println("Start Timer");
        }
        else if (p->value() == "wind")
        {
            _commandStack.push(wind_mode);
            Serial.println("Wind Mode");
        }
    }
    request->send(200);
}

// Process Commands On Main Thread
void BoxWebServer::ProcessCommands()
{
    while (!_commandStack.isEmpty())
    {
        commands nextCommand= (commands)_commandStack.pop();
        _seaTalk->sendCommand(nextCommand);
    }
}
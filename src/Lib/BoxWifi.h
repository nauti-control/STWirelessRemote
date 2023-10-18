#ifndef BOXWIFI_H
#define BOXWIFI_H
#include <WiFi.h>


class BoxWifi
{

public:
    BoxWifi();
   

private:
    IPAddress mainServerIP= IPAddress(192, 168, 1, 1);
    IPAddress mainServerGatewayIP=IPAddress(192, 168, 1, 1);
    IPAddress mainServerIPMask=IPAddress(255, 255, 255, 0);
    // Replace with your network credentials
    const char *ssid = "NAUTI-CONTROL";
    const char *password = "123456789";
};
#endif

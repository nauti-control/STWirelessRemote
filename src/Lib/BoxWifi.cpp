#include "BoxWifi.h"

BoxWifi::BoxWifi()
{
  Serial.print("Setting AP (Access Point)…");
 
  WiFi.softAP(ssid, password,1,0,1);

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid,password);
  WiFi.softAPConfig(mainServerIP, mainServerGatewayIP, mainServerIPMask);

  IPAddress IP = WiFi.softAPIP();
  
  Serial.print("AP IP address: ");
  Serial.println(IP);
}

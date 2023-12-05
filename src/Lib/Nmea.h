#ifndef NMEA_H
#define NMEA_H


#include <Arduino.h>
#include "NmeaServer.h"

class Nmea
{

public:
    Nmea();
  
    void updateApparentWindAngle(double apparentWindAngle);
    void updateApparentWindSpeed(double apparentWindSpeed);
    void updateSTW(double stw);
    void updateSOG(double sog);
    void updateCOG(double cog);

private:
    NmeaServer *_nmeaServer;
    void sendNMEA(const char *sentence);
};
#endif
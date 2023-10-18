#ifndef NMEA_H
#define NMEA_H

#include "SeaTalkData.h"
#include <Arduino.h>
#include "NmeaServer.h"

class Nmea
{

public:
    Nmea();
    void updateTrueWind(SeaTalkData seaTalkData);
    void updateApparentWind(SeaTalkData seaTalkData);
    void updateGPS(SeaTalkData seaTalkData);
    void updateSTW(SeaTalkData seaTalkData);
    void updateSOG(SeaTalkData seaTalkData);
    void updateCOG(SeaTalkData seaTalkData);

private:
    NmeaServer *_nmeaServer;
    void sendNMEA(const char *sentence);
};
#endif
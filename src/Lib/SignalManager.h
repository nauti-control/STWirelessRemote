#ifndef SIGNALMANAGER_H
#define SIGNALMANAGER_H

#include "Nmea.h"
#include "models\SeaTalkData.h"

class SignalManager
{

public:
    SignalManager(SeaTalkData *seaTalkData);
    void UpdateApparentWindAngle(double angle);
    void UpdateApparentWindSpeed(double speed);
    void UpdateSpeedThroughWater(double speed);
    void UpdateSpeedOverGround(double speed);
    void UpdateCourseOverGround(double courseOverGround);


private:
    Nmea *_nmea;
    SeaTalkData *_seaTalkData;
   
};

#endif
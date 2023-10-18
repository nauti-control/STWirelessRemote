#ifndef SEATALKDATA_H
#define SEATALKDATA_H

enum AutoPilotModes
{
    standby,
    autom,
    vane,
    track
};

enum TurningDirection
{
    port,
    starboard
};

struct AutoPilotData
{
    double compassHeading;
    AutoPilotModes autoPilotMode;
    TurningDirection turningDirection;
    double autoPilotCourse;
};

struct SeaTalkData
{
    double apparentWindAngle;
    long apparentWindAngleLastUpdated;
    double apparentWindSpeed;
    long apparentWindSpeedLastUpdated;
    double speedThroughWater;
    long speedThroughWaterLastUpdated;
    double speedOverGround;
    long speedOverGroundLastUpdated;
    double courseOverGround;
    long courseOverGroundLastUpdated;
    double depthBelowTransducer;
    long depthBelowTransducerLastUpdated;
    AutoPilotData autoPilotData;
    long autoPilotDataLastUpdated;
};

#endif // SEATALKDATA_H
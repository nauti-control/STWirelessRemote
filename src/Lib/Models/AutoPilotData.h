#ifndef AUTOPILOTDATA_H
#define AUTOPILOTDATA_H

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
#endif
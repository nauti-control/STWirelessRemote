#include "SignalManager.h"


/// @brief Signal Manager Class To Route Seatalk to NMEA as well as update Seatalk Data
/// @param seaTalkData 
SignalManager::SignalManager(SeaTalkData *seaTalkData)
{
    _seaTalkData=seaTalkData;
    _nmea=new Nmea();

}

/// @brief Seatalk Update Wind Angle
/// @param windAngle angle
void SignalManager::UpdateApparentWindAngle(double windAngle)
{
    _seaTalkData->apparentWindAngle = windAngle;
    _nmea->updateApparentWindAngle(windAngle);
}

/// @brief Seatalk Updated Wind Speed
/// @param windSpeed speed
void SignalManager::UpdateApparentWindSpeed(double windSpeed)
{
    _seaTalkData->apparentWindSpeed = windSpeed;
    _nmea->updateApparentWindSpeed(windSpeed);
}

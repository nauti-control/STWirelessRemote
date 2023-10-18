
#include "Nmea.h"

Nmea::Nmea()
{
    _nmeaServer = new NmeaServer();
}

void Nmea::updateApparentWind(SeaTalkData seaTalkData)
{
    char sentence[100];
    snprintf(sentence, sizeof(sentence), "$IIMWV,%.1f,A,%.1f,K,A*", seaTalkData.apparentWindAngle, seaTalkData.apparentWindSpeed);
    sendNMEA(sentence);
}

void Nmea::updateSTW(SeaTalkData seaTalkData)
{
    char sentence[100];
    snprintf(sentence, sizeof(sentence), "$IIVHW,,T,,M,%.1f,N,,K*", seaTalkData.speedThroughWater);
    sendNMEA(sentence);
}

void Nmea::updateSOG(SeaTalkData seaTalkData)
{
    char sentence[100];
    snprintf(sentence, sizeof(sentence), "$IIVTG,,T,,M,%.1f,N,%.1f,K*", seaTalkData.speedOverGround, seaTalkData.speedOverGround * 1.852);
    sendNMEA(sentence);
}

void Nmea::updateCOG(SeaTalkData seaTalkData)
{
    char sentence[100];
    snprintf(sentence, sizeof(sentence), "$IIVTG,%.1f,T,,M,,N,,K*", seaTalkData.courseOverGround);
    sendNMEA(sentence);
}

void Nmea::sendNMEA(const char *sentence)
{
    char sentenceWithChecksum[1024];
    uint8_t checksum = 0;
    for (; *sentence; sentence++)
    {
        checksum ^= *sentence;
    }
    sprintf(sentenceWithChecksum, "%s%02X\n", sentence, checksum);
    // Send Message To Connected Clients
    _nmeaServer->sendMessageToClients(sentenceWithChecksum);
}
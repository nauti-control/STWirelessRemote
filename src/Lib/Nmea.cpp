
#include "Nmea.h"

Nmea::Nmea()
{
    _nmeaServer = new NmeaServer();
}

void Nmea::updateApparentWindAngle(double apparentWindAngle)
{
    char sentence[100];
    snprintf(sentence, sizeof(sentence), "$IIMWV,%.1f,A,,K,A*", apparentWindAngle);
    sendNMEA(sentence);
}

void Nmea::updateApparentWindSpeed(double apparentWindSpeed)
{
    char sentence[100];
    snprintf(sentence, sizeof(sentence), "$IIMWV,,A,%.1f,K,A*",  apparentWindSpeed);
    sendNMEA(sentence);
}

void Nmea::updateSTW(double stw)
{
    char sentence[100];
    snprintf(sentence, sizeof(sentence), "$IIVHW,,T,,M,%.1f,N,,K*", stw);
    sendNMEA(sentence);
}

void Nmea::updateSOG(double sog)
{
    char sentence[100];
    snprintf(sentence, sizeof(sentence), "$IIVTG,,T,,M,%.1f,N,%.1f,K*", sog, sog * 1.852);
    sendNMEA(sentence);
}

void Nmea::updateCOG(double cog)
{
    char sentence[100];
    snprintf(sentence, sizeof(sentence), "$IIVTG,%.1f,T,,M,,N,,K*", cog);
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
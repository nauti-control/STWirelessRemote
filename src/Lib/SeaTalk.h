#ifndef SEATALK_H
#define SEATALK_H
#define BEEP_DURATION 150 // 150 ms beep time
#define MAX_BUF_SIZE 20
#define RX_IN 32
#define TX_OUT 33
#define LED_PIN 2
#define METRES_TO_FEET 3.28084
#define METRES_TO_FATHONS 0.546807
#define FEET_TO_METERS 0.3048

#include <SoftwareSerial.h>
#include "SeaTalkData.h"
#include "Nmea.h"
#include "Commands.h"

class SeaTalk
{

public:
    SeaTalk();

    const uint8_t ST_Minus_1[4] = {0x86, 0x11, 0x05, 0xFA};
    const uint8_t ST_Minus_10[4] = {0x86, 0x11, 0x06, 0xF9};
    const uint8_t ST_Plus_1[4] = {0x86, 0x11, 0x07, 0xF8};
    const uint8_t ST_Plus_10[4] = {0x86, 0x11, 0x08, 0xF7};
    const uint8_t ST_Auto[4] = {0x86, 0x11, 0x01, 0xFE};
    const uint8_t ST_Standby[4] = {0x86, 0x11, 0x02, 0xFD};
    const uint8_t ST_Wind[4] = {0x86, 0x11, 0x23, 0xDC};
    const uint8_t ST_BeepOn[6] = {0xA8, 0x53, 0x80, 0x00, 0x00, 0xD3};
    const uint8_t ST_BeepOff[6] = {0xA8, 0x43, 0x80, 0x00, 0x00, 0xC3};
    const uint8_t ST_TimerStart[5] = {0x59, 0x22, 0x00, 0x05, 0x80};
    void processMessages();
    void sendCommand(commands cmd);
    void sendCompass(float heading);

private:
    SoftwareSerial _mySerial;
    SeaTalkData _seaTalkData;
    Nmea *_nmea;
    int checkBus();
    void checkClearToWrite();
    bool send2ST(const uint8_t cmd[], int bytes);
};

#endif
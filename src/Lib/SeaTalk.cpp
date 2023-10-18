
#include "SeaTalk.h"
#include <vector>

SeaTalk::SeaTalk()
{
    _mySerial.begin(4800, SWSERIAL_8S1, RX_IN, TX_OUT, true, 95, 11);
    //_nmea= new Nmea();
}

void SeaTalk::processMessages()
{

    checkBus();
}

// Receive apparent wind speed from bus
int SeaTalk::checkBus()
{

    static std::vector<uint8_t> message;

    while (_mySerial.available())
    {
        uint8_t inByte = _mySerial.read();
        bool parity = _mySerial.readParity();

        if (parity) // Command byte received
        {
            message.clear(); // Clear previous message
            message.push_back(inByte);
        }
        else if (!message.empty()) // Data byte received
        {
            message.push_back(inByte);

            // Process messages
            // Apparent Wind Angle
            if (message[0] == 0x10 && message.size() == 4)
            {
                _seaTalkData.apparentWindAngle = ((message[2] << 8) | (message[3])) / 2.0;
                _seaTalkData.apparentWindAngle = millis();
                Serial.printf("Apparent Wind Angle: %.1f degrees\n", _seaTalkData.apparentWindAngle);
            }
            // Apparent Wind Speed
            else if (message[0] == 0x11 && message.size() == 4)
            {
                _seaTalkData.apparentWindSpeed = ((message[2] & 0x7f) + (message[3] & 0x0f) / 10.0);
                _seaTalkData.apparentWindSpeedLastUpdated = millis();
                Serial.printf("Apparent Wind Speed: %.1f knots\n", _seaTalkData.apparentWindSpeed);
            }

            // Speed Through Water
            else if (message[0] == 0x20 && message.size() == 4)
            {
                _seaTalkData.speedThroughWater = ((message[3] << 8) | message[2]) / 10;
                _seaTalkData.speedThroughWaterLastUpdated = millis();
                Serial.printf("Speed Through Water: %.1f knots\n", _seaTalkData.speedThroughWater);
            }

            // Speed Over Ground
            else if (message[0] == 0x52 && message.size() == 4)
            {
                _seaTalkData.speedOverGround = ((message[3] << 8) | message[2]) / 10;
                _seaTalkData.speedOverGroundLastUpdated = millis();
                Serial.printf("Speed Over Ground: %.1f knots\n", _seaTalkData.speedOverGround);
            }
            // Course Over Ground
            else if (message[0] == 0x53 && message.size() == 4)
            {
                uint8_t u = (message[1] & 0xf0) >> 4;
                uint8_t vw = message[2];
                _seaTalkData.courseOverGround = (u & 0x3) * 90 + (vw & 0x3F) * 2 + ((u & 0xC) >> 2) / 2;
                _seaTalkData.courseOverGroundLastUpdated = millis();
                Serial.printf("Course Over Ground: %.1f degrees\n", _seaTalkData.courseOverGround);
            }
            // Depth Below Transducer
            else if (message[0] == 0x00 && message.size() == 5)
            {
                _seaTalkData.depthBelowTransducer = (((message[4] >> 8) | message[3]) / 10);
                _seaTalkData.depthBelowTransducerLastUpdated = millis();
                Serial.printf("Depth Below Transducer %.1f Meters\n", _seaTalkData.depthBelowTransducer);
            }

            // Auto Pilot Data
            else if (message[0] == 0x84 && message.size() == 9)
            {
                uint8_t u = (message[1] & 0xf0) >> 4;
                uint8_t vw = message[2];

                AutoPilotData pilotData;
                // Get Compass Heading
                pilotData.compassHeading = (u & 0x3) * 90 + (vw & 0x3F) * 2 + (u & 0xC ? (u & 0xC == 0xC ? 2 : 1) : 0);
                Serial.printf("Auto Compass heading %.1f Degrees\n", pilotData.compassHeading);
                // Get Turning Direction
                uint8_t dir = (u & 0x80) >> 3;
                if (dir == 1)
                {
                    pilotData.turningDirection = TurningDirection::port;
                }
                else
                {
                    pilotData.turningDirection = TurningDirection::starboard;
                }
                Serial.printf("Auto Turning Direction %d \n", pilotData.turningDirection);

                // Get
                uint8_t v = (message[2] & 0xc0) >> 6;
                uint8_t xy = message[3];

                pilotData.autoPilotCourse = (v * 90) + (xy / 2);

                Serial.printf("Auto Pilot Course= %.1f Degrees \n", pilotData.autoPilotCourse);
                uint8_t z = message[4];
                if (z & 0x2 == 0)
                {

                    pilotData.autoPilotMode = standby;
                }
                else if (z & 0x2 == 2)
                {
                    pilotData.autoPilotMode = autom;
                }
                else if (z & 0x2 == 4)
                {
                    pilotData.autoPilotMode = vane;
                }
                else if (z & 0x8 == 8)
                {

                    pilotData.autoPilotMode = track;
                }

                Serial.printf("Auto Pilot Mode = %d ", pilotData.autoPilotMode);

                _seaTalkData.autoPilotData = pilotData;

                _seaTalkData.autoPilotDataLastUpdated = millis();
            }
        }
    }

    return -1;
}

void SeaTalk::sendCommand(commands cmd)
{
    Serial.println(cmd);
    if (cmd == minus_1)
    {
        send2ST(ST_Minus_1, 4);
    }
    else if (cmd == plus_1)
    {
        send2ST(ST_Plus_1, 4);
    }
    else if (cmd == minus_10)
    {
        send2ST(ST_Minus_10, 4);
    }
    else if (cmd == plus_10)
    {
        send2ST(ST_Plus_10, 4);
    }
    else if (cmd == auto_but)
    {
        send2ST(ST_Auto, 4);
    }
    else if (cmd == standby_but)
    {
        send2ST(ST_Standby, 4);
    }
    else if (cmd == start_timer)
    {
        send2ST(ST_TimerStart, 5);
    }
    else if (cmd == wind_mode)
    {
        send2ST(ST_Wind, 4);
    }
}

// Send compass heading to Seatalk
void SeaTalk::sendCompass(float heading)
{
    uint16_t headingTenths = heading * 10; // Convert to tenths of a degree
    uint8_t message[] = {
        0x9C,                            // Compass heading message code
        0x02,                            // Data length
        (uint8_t)(headingTenths & 0xFF), // Low byte
        (uint8_t)(headingTenths >> 8)    // High byte
    };
    send2ST(message, sizeof(message));
}

// Send To Seatalk
bool SeaTalk::send2ST(const uint8_t cmd[], int bytes)
{
    int j = 0;
    boolean ok = true;
    // Retry 5 Times
    while (j < 5)
    {
        checkClearToWrite();
        digitalWrite(LED_PIN, HIGH);
        for (int i = 0; (i < bytes) & (ok); i++)
        {
            (i == 0) ? _mySerial.write(cmd[i], SWSERIAL_PARITY_MARK) : _mySerial.write(cmd[i], SWSERIAL_PARITY_SPACE);
            delay(1);
            if (_mySerial.available())
            {
                uint8_t nextByte = _mySerial.read();
                if (nextByte != cmd[i])
                {
                    Serial.printf("Failed Byte Sent = %x byte received= %x \n", cmd[i], nextByte);
                    ok = false;
                }
            }
            else
            {
                Serial.println("Serial Not Available");
                ok = false;
            }
        }

        if (ok)
        {
            digitalWrite(LED_PIN, LOW);
            delay(100);

            Serial.println("Command Sent");
            return ok;
        }
        j++; // Collision detected
        Serial.println("Collision Detected");
        delay(random(2, 50));
        ok = true;
    }

    Serial.println("Send Failed");
    return false;
}

// wait to serial line clear
void SeaTalk::checkClearToWrite()
{

    while (_mySerial.available())
    { // Wait for silence on the bus
        uint8_t inbyte = _mySerial.read();
        delay(3);
    }
    Serial.println("Clear To Send");
}

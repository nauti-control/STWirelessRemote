#ifndef REMOTECONTROL_H
#define REMOTECONTROL_H
#include <Arduino.h>
#include <RCSwitch.h>
#include "SeaTalk.h"
#include "Options.h"
#include "Commands.h"

#define KEY_DELAY 300 // 300 ms break between keys
#define BEEP_DURATION 150  // 150 ms beep time



class RemoteControl
{

public:
    RemoteControl(SeaTalk *seaTalk,Options *options);
    void processRemote();

private:
    SeaTalk *_seaTalk;
    Options *_options;
    RCSwitch _mySwitch = RCSwitch();
    unsigned long _beep_time = 0; // timer for beep duration
    unsigned long _beep_timer2 = 0;  // timer to stop alarm sound
    bool _beep_status = false;
    unsigned long _key_time = 0;                        // time of last key detected
    const unsigned long _button1= 2548136;
    const unsigned long _button2= 2548132;
    const unsigned long _button3= 2548140;
    const unsigned long _button4= 2548130;
    const unsigned long _button5= 2548138;
    const unsigned long _button6= 2548134;
    const unsigned long _button7= 2548142;
    const unsigned long _button8= 2548129;
    commands GetCommand(unsigned long value);


};

#endif
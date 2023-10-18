#include "RemoteControl.h"

RemoteControl::RemoteControl(SeaTalk *seaTalk, Options *options)
{
    _seaTalk = seaTalk;
    _options = options;
    _mySwitch.enableReceive(34); // RF Receiver on inerrupt 4 => that is pin 7 on Micro
}

void RemoteControl::processRemote()
{
    unsigned long value = 0;

    if (_mySwitch.available())
    {
        value = _mySwitch.getReceivedValue();
        Serial.println("Keypad Received");
        Serial.printf("Keypad Value %lu", value);
        Serial.println("Received");
        commands command = GetCommand(value);
        _seaTalk->sendCommand(command);
        _mySwitch.resetAvailable();
    }
}

commands RemoteControl::GetCommand(unsigned long value)
{

    WebOptions options = _options->GetWebOptions();

    commands command;
    if (value == _button1)
    {
        command = (commands)options.button1;
    }
    else if (value == _button2)
    {
        command = (commands)options.button2;
    }
    else if (value == _button3)
    {
        command = (commands)options.button3;
    }
    else if (value == _button4)
    {
        command = (commands)options.button4;
    }
    else if (value == _button5)
    {
        command = (commands)options.button5;
    }
    else if (value == _button6)
    {
        command = (commands)options.button6;
    }
    else if (value == _button7)
    {
        command = (commands)options.button7;
    }
    else if (value == _button8)
    {
        command = (commands)options.button8;
    }
    Serial.println(command);
    return command;
}
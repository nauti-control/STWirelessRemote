#include "Options.h"

Options::Options()
{
    _preferences.begin("NautiControl", false);
}

void Options::SaveWebOptions(WebOptions webOptions)
{
    _preferences.putInt("button1", webOptions.button1);
    _preferences.putInt("button2", webOptions.button2);
    _preferences.putInt("button3", webOptions.button3);
    _preferences.putInt("button4", webOptions.button4);
    _preferences.putInt("button5", webOptions.button5);
    _preferences.putInt("button6", webOptions.button6);
    _preferences.putInt("button7", webOptions.button7);
    _preferences.putInt("button8", webOptions.button8);
    _preferences.putInt("timermin", webOptions.timermin);
    _preferences.putInt("timersec", webOptions.timersec);
    _preferences.putBool("enableRemoteCompass", webOptions.enableRemoteCompass);
}

WebOptions Options::GetWebOptions()
{
    Serial.println("Getting Options");
    WebOptions webOptions;
    if (_preferences.isKey("button1"))
    {

        webOptions.button1 = _preferences.getInt("button1", 0);
    }
    if (_preferences.isKey("button2"))
    {
        webOptions.button2 = _preferences.getInt("button2", 1);
    }
    if (_preferences.isKey("button3"))
    {
        webOptions.button3 = _preferences.getInt("button3", 2);
    }
    if (_preferences.isKey("button4"))
    {
        webOptions.button4 = _preferences.getInt("button4", 3);
    }
    if (_preferences.isKey("button5"))
    {
        webOptions.button5 = _preferences.getInt("button5", 4);
    }
    if (_preferences.isKey("button6"))
    {
        webOptions.button6 = _preferences.getInt("button6", 5);
    }
    if (_preferences.isKey("button7"))
    {
        webOptions.button7 = _preferences.getInt("button7", 6);
    }
    if (_preferences.isKey("button8"))
    {
        webOptions.button8 = _preferences.getInt("button8", 6);
    }
    if (_preferences.isKey("timermin"))
    {
        webOptions.timermin = _preferences.getInt("timermin", 7);
    }
    if (_preferences.isKey("timersec"))
    {
        webOptions.timersec = _preferences.getInt("timersec", 0);
    }
    if (_preferences.isKey("enableRemoteCompass"))
    {
        webOptions.enableRemoteCompass = _preferences.getBool("enableRemoteCompass,false");
    }
    return webOptions;
}
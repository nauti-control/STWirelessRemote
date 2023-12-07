#include "Options.h"

/// @brief Options class constructor
Options::Options()
{
    _preferences.begin("NautiControl", false);
}

/// @brief Save Web Options
/// @param webOptions options
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
}

/// @brief Get the web options from storage
/// @return options
WebOptions Options::GetWebOptions()
{
    Serial.println("Getting Options");
    WebOptions webOptions;
    if (_preferences.isKey("button1"))
    {

        webOptions.button1 = _preferences.getInt("button1", 0);
    }
    else
    {
        webOptions.button1 = 0;
    }

    if (_preferences.isKey("button2"))
    {
        webOptions.button2 = _preferences.getInt("button2", 1);
    }
    else
    {
        webOptions.button2 = 1;
    }
    if (_preferences.isKey("button3"))
    {
        webOptions.button3 = _preferences.getInt("button3", 2);
    }
    else
    {
        webOptions.button3 = 2;
    }
    if (_preferences.isKey("button4"))
    {
        webOptions.button4 = _preferences.getInt("button4", 3);
    }
    else
    {
        webOptions.button4 = 3;
    }
    if (_preferences.isKey("button5"))
    {
        webOptions.button5 = _preferences.getInt("button5", 4);
    }
    else
    {
        webOptions.button5 = 4;
    }
    if (_preferences.isKey("button6"))
    {
        webOptions.button6 = _preferences.getInt("button6", 5);
    }
    else
    {
        webOptions.button6 = 5;
    }
    if (_preferences.isKey("button7"))
    {
        webOptions.button7 = _preferences.getInt("button7", 6);
    }
    else
    {
        webOptions.button7 = 6;
    }
    if (_preferences.isKey("button8"))
    {
        webOptions.button8 = _preferences.getInt("button8", 7);
    }
    else
    {
        webOptions.button8 = 7;
    }
    if (_preferences.isKey("timermin"))
    {
        webOptions.timermin = _preferences.getInt("timermin", 5);
    }
    else
    {
        webOptions.timermin = 5;
    }
    if (_preferences.isKey("timersec"))
    {
        webOptions.timersec = _preferences.getInt("timersec", 0);
    }
    else
    {
        webOptions.timersec = 0;
    }

    return webOptions;
}
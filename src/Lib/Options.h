#ifndef OPTIONS_H
#define OPTIONS_H

#include <Preferences.h>
#include "Models\WebOptions.h"

class Options
{

public:
    Options();

    void SaveWebOptions(WebOptions webOptions);
    WebOptions GetWebOptions();

private:
    Preferences _preferences;
    void CreateDefaults();
};

#endif
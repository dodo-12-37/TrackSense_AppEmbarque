#pragma once
#include <Arduino.h>
#include "Interfaces/ICompass.h"



class CompassHMC5883L : ICompass
{
private:
    /* data */
public:
    CompassHMC5883L();
    ~CompassHMC5883L();
};

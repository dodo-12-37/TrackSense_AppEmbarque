#pragma once
#include <Arduino.h>
#include "Interfaces/ICompass.h"
#include "Configurations.h"
#include "TSProperties.h"



class CompassHMC5883L : public ICompass
{
private:
    TSProperties* _TSProperties;

public:
    CompassHMC5883L(TSProperties* TSProperties);
    ~CompassHMC5883L();

    void tick() override;
};

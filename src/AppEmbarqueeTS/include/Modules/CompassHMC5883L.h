#pragma once
#include <Arduino.h>
#include "Interfaces/ICompass.h"
#include "Configurations.h"
#include "TrackSenseProperties.h"



class CompassHMC5883L : ICompass
{
private:
    TrackSenseProperties* _trackSenseProperties;

public:
    CompassHMC5883L(TrackSenseProperties* trackSenseProperties);
    ~CompassHMC5883L();

    void tick() const override;
};

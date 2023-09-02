#pragma once
#include <Arduino.h>
#include "Interfaces/IGPS.h"
#include "Configurations.h"
#include "TrackSenseProperties.h"



class GPSTinyPlus : IGPS
{
private:
    TrackSenseProperties* _trackSenseProperties;

public:
    GPSTinyPlus(TrackSenseProperties* trackSenseProperties);
    ~GPSTinyPlus();

    // void test() const override;
    void tick() const override;
};

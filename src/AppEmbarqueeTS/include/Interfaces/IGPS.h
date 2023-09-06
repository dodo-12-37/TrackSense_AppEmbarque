#pragma once
#include "TrackSenseProperties.h"



class IGPS
{
public:
    virtual void tick() = 0;

    virtual void gpsPowerOn() = 0;
    virtual void gpsPowerOff() = 0;
    virtual void gpsRestart() = 0;
};

#pragma once
#include "TrackSenseProperties.h"



class IGSM
{
public:
    virtual void init() = 0;
    virtual void tick() = 0;

    // virtual void gpsPowerOn() = 0;
    // virtual void gpsPowerOff() = 0;
    // virtual void gpsRestart() = 0;
};

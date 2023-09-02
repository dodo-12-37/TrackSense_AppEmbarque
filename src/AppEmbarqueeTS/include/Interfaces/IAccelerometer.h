#pragma once
#include "TrackSenseProperties.h"



class IAccelerometer
{
public:
    virtual void tick() const = 0;
};

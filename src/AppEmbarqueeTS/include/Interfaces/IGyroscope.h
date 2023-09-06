#pragma once
#include "TrackSenseProperties.h"



class IGyroscope
{
public:
    virtual void tick() = 0;
};

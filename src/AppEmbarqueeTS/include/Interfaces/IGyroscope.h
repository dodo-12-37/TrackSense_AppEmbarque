#pragma once
#include "TrackSenseProperties.h"



class IGyroscope
{
public:
    virtual void tick() const = 0;
};

#pragma once
#include "TrackSenseProperties.h"



class ICompass
{
public:
    virtual void tick() const = 0;
};

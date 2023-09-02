#pragma once
#include "TrackSenseProperties.h"



class IBuzzer
{
public:
    virtual void tick() const = 0;
};

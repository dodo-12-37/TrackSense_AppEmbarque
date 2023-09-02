#pragma once
#include "TrackSenseProperties.h"



class ISDCard
{
public:
    virtual void init() = 0;
    virtual void tick() = 0;
};

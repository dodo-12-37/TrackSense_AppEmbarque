#pragma once
#include "TrackSenseProperties.h"



class IButton
{
public:
    // virtual void tick() const = 0;
    virtual int getState() = 0;
};

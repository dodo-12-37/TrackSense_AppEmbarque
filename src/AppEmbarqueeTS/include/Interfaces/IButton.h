#pragma once
#include "TrackSenseProperties.h"



class IButton
{
public:
    // virtual void tick() const = 0;
    virtual int getFinalState(bool isPressedOtherButton) = 0;
    virtual bool getIsPressedButton() = 0;
};

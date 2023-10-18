#pragma once
#include "TSProperties.h"



class IButton
{
public:
    // virtual void tick() = 0;
    virtual int getFinalState() = 0;
    // virtual bool getIsPressedButton() = 0;
};

#pragma once
#include "TSProperties.h"



class IGyroscope
{
public:
    virtual void tick() = 0;
};

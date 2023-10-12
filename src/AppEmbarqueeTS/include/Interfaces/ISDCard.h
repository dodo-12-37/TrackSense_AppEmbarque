#pragma once
#include "TSProperties.h"



class ISDCard
{
public:
    virtual void init() = 0;
    virtual void tick() = 0;
};

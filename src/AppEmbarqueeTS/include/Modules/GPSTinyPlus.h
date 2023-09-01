#pragma once
#include <Arduino.h>
#include "Interfaces/IGPS.h"



class GPSTinyPlus : IGPS
{
private:
    /* data */
public:
    GPSTinyPlus();
    ~GPSTinyPlus();
};

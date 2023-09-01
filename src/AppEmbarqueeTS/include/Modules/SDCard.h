#pragma once
#include <Arduino.h>
#include "Interfaces/ISDCard.h"



class SDCard : ISDCard
{
private:
    /* data */
public:
    SDCard();
    ~SDCard();
};

#pragma once
#include <Arduino.h>
#include "Interfaces/IButton.h"



class ButtonTactile : public IButton
{
private:
    /* data */
public:
    ButtonTactile();
    ~ButtonTactile();
};

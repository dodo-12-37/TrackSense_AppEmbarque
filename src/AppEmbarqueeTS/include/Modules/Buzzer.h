#pragma once
#include <Arduino.h>
#include "Interfaces/IBuzzer.h"
#include "Configurations.h"
#include "TSProperties.h"



class Buzzer : public IBuzzer
{
private:
    TSProperties* _TSProperties;

public:
    Buzzer(TSProperties* TSProperties);
    ~Buzzer();

    void tick() override;
};

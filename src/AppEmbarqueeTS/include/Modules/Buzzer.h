#pragma once
#include <Arduino.h>
#include "Interfaces/IBuzzer.h"
#include "Configurations.h"
#include "TrackSenseProperties.h"



class Buzzer : IBuzzer
{
private:
    TrackSenseProperties* _trackSenseProperties;

public:
    Buzzer(TrackSenseProperties* trackSenseProperties);
    ~Buzzer();

    void tick() const override;
};

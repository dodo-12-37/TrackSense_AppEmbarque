#pragma once
#include <Arduino.h>
#include "Interfaces/IBLE.h"
#include "Configurations.h"
#include "TrackSenseProperties.h"



class BLE : public IBLE
{
private:
    TrackSenseProperties* _trackSenseProperties;

public:
    BLE(TrackSenseProperties* trackSenseProperties);
    ~BLE();

    void tick() const override;
};

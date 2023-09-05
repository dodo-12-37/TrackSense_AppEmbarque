#pragma once
#include <Arduino.h>
#include "Interfaces/IGPS.h"
#include "Configurations.h"
#include "TrackSenseProperties.h"
#include <TinyGPS++.h>



class GPSTinyPlus : public IGPS
{
private:
    TrackSenseProperties *_trackSenseProperties;
    TinyGPSPlus *_GPS;

    bool readDatas() const;

public:
    GPSTinyPlus(TrackSenseProperties *trackSenseProperties);
    ~GPSTinyPlus();

    // void test() const override;
    void tick() override;
};

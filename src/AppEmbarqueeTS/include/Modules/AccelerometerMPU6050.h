#pragma once
#include <Arduino.h>
#include "Interfaces/IAccelerometer.h"
#include "Configurations.h"
#include "TrackSenseProperties.h"



class AccelerometerMPU6050 : public IAccelerometer
{
private:
    TrackSenseProperties* _trackSenseProperties;

public:
    AccelerometerMPU6050(TrackSenseProperties* trackSenseProperties);
    ~AccelerometerMPU6050();

    void tick() const override;
};
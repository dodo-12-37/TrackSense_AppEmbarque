#pragma once
#include <Arduino.h>
#include "Interfaces/IGyroscope.h"
#include "Configurations.h"
#include "TrackSenseProperties.h"



class GyroscopeMPU6050 : public IGyroscope
{
private:
    TrackSenseProperties* _trackSenseProperties;

public:
    GyroscopeMPU6050(TrackSenseProperties* trackSenseProperties);
    ~GyroscopeMPU6050();

    void tick() const override;
};

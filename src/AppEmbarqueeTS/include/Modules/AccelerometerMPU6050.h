#pragma once
#include <Arduino.h>
#include "Interfaces/IAccelerometer.h"
#include "Configurations.h"
#include "TSProperties.h"



class AccelerometerMPU6050 : public IAccelerometer
{
private:
    TSProperties* _TSProperties;

public:
    AccelerometerMPU6050(TSProperties* TSProperties);
    ~AccelerometerMPU6050();

    void tick() override;
};
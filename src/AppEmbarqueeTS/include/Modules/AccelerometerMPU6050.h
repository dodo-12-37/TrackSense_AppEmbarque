#pragma once
#include <Arduino.h>
#include "Interfaces/IAccelerometer.h"



class AccelerometerMPU6050 : IAccelerometer
{
private:
    /* data */
public:
    AccelerometerMPU6050();
    ~AccelerometerMPU6050();
};
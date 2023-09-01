#pragma once
#include <Arduino.h>
#include "Interfaces/IGyroscope.h"



class GyroscopeMPU6050 : IGyroscope
{
private:
    /* data */
public:
    GyroscopeMPU6050();
    ~GyroscopeMPU6050();
};

#pragma once
#include <Arduino.h>
#include "Interfaces/IGyroscope.h"
#include "Configurations.h"
#include "TSProperties.h"



class GyroscopeMPU6050 : public IGyroscope
{
private:
    TSProperties* _TSProperties;

public:
    GyroscopeMPU6050(TSProperties* TSProperties);
    ~GyroscopeMPU6050();

    void tick() override;
};

#pragma once
#include <Arduino.h>
#include "Configurations.h"
#include "TSProperties.h"
#include "ControlerButtons.h"

// #include "Modules/LTE.h"
#include "Modules/GSMTiny.h"
#include "Modules/SDCard.h"
#include "Modules/GyroscopeMPU6050.h"
#include "Modules/CompassHMC5883L.h"
#include "Modules/AccelerometerMPU6050.h"
#include "Modules/BLE.h"
#include "Modules/ScreenGC9A01.h"
#include "Modules/Buzzer.h"



class Program
{
private:
    TSProperties *_TSProperties;
    // ILTE *_lte;
    // IGPS *_gps;
    IGSM *_gsm;
    ISDCard *_sdCard;
    IGyroscope *_gyroscope;
    ICompass *_compass;
    IAccelerometer *_accelerometer;
    IBLE *_ble;
    IScreen *_screen;
    IBuzzer *_buzzer;
    ControlerButtons *_controlerButtons;

    void initProperties();

public:
    Program();
    ~Program();

    void execute();
};

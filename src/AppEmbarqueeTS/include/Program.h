#pragma once
#include <Arduino.h>
#include "Configurations.h"
#include "TrackSenseProperties.h"
#include "ControlerButtons.h"

#include "Modules/LTE.h"
#include "Modules/GPSTinyPlus.h"
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
    TrackSenseProperties *_trackSenseProperties;
    LTE *_lte;
    GPSTinyPlus *_gps;
    SDCard *_sdCard;
    GyroscopeMPU6050 *_gyroscope;
    CompassHMC5883L *_compass;
    AccelerometerMPU6050 *_accelerometer;
    BLE *_ble;
    ScreenGC9A01 *_screen;
    Buzzer *_buzzer;
    ControlerButtons *_controlerButtons;

    void initProperties();

public:
    Program();
    ~Program();

    void execute();
};

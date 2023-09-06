#pragma once
#include <Arduino.h>
#include "Interfaces/IGSM.h"
#include "Configurations.h"
#include "TrackSenseProperties.h"
#include <TinyGsmClient.h>



class GSMTiny : public IGSM
{
private:
    TrackSenseProperties *_trackSenseProperties;
    TinyGsm *modem;

    float _lat;
    float _long;
    float _speed;
    float _alt;
    int _vsat;
    int _usat;
    float _accuracy;
    int _year;
    int _month;
    int _day;
    int _hour;
    int _min;
    int _sec;

    bool readDatas();
    void gpsPowerOn();
    void gpsPowerOff();
    void gpsRestart();

public:
    GSMTiny(TrackSenseProperties *trackSenseProperties);
    ~GSMTiny();

    void init();
    void tick() override;

};

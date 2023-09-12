#pragma once
#include <Arduino.h>
#include "Interfaces/IGSM.h"
#include "Configurations.h"
#include "TSProperties.h"
#include <TinyGsmClient.h>



class GSMTiny : public IGSM
{
private:
    TSProperties *_TSProperties;
    TinyGsm *modem;

    bool _isInitialized;
    bool _isGpsOn;
    bool _isModemOn;
    bool _isFixIsValid; // ???

    // int _pointId;

    float _latitude;
    float _longitude;
    float _altitude;
    float _speed;
    int _visibleSatellites;
    int _usedSatellites;
    float _accuracy;
    int _year;
    int _month;
    int _day;
    int _hour;
    int _minute;
    int _seconde;

    int _TEST_counterGoodValue;
    int _TEST_counterTotal;

    String getDate();
    String getTime();
    String getDatetime();

    void modemPowerOn();
    void modemPowerOff();
    void modemRestart();

    bool readDatas();
    void gpsPowerOn();
    void gpsPowerOff();
    void gpsRestart();
    void setWorkModeGPS();

    bool isFixValid();
    void saveFixToTSProperties();

public:
    GSMTiny(TSProperties *TSProperties);
    ~GSMTiny();

    void init() override;
    void tick() override;
    bool isInitialized() override;

};

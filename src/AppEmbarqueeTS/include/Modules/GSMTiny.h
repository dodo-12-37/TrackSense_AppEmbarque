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
    bool _isGPSFixed;

    double _distanceMetersBetweenLastPointAndCurrentPoint;
    unsigned long _maxDistanceTresholdInMeters;

    unsigned long _lastReadTimeMS;

    unsigned long _durationS;
    unsigned long _maxDurationTresholdInSeconds;

    double _lastValidLatitude;
    double _lastValidLongitude;

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
    bool isGPSFixed();
    void saveGPSDatasToTSProperties();
    void saveCurrentRideDatasToTSProperties();

    /* Méthode provient de TinyGPS++ */
    double distanceBetweenInMeters(double lat1, double long1, double lat2, double long2);

public:
    GSMTiny(TSProperties *TSProperties);
    ~GSMTiny();

    void init() override;
    void tick() override;
    bool isInitialized() override;
};

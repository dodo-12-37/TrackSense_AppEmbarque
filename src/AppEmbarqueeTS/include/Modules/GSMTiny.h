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

    // TinyGsm modem(SerialAT);

    bool readDatas() const;

public:
    GSMTiny(TrackSenseProperties *trackSenseProperties);
    ~GSMTiny();

    void tick() override;

    void gpsPowerOn() override;
    void gpsPowerOff() override;
    void gpsRestart() override;
};

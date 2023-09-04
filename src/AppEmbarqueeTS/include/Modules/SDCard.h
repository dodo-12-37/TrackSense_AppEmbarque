#pragma once
#include <Arduino.h>
#include "Interfaces/ISDCard.h"
#include "Configurations.h"
#include "TrackSenseProperties.h"
#include <SPI.h>
#include <SD.h>




class SDCard : public ISDCard
{
private:
    TrackSenseProperties* trackSenseProperties;
    // SD* _sd;

public:
    SDCard(TrackSenseProperties* trackSenseProperties);
    ~SDCard();

    void init() override;
    void tick() override;
};

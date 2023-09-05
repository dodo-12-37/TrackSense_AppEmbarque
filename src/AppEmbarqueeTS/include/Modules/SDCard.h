#pragma once

#include <SPI.h>
#include <SD.h>
#include <Arduino.h>

#include "Interfaces/ISDCard.h"
#include "Configurations.h"
#include "TrackSenseProperties.h"

class SDCard : public ISDCard
{
private:
    TrackSenseProperties* trackSenseProperties;
    // SD* _sd;

    int _nbFiles;
    File _currentFile;

    void checkFiles();

public:
    SDCard(TrackSenseProperties* trackSenseProperties);
    ~SDCard();

    void init() override;
    void tick() override;
};

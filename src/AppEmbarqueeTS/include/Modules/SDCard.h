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
    TrackSenseProperties* _trackSenseProperties;
    // SD* _sd;

    int _nbFiles;
    bool _isRideStarted;
    File _currentPointsFile;
    String _currentPointsFileName;
    String _currentStatsFileName;

    void checkFiles();
    void createRideFiles();
    void writeStatsFile();
    void writePoint();
    void setStatsToSendFromFile();
    void setPointsToSendFromFile();

public:
    SDCard(TrackSenseProperties* trackSenseProperties);
    ~SDCard();

    void init() override;
    void tick() override;
};

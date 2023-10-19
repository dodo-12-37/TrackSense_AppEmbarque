#pragma once

#include <SPI.h>
#include <SD.h>
#include <Arduino.h>

// #include "Interfaces/ISDCard.h"
// #include "Configurations.h"
// #include "TSProperties.h"
// #include "StringQueue.h"

class SDCard
{
private:
    // TSProperties* _TSProperties;
    // SD* _sd;

    // StringQueue _queueCompletedRideIds;
    int _nbRidesInSDCard;
    bool _isRideStarted;
    File _currentPointsFile;
    String _currentPointsFileName;
    String _currentStatsFileName;

    File _currentFileSendPoints;
    unsigned long _positionCursorFileSendPoints;
    bool _isSendingRide;
    bool _isSendingPoints;

    bool IsSDCardConnected;

    void createRideFiles();
    void writePoint(float batteryVoltage, int batteryPourcent);


public:
    // SDCard(TSProperties* TSProperties);
    SDCard();
    ~SDCard();

    void init();
    void tick(float batteryVoltage, int batteryPourcent);
};

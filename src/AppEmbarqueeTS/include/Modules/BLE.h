#pragma once

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLESecurity.h>
#include <BLE2902.h>

#include "Interfaces/IBLE.h"
#include "Configurations.h"
#include "TSProperties.h"

class BLE 
    : public IBLE
{
private:
    TSProperties* _TSProperties;

    BLEServer* _serverBLE;
    BLEAdvertising* _advertisingBLE;

    BLEService* _completedRideService;

    BLECharacteristic* _CRDataCaracteristic;
    BLECharacteristic* _CRNotificationCaracteristic;

    BLEDescriptor* _CRDataDescriptor;
    BLEDescriptor* _CRNotificationDescriptor;

    unsigned long _lastTimeStatsSent;
    unsigned long _lastTimePointSent;
    unsigned long _lastTimeAdvertiesingStarted;

    bool _isBLEOnStandy;

    void initBLE();
    void initAdvertising();
    void initCompletedRideService();
    void initCompletedRideCaracteristics();
    void initCompletedRideDescriptors();
    void sendCompletedRideStats();
    void sendCompletedRideCurrentPoint();
    void confirmPointReceived();

public:
    static bool isDeviceConnected;
    static bool isCompletedRideStatsSending;
    static bool isCompletedRideStatsReceived;
    static bool isCompletedRidePointSending;
    static bool isCompletedRidePointReceived;
    static bool isAdvertiesingStarted;
    static int currentPointNumber;

    BLE(TSProperties* TSProperties);
    ~BLE();

    void tick() override;
};

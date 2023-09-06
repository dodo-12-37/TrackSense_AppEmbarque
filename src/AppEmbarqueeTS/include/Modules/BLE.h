#pragma once

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLESecurity.h>
#include <BLE2902.h>

#include "Interfaces/IBLE.h"
#include "Configurations.h"
#include "TrackSenseProperties.h"

class BLE 
    : public IBLE
{
private:
    TrackSenseProperties* _trackSenseProperties;

    BLEServer* _serverBLE;
    BLEAdvertising* _advertisingBLE;

    BLEService* _completedRideService;

    BLECharacteristic* _CRStatsCaracteristic;
    BLECharacteristic* _CRPointCaracteristic;
    BLECharacteristic* _CRPointNumberCaracteristic;
    BLECharacteristic* _CRIsReadyCaracteristic;
    BLECharacteristic* _CRIsReceivedCaracteristic;

    BLEDescriptor* _CRStatsDescriptor;
    BLEDescriptor* _CRPointDescriptor;
    BLEDescriptor* _CRPointNumberDescriptor;
    BLEDescriptor* _CRIsReadyDescriptor;
    BLEDescriptor* _CRIsReceivedDescriptor;

    void initBLE();
    void initAdvertising();
    void initCompletedRideService();
    void initCompletedRideCaracteristics();
    void initCompletedRideDescriptors();
    void sendCompletedRideStats();
    void sendCompletedRideCurrentPoint();

public:
    static bool isDeviceConnected;
    static bool isCompletedRideStatsSending;
    static bool isCompletedRideStatsReceived;
    static bool isCompletedRidePointSending;
    static bool isCompletedRidePointReceived;

    BLE(TrackSenseProperties* trackSenseProperties);
    ~BLE();

    void tick() override;
};

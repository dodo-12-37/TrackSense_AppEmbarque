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
    BLECharacteristic* _CRPointsCaracteristic;
    BLECharacteristic* _CRIsReadyCaracteristic;
    BLECharacteristic* _CRIsReceivedCaracteristic;
    BLEDescriptor* _CRStatsDescriptor;
    BLEDescriptor* _CRPointsDescriptor;
    BLEDescriptor* _CRIsReadyDescriptor;
    BLEDescriptor* _CRIsReceivedDescriptor;

    // BLECharacteristic* _CRIdCaracteristic;
    // BLECharacteristic* _CRRouteIdCaracteristic;
    // BLECharacteristic* _CRMaxSpeedCaracteristic;
    // BLECharacteristic* _CRAVGSpeedCaracteristic;
    // BLECharacteristic* _CRDistanceCaracteristic;
    // BLECharacteristic* _CRDurationCaracteristic;
    // BLECharacteristic* _CRDateBeginCaracteristic;
    // BLECharacteristic* _CRDateEndCaracteristic;
    // BLECharacteristic* _CRNbPointsCaracteristic;
    // BLECharacteristic* _CRNbFallsCaracteristic;

    void initBLE();
    void initAdvertising();
    void initCompletedRideService();
    void initCompletedRideCaracteristics();
    void initCompletedRideDescriptors();
    void sendCompletedRide();


public:
    static bool isDeviceConnected;
    static bool isCompletedRideReceived;

    BLE(TrackSenseProperties* trackSenseProperties);
    ~BLE();

    void tick() override;
};

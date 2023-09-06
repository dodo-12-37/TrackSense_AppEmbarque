#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
// #include <BLESecurity.h>
// #include <BLE2902.h>

#include "Modules/BLE.h"
#include "Configurations.h"


/*----- Definition des membres statics -----*/
bool BLE::isDeviceConnected = false;
bool BLE::isCompletedRideStatsSending = false;
bool BLE::isCompletedRideStatsReceived = false;
bool BLE::isCompletedRidePointSending = false;
bool BLE::isCompletedRidePointReceived = false;

/*----- CallBacks -----*/
class ServerBLECallbacks
    : public BLEServerCallbacks
{
    void onConnect(BLEServer *p_server)
    {
        BLE::isDeviceConnected = true;
        Serial.println("Connecte");
    }

    void onDisconnect(BLEServer *p_server)
    {
        BLE::isDeviceConnected = false;
        Serial.println("Deconnecte");
    }
};

class CompletedRideReceiveStatsCallbacks
    : public BLECharacteristicCallbacks
{
    void onWrite(BLECharacteristic *p_characteristic)
    {
        std::string receivedData = p_characteristic->getValue();
        std::string falseString = BLE_FALSE;

        if (receivedData.compare(falseString) == 0)
        {
            BLE::isCompletedRideStatsReceived = true;
            BLE::isCompletedRideStatsSending = false;
        }
    }
};

class CompletedRideReceivePointCallbacks
    : public BLECharacteristicCallbacks
{
    void onWrite(BLECharacteristic *p_characteristic)
    {
        std::string receivedData = p_characteristic->getValue();
        std::string okString = BLE_OK;

        if (receivedData.compare(okString) == 0)
        {
            p_characteristic->setValue("");
            BLE::isCompletedRidePointReceived = true;
            BLE::isCompletedRidePointSending = false;
        }
    }
};

/*----- BLE -----*/
BLE::BLE(TrackSenseProperties* trackSenseProperties) 
    : _trackSenseProperties(trackSenseProperties),
    _serverBLE(nullptr),
    _advertisingBLE(nullptr),
    _completedRideService(nullptr),
    _CRStatsCaracteristic(nullptr),
    _CRPointCaracteristic(nullptr),
    _CRPointNumberCaracteristic(nullptr),
    _CRIsReadyCaracteristic(nullptr),
    _CRStatsDescriptor(nullptr),
    _CRPointDescriptor(nullptr),
    _CRPointNumberDescriptor(nullptr),
    _CRIsReadyDescriptor(nullptr)
{
    this->initBLE();
    this->initCompletedRideService();
    this->initCompletedRideCaracteristics();
    this->initCompletedRideDescriptors();
    this->_completedRideService->start();
    this->initAdvertising();
    this->_serverBLE->startAdvertising();
}

BLE::~BLE()
{
}

void BLE::tick() 
{            
    if (BLE::isDeviceConnected)
    {
        if (this->_trackSenseProperties->PropertiesCompletedRideToSend._isReady)
        {
            if (!BLE::isCompletedRideStatsReceived && !BLE::isCompletedRideStatsSending)
            {
                this->sendCompletedRideStats();
            }
            else if (BLE::isCompletedRideStatsReceived
                        && this->_trackSenseProperties->PropertiesCompletedRideToSend._isReady)
            {
                this->sendCompletedRideCurrentPoint();
            }
        }
    }
    else
    {
        Serial.println("Restart Advertising");
        this->_serverBLE->startAdvertising();
    }

    // if (!BLE::isDeviceConnected)
    // {
    //     Serial.println("Restart Advertising");
    //     this->_serverBLE->startAdvertising();
    // } 
    // else if (!BLE::isCompletedRideStatsReceived)
    // {
    //     String val = this->_CRIsReadyCaracteristic->getValue().c_str();
    // 
    //     if (val == String("false"))
    //     {
    //         this->_CRIsReadyCaracteristic->setValue("true");
    //     }
    //     else
    //     {
    //         this->_CRIsReadyCaracteristic->setValue("false");
    //     }
    //
    //     Serial.println(this->_CRIsReadyCaracteristic->getValue().c_str());
    //     Serial.println(this->_completedRideService->getServer()->getConnectedCount());
    //     this->_CRIsReadyCaracteristic->notify();
    //     Serial.println("Notified");
    // }
}

void BLE::initBLE()
{
    BLEDevice::init(BLE_DEVICE_NAME);

    this->_serverBLE = BLEDevice::createServer();
    this->_serverBLE->setCallbacks(new ServerBLECallbacks());

    Serial.println("BLE initialised");
}

void BLE::initAdvertising()
{
    this->_advertisingBLE = this->_serverBLE->getAdvertising();
    this->_advertisingBLE->setScanResponse(true);
    this->_advertisingBLE->setMinPreferred(0x06);
    this->_advertisingBLE->setMinPreferred(0x12);
    this->_advertisingBLE->setAppearance(0x0000);

    this->_advertisingBLE->addServiceUUID(BLE_COMPLETED_RIDE_SERVICE_UUID);
    this->_advertisingBLE->start();
    Serial.println("Advertising initialised");
}

void BLE::initCompletedRideService()
{
    this->_completedRideService = this->_serverBLE->createService(BLE_COMPLETED_RIDE_SERVICE_UUID);
    // this->_completedRideService->start();
    Serial.println("Completed Ride Service initialised");
};

void BLE::initCompletedRideCaracteristics()
{
    this->_CRStatsCaracteristic = this->_completedRideService->
        createCharacteristic(BLE_COMPLETED_RIDE_CARACTRISTIC_STATS, BLECharacteristic::PROPERTY_READ);
    this->_CRStatsCaracteristic->setValue("id;plannedRideId;maxSpeed;avgSpeed;distance;duration;dateBegin;dateEnd;nbPoints;nbFalls");

    this->_CRPointCaracteristic = this->_completedRideService->
        createCharacteristic(BLE_COMPLETED_RIDE_CHARACTERISTIC_POINT, BLECharacteristic::PROPERTY_READ);
    this->_CRPointCaracteristic->setValue("idPoint;lat;long;alt;tmp;speed;date;effectiveTime");
    this->_CRPointCaracteristic->setCallbacks(new CompletedRideReceivePointCallbacks());

    this->_CRPointNumberCaracteristic = this->_completedRideService->
        createCharacteristic(BLE_COMPLETED_RIDE_CHARACTERISTIC_POINT, BLECharacteristic::PROPERTY_READ);
    this->_CRPointNumberCaracteristic->setValue("0");
 
    this->_CRIsReadyCaracteristic = this->_completedRideService->
        createCharacteristic(BLE_COMPLETED_RIDE_CHARACTERISTIC_IS_STATS_READY, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
    this->_CRIsReadyCaracteristic->setValue(BLE_FALSE);
    this->_CRIsReadyCaracteristic->setCallbacks(new CompletedRideReceiveStatsCallbacks());

    Serial.println("Completed Ride Caracteristics initialised");
}

void BLE::initCompletedRideDescriptors()
{
    this->_CRStatsDescriptor = new BLEDescriptor(BLE_COMPLETED_RIDE_DESCRIPTOR_STATS_UUID);
    this->_CRStatsDescriptor->setValue(BLE_COMPLETED_RIDE_DESCRIPTOR_STATS_NAME);
    this->_CRStatsCaracteristic->addDescriptor(this->_CRStatsDescriptor);

    this->_CRPointDescriptor = new BLEDescriptor(BLE_COMPLETED_RIDE_DESCRIPTOR_POINT_UUID);
    this->_CRPointDescriptor->setValue(BLE_COMPLETED_RIDE_DESCRIPTOR_POINT_NAME);
    this->_CRPointCaracteristic->addDescriptor(this->_CRPointDescriptor);

    this->_CRPointNumberDescriptor = new BLEDescriptor(BLE_COMPLETED_RIDE_DESCRIPTOR_POINT_NUMBER_UUID);
    this->_CRPointNumberDescriptor->setValue(BLE_COMPLETED_RIDE_DESCRIPTOR_POINT_NUMBER_NAME);
    this->_CRPointNumberCaracteristic->addDescriptor(this->_CRPointNumberDescriptor);
    
    this->_CRIsReadyDescriptor = new BLEDescriptor(BLE_COMPLETED_RIDE_DESCRIPTOR_IS_READY_UUID);
    this->_CRIsReadyDescriptor->setValue(BLE_COMPLETED_RIDE_DESCRIPTOR_IS_READY_NAME);
    this->_CRIsReadyCaracteristic->addDescriptor(this->_CRIsReadyDescriptor);

    Serial.println("Completed Ride Descriptors initialised");
}

void BLE::sendCompletedRideStats()
{
    this->_CRStatsCaracteristic->setValue(this->_trackSenseProperties->PropertiesCompletedRideToSend._stats.c_str());
    this->_CRIsReadyCaracteristic->setValue(BLE_TRUE);
    this->_CRIsReadyCaracteristic->notify();
    BLE::isCompletedRideStatsSending = true;
    BLE::isCompletedRideStatsReceived = false;
    Serial.println("Completed Ride envoyed");
}

void BLE::sendCompletedRideCurrentPoint()
{
    if (BLE::isCompletedRidePointReceived)
    {
        this->_trackSenseProperties->PropertiesCompletedRideToSend._isPointReady = false;
        this->_trackSenseProperties->PropertiesCompletedRideToSend._isPointReceived = true;
        BLE::isCompletedRidePointReceived = false;
        Serial.println("Completed Ride Point received");
    }
    else if (!BLE::isCompletedRidePointSending)
    {
        this->_CRPointCaracteristic->setValue(this->_trackSenseProperties->PropertiesCompletedRideToSend._point.c_str());
        this->_CRPointNumberCaracteristic->setValue(String(this->_trackSenseProperties->PropertiesCompletedRideToSend._currentPoint).c_str());
        this->_CRPointNumberCaracteristic->notify();
        BLE::isCompletedRidePointSending = true;
        BLE::isCompletedRidePointReceived = false;

        this->_trackSenseProperties->PropertiesCompletedRideToSend._isPointReady = false;
        Serial.println("Completed Ride Point envoyed");
    }
}

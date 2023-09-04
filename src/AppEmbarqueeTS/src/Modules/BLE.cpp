#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLESecurity.h>
#include <BLE2902.h>

#include "Modules/BLE.h"
#include "Configurations.h"


/*----- Definition des membres statics -----*/
bool BLE::isDeviceConnected = false;
bool BLE::isCompletedRideReceived = false;



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

class CompletedRideReceiveCallbacks
    : public BLECharacteristicCallbacks
{
    void onWrite(BLECharacteristic *p_characteristic)
    {
        std::string receivedData = p_characteristic->getValue();
        std::string trueString = BLE_TRUE;

        if (receivedData.compare(trueString) == 0)
        {
            p_characteristic->setValue(BLE_FALSE);
            BLE::isCompletedRideReceived = true;
        }
    }
};




/*----- BLE -----*/

BLE::BLE(TrackSenseProperties* trackSenseProperties) 
    : _trackSenseProperties(trackSenseProperties),
    _serverBLE(nullptr),
    _completedRideService(nullptr),
    _CRIdCaracteristic(nullptr),
    _CRRouteIdCaracteristic(nullptr),
    _CRMaxSpeedCaracteristic(nullptr),
    _CRAVGSpeedCaracteristic(nullptr),
    _CRDistanceCaracteristic(nullptr),
    _CRDurationCaracteristic(nullptr),
    _CRDateBeginCaracteristic(nullptr),
    _CRDateEndCaracteristic(nullptr),
    _CRPointsCaracteristic(nullptr),
    _CRNbPointsCaracteristic(nullptr),
    _CRNbFallsCaracteristic(nullptr),
    _CRIsReadyCaracteristic(nullptr),
    _CRIsReceivedCaracteristic(nullptr)
{
    this->initBLE();
    this->initCompletedRideService();
    this->initCompletedRideCaracteristics();

}

BLE::~BLE()
{
}

void BLE::tick() 
{            
    if (this->isCompletedRideReceived)
    {
        this->_CRIsReadyCaracteristic->setValue(BLE_FALSE);
        this->isCompletedRideReceived = false;
        this->_trackSenseProperties->PropertiesCompletedRideToSend._isReady = false;
        this->_trackSenseProperties->PropertiesCompletedRideToSend._isReceived = true;
    }
    else if (this->_trackSenseProperties->PropertiesCompletedRideToSend._isReady && this->isDeviceConnected)
    {
        this->sendCompletedRide();
        this->_trackSenseProperties->PropertiesCompletedRideToSend._isReady = false;
    }
}

void BLE::initBLE()
{
    BLE::isDeviceConnected = false;
    BLE::isCompletedRideReceived = false;
    BLEDevice::init(BLE_DEVICE_NAME);

    this->_serverBLE = BLEDevice::createServer();
    this->_serverBLE->setCallbacks(new ServerBLECallbacks());
}

void BLE::initCompletedRideService()
{
    this->_completedRideService = this->_serverBLE->createService(BLE_COMPLETED_RIDE_SERVICE_UUID);
};

void BLE::initCompletedRideCaracteristics()
{
    this->_CRIdCaracteristic = this->_completedRideService->createCharacteristic(
        BLE_COMPLETED_RIDE_CHARACTERISTIC_ID,
        BLECharacteristic::PROPERTY_READ
    );
    this->_CRIdCaracteristic->setValue("00000000-0000-0000-0000-000000000000");

    this->_CRRouteIdCaracteristic = this->_completedRideService->createCharacteristic(
        BLE_COMPLETED_RIDE_CHARACTERISTIC_ROUTE_ID,
        BLECharacteristic::PROPERTY_READ
    );
    this->_CRRouteIdCaracteristic->setValue("00000000-0000-0000-0000-000000000000");

    this->_CRMaxSpeedCaracteristic = this->_completedRideService->createCharacteristic(
        BLE_COMPLETED_RIDE_CHARACTERISTIC_MAX_SPEED,
        BLECharacteristic::PROPERTY_READ
    );
    this->_CRMaxSpeedCaracteristic->setValue("0.0");

    this->_CRAVGSpeedCaracteristic = this->_completedRideService->createCharacteristic(
        BLE_COMPLETED_RIDE_CHARACTERISTIC_AVG_SPEED,
        BLECharacteristic::PROPERTY_READ
    );
    this->_CRAVGSpeedCaracteristic->setValue("0.0");
    
    this->_CRDateBeginCaracteristic = this->_completedRideService->createCharacteristic(
        BLE_COMPLETED_RIDE_CHARACTERISTIC_DATE_BEGIN,
        BLECharacteristic::PROPERTY_READ
    );
    this->_CRDateBeginCaracteristic->setValue("0000/00/00-00:00:00");

    this->_CRDateEndCaracteristic = this->_completedRideService->createCharacteristic(
        BLE_COMPLETED_RIDE_CHARACTERISTIC_DATE_END,
        BLECharacteristic::PROPERTY_READ
    );
    this->_CRDateEndCaracteristic->setValue("0000/00/00-00:00:00");

    this->_CRDurationCaracteristic = this->_completedRideService->createCharacteristic(
        BLE_COMPLETED_RIDE_CHARACTERISTIC_DURATION,
        BLECharacteristic::PROPERTY_READ
    );
    this->_CRDurationCaracteristic->setValue("00:00:00");

    this->_CRDistanceCaracteristic = this->_completedRideService->createCharacteristic(
        BLE_COMPLETED_RIDE_CHARACTERISTIC_DISTANCE,
        BLECharacteristic::PROPERTY_READ
    );
    this->_CRDistanceCaracteristic->setValue("0.0");

    this->_CRPointsCaracteristic = this->_completedRideService->createCharacteristic(
        BLE_COMPLETED_RIDE_CHARACTERISTIC_POINTS,
        BLECharacteristic::PROPERTY_READ
    );
    this->_CRPointsCaracteristic->setValue("id;lat;long;alt;tmp;speed;date;effectiveTime");

    this->_CRNbPointsCaracteristic = this->_completedRideService->createCharacteristic(
        BLE_COMPLETED_RIDE_CHARACTERISTIC_POINTS,
        BLECharacteristic::PROPERTY_READ
    );
    this->_CRNbPointsCaracteristic->setValue("0");

    this->_CRNbFallsCaracteristic = this->_completedRideService->createCharacteristic(
        BLE_COMPLETED_RIDE_CHARACTERISTIC_POINTS,
        BLECharacteristic::PROPERTY_READ
    );
    this->_CRNbFallsCaracteristic->setValue("0");

    this->_CRIsReadyCaracteristic = this->_completedRideService->createCharacteristic(
        BLE_COMPLETED_RIDE_CHARACTERISTIC_POINTS,
        BLECharacteristic::PROPERTY_NOTIFY | BLECharacteristic::PROPERTY_READ
    );
    this->_CRIsReadyCaracteristic->setValue(BLE_FALSE);

    this->_CRIsReceivedCaracteristic = this->_completedRideService->createCharacteristic(
        BLE_COMPLETED_RIDE_CHARACTERISTIC_POINTS,
        BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE
    );
    this->_CRIsReceivedCaracteristic->setValue(BLE_FALSE);
}

void BLE::sendCompletedRide()
{
    this->_CRIdCaracteristic->setValue(this->_trackSenseProperties->PropertiesCompletedRideToSend._completedRideId.c_str());
    this->_CRRouteIdCaracteristic->setValue(this->_trackSenseProperties->PropertiesCompletedRideToSend._routeId.c_str());
    this->_CRMaxSpeedCaracteristic->setValue(String(this->_trackSenseProperties->PropertiesCompletedRideToSend._maxSpeed).c_str());
    this->_CRAVGSpeedCaracteristic->setValue(String(this->_trackSenseProperties->PropertiesCompletedRideToSend._avgSpeed).c_str());
    this->_CRDistanceCaracteristic->setValue(String(this->_trackSenseProperties->PropertiesCompletedRideToSend._distance).c_str());
    this->_CRDurationCaracteristic->setValue(String(this->_trackSenseProperties->PropertiesCompletedRideToSend._duration).c_str());
    this->_CRDateBeginCaracteristic->setValue(this->_trackSenseProperties->PropertiesCompletedRideToSend._dateBegin.c_str());
    this->_CRDateEndCaracteristic->setValue(this->_trackSenseProperties->PropertiesCompletedRideToSend._dateEnd.c_str());
    this->_CRPointsCaracteristic->setValue(this->_trackSenseProperties->PropertiesCompletedRideToSend._points.c_str());
    this->_CRNbPointsCaracteristic->setValue(String(this->_trackSenseProperties->PropertiesCompletedRideToSend._nbPoints).c_str());
    this->_CRNbFallsCaracteristic->setValue(String(this->_trackSenseProperties->PropertiesCompletedRideToSend._nbFalls).c_str());
    this->_CRIsReadyCaracteristic->setValue(BLE_TRUE);
}

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLESecurity.h>

/*----- BLE -----*/
#define BLE_DEVICE_NAME "TrackSense_TEST_ENVOI"
#define BLE_PIN_CODE "123456"
#define BLE_TRUE "true"
#define BLE_FALSE "false"
#define BLE_OK "ok"

#define BLE_DELAY_SEND_STATS_MS 1000
#define BLE_DELAY_SEND_POINT_MS 200

// Service et caracterisiques pour CompletedRide
#define BLE_COMPLETED_RIDE_SERVICE_UUID "62ffab64-3646-4fb9-88d8-541deb961192"

#define BLE_COMPLETED_RIDE_CARACTRISTIC_STATS "51656aa8-b795-427f-a96c-c4b6c57430dd"
#define BLE_COMPLETED_RIDE_DESCRIPTOR_STATS_NAME "Completed Ride Stats"
#define BLE_COMPLETED_RIDE_DESCRIPTOR_STATS_UUID "5a2b4a0f-8ddd-4c69-a825-dbab5822ba0e"

#define BLE_COMPLETED_RIDE_NOTIFICATION_CARACTRISTIC "61656aa8-b795-427f-a96c-c4b6c57430dd"
#define BLE_COMPLETED_RIDE_DESCRIPTOR_NOTIF_NAME "Notification"
#define BLE_COMPLETED_RIDE_DESCRIPTOR_NOTIFICATION_UUID "6a2b4a0f-8ddd-4c69-a825-dbab5822ba0e"


// Donnees pour CompletedRide
#define RIDE_NB_POINTS 1000
#define RIDE_STATS "e3ba4698-d64b-447e-81f5-0bf0e09700eb;00000000-0000-0000-0000-000000000000;0.00;0.00;2023-09-13T12:09:55;2023-09-13T12:41:38;33.00;0.00;1000;0;"
#define RIDE_POINT String(";46.8423843384;-71.3978271484;95.70;0.00;49.26;2023-09-13T12:09:55;0")
#define RIDE_POINT_1 String("1;46.8423843384;-71.3978271484;95.70;0.00;49.26;2023-09-13T12:09:55;0")
#define RIDE_POINT_2 String("2;46.8425025940;-71.3976898193;99.40;0.00;47.78;2023-09-13T12:09:55;0")
#define RIDE_POINT_3 String("3;46.8427085876;-71.3974456787;101.90;0.00;46.11;2023-09-13T12:09:55;0")
#define RIDE_POINT_4 String("4;46.8428497314;-71.3972473145;102.50;0.00;28.89;2023-09-13T12:09:55;0")
#define RIDE_POINT_5 String("5;46.8428993225;-71.3971862793;101.90;0.00;19.08;2023-09-13T12:09:55;0")
String currentPoint;
int currentPointNumber = 1;
bool isPointReady = false;
bool isPointReceived = false;
bool isReady = false;
bool isReceived = false;

///////////////////////////////////////////////////////////////////////////////////////////

class BLE
{
private:
    BLEServer* _serverBLE;
    BLEAdvertising* _advertisingBLE;

    BLEService* _completedRideService;

    BLECharacteristic* _CRStatsCaracteristic;
    BLECharacteristic* _CRNotificationCaracteristic;
    BLECharacteristic* _CRPointCaracteristic;
    BLECharacteristic* _CRPointNumberCaracteristic;
    BLECharacteristic* _CRIsReadyCaracteristic;

    BLEDescriptor* _CRStatsDescriptor;
    BLEDescriptor* _CRNotificationDescriptor;
    BLEDescriptor* _CRPointDescriptor;
    BLEDescriptor* _CRPointNumberDescriptor;
    BLEDescriptor* _CRIsReadyDescriptor;

    unsigned long _lastTimeStatsSent;
    unsigned long _lastTimePointSent;

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

    BLE();
    ~BLE();

    void tick();
};


/*----- Definition des membres statics -----*/
bool BLE::isDeviceConnected = false;
bool BLE::isCompletedRideStatsSending = false;
bool BLE::isCompletedRideStatsReceived = false;
bool BLE::isCompletedRidePointSending = false;
bool BLE::isCompletedRidePointReceived = false;
bool BLE::isAdvertiesingStarted = false;
int BLE::currentPointNumber = 0;

/*----- CallBacks -----*/
class ServerBLECallbacks
    : public BLEServerCallbacks
{
    void onConnect(BLEServer *p_server)
    {
        BLE::isDeviceConnected = true;
        BLE::isAdvertiesingStarted = false;
        Serial.println("Connected");
    }

    void onDisconnect(BLEServer *p_server)
    {
        BLE::isDeviceConnected = false;
        Serial.println("Disconnected");
    }
};

class CompletedRideReceiveStatsCallbacks
    : public BLECharacteristicCallbacks
{
    void onWrite(BLECharacteristic *p_characteristic)
    {
        std::string receivedData = p_characteristic->getValue();
        std::string acceptation = String(BLE::currentPointNumber).c_str();

        Serial.println(String("Callback Reception data: ") + String(receivedData.c_str()));
        Serial.println(String("Callback Acceptation data: ") + String(acceptation.c_str()));

        if (receivedData.compare(acceptation) == 0)
        {
            if (BLE::isCompletedRideStatsSending)
            {
                // Serial.println("Callback reception stats");
                BLE::isCompletedRideStatsReceived = true;
                BLE::isCompletedRideStatsSending = false;
            }
            else if (BLE::isCompletedRidePointSending)
            {
                // Serial.println("Callback reception point");
                BLE::isCompletedRidePointReceived = true;
                BLE::isCompletedRidePointSending = false;
            }
            // p_characteristic->setValue("sending");
        }
    }
};

// class CompletedRideReceivePointCallbacks
//     : public BLECharacteristicCallbacks
// {
//     void onWrite(BLECharacteristic *p_characteristic)
//     {
//         std::string receivedData = p_characteristic->getValue();
//         std::string okString = BLE_OK;
//
//         Serial.println("Confirmation reception point");
//         Serial.println(receivedData.c_str());
//
//         if (receivedData.compare(okString) == 0)
//         {
//             p_characteristic->setValue("");
//             BLE::isCompletedRidePointReceived = true;
//             BLE::isCompletedRidePointSending = false;
//         }
//     }
// };

/*----- BLE -----*/
BLE::BLE()
    :
    _serverBLE(nullptr),
    _advertisingBLE(nullptr),
    _completedRideService(nullptr),
    _CRStatsCaracteristic(nullptr),
    _CRNotificationCaracteristic(nullptr),
    _CRPointCaracteristic(nullptr),
    _CRPointNumberCaracteristic(nullptr),
    _CRIsReadyCaracteristic(nullptr),
    _CRStatsDescriptor(nullptr),
    _CRPointDescriptor(nullptr),
    _CRPointNumberDescriptor(nullptr),
    _CRIsReadyDescriptor(nullptr),
    _lastTimeStatsSent(0),
    _lastTimePointSent(0)
{
    this->initBLE();
    this->initCompletedRideService();
    this->initCompletedRideCaracteristics();
    this->initCompletedRideDescriptors();
    this->_completedRideService->start();
    this->initAdvertising();
    Serial.println("Start Advertising");
    this->_serverBLE->startAdvertising();
    BLE::isAdvertiesingStarted = true;
}

BLE::~BLE()
{
}

void BLE::tick()
{
    if (BLE::isDeviceConnected)
    {
        if (isReady)
        {
            if (!BLE::isCompletedRideStatsReceived || BLE::isCompletedRideStatsSending) // Renvoie les stats tant qu'on a pas la confirmation de reception
            {
                // Serial.println("Envoie des stats");
                this->sendCompletedRideStats();
            }
            else if (BLE::isCompletedRidePointReceived)
            {
                // Serial.println("Confirmation reception point");
                this->confirmPointReceived();
            }
            else if (BLE::isCompletedRideStatsReceived
                        && (isPointReady || BLE::isCompletedRidePointSending))
            {
                // Serial.println("Envoie du point");
                this->sendCompletedRideCurrentPoint();
            }
            // else if (BLE::isCompletedRideStatsReceived
            //             && RIDE_NB_POINTS
            //            >= currentPointNumber)
            // {
            //     Serial.println("Fin des points");
            //     isReady = false;
            //     isReceived = true;
            // }
        }
    }
    else if (!BLE::isAdvertiesingStarted)
    {
        Serial.println("Restart Advertising");
        isReady = true;
        // currentPoint = RIDE_POINT_1;
        currentPointNumber = 1;
        currentPoint = String(currentPointNumber) + String(RIDE_POINT);
        isPointReady = true;
        BLE::isCompletedRidePointReceived = false;
        BLE::isCompletedRideStatsReceived = false;
        BLE::isCompletedRidePointSending = false;
        BLE::currentPointNumber = 0;

        delay(500);
        BLE::isAdvertiesingStarted = true;
        this->_serverBLE->startAdvertising();
    }
}

void BLE::initBLE()
{
    BLEDevice::init(BLE_DEVICE_NAME);

    this->_serverBLE = BLEDevice::createServer();
    this->_serverBLE->setCallbacks(new ServerBLECallbacks());

    Serial.println("BLE initialized");
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
    Serial.println("Advertising initialized");
}

void BLE::initCompletedRideService()
{
    this->_completedRideService = this->_serverBLE->createService(BLE_COMPLETED_RIDE_SERVICE_UUID);
    // this->_completedRideService->start();
    Serial.println("Completed Ride Service initialized");
};

void BLE::initCompletedRideCaracteristics()
{
    this->_CRStatsCaracteristic = this->_completedRideService->
        createCharacteristic(BLE_COMPLETED_RIDE_CARACTRISTIC_STATS, BLECharacteristic::PROPERTY_READ);
    this->_CRStatsCaracteristic->setValue("id;plannedRideId;maxSpeed;avgSpeed;distance;duration;dateBegin;dateEnd;nbPoints;nbFalls");

    this->_CRNotificationCaracteristic = this->_completedRideService->
        createCharacteristic(BLE_COMPLETED_RIDE_NOTIFICATION_CARACTRISTIC, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_NOTIFY);
    this->_CRNotificationCaracteristic->setValue("sending");
    this->_CRNotificationCaracteristic->setCallbacks(new CompletedRideReceiveStatsCallbacks());

    // this->_CRPointCaracteristic = this->_completedRideService->
    //     createCharacteristic(BLE_COMPLETED_RIDE_CHARACTERISTIC_POINT, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);
    // this->_CRPointCaracteristic->setValue("idPoint;lat;long;alt;tmp;speed;date;effectiveTime");
    // this->_CRPointCaracteristic->setCallbacks(new CompletedRideReceivePointCallbacks());
    //
    // this->_CRPointNumberCaracteristic = this->_completedRideService->
    //     createCharacteristic(BLE_COMPLETED_RIDE_CHARACTERISTIC_POINT_NUMBER, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
    // this->_CRPointNumberCaracteristic->setValue("0");
    //
    // this->_CRIsReadyCaracteristic = this->_completedRideService->
    //     createCharacteristic(BLE_COMPLETED_RIDE_CHARACTERISTIC_IS_STATS_READY, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_NOTIFY);
    // this->_CRIsReadyCaracteristic->setValue(BLE_FALSE);
    // this->_CRIsReadyCaracteristic->setCallbacks(new CompletedRideReceiveStatsCallbacks());

    Serial.println("Completed Ride Caracteristics initialized");
}

void BLE::initCompletedRideDescriptors()
{
    this->_CRStatsDescriptor = new BLEDescriptor(BLE_COMPLETED_RIDE_DESCRIPTOR_STATS_UUID);
    this->_CRStatsDescriptor->setValue(BLE_COMPLETED_RIDE_DESCRIPTOR_STATS_NAME);
    this->_CRStatsCaracteristic->addDescriptor(this->_CRStatsDescriptor);

    this->_CRNotificationDescriptor = new BLEDescriptor(BLE_COMPLETED_RIDE_DESCRIPTOR_NOTIFICATION_UUID);
    this->_CRNotificationDescriptor->setValue(BLE_COMPLETED_RIDE_DESCRIPTOR_NOTIF_NAME);
    this->_CRNotificationCaracteristic->addDescriptor(this->_CRNotificationDescriptor);

    Serial.println("Completed Ride Descriptors initialized");
}

void BLE::sendCompletedRideStats()
{
    unsigned long currentTime = millis();

    if ( (currentTime - this->_lastTimeStatsSent) >= BLE_DELAY_SEND_STATS_MS)
    {
        this->_lastTimeStatsSent = currentTime;
        this->_CRStatsCaracteristic->setValue(RIDE_STATS);
        // this->_CRIsReadyCaracteristic->setValue(BLE_TRUE);
        this->_CRNotificationCaracteristic->notify();
        BLE::isCompletedRideStatsSending = true;
        BLE::isCompletedRideStatsReceived = false;
        Serial.println("Completed Ride stats sent");
    }
}

void BLE::sendCompletedRideCurrentPoint()
{
    unsigned long currentTime = millis();

    if ( (currentTime - this->_lastTimePointSent) > BLE_DELAY_SEND_POINT_MS) // Envoie le point tant qu'on a pas la confirmation de reception
    {
        this->_lastTimePointSent = currentTime;
        // this->_CRPointCaracteristic->setValue(currentPoint.c_str());
        this->_CRStatsCaracteristic->setValue(currentPoint.c_str());
        // Serial.println("notification charac value : " + String(this->_CRNotificationCaracteristic->getValue().c_str()));
        BLE::currentPointNumber = currentPointNumber;
        this->_CRNotificationCaracteristic->setValue("sending");
        this->_CRNotificationCaracteristic->notify();
        BLE::isCompletedRidePointSending = true;
        // BLE::isCompletedRidePointReceived = false;

        isPointReady = false;
        Serial.println(String("Completed Ride Point ") + String(currentPointNumber) + String(" sent"));
    }
}

void BLE::confirmPointReceived()
{
    BLE::isCompletedRidePointReceived = false;
    
    if (RIDE_NB_POINTS > currentPointNumber) 
    {
        isPointReady = false;
        isPointReceived = true;
        Serial.println(String("Completed Ride Point ") + String(currentPointNumber) +  String(" received"));
    }
    else
    {
        Serial.println("End of points");
        isReady = false;
        isReceived = true;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////

BLE* serveurBLE;

void setup() {
  Serial.begin(115200);
  Serial.println("Bienvenue dans le test d'envoi Bluetooth !");

  serveurBLE = new BLE();

  isReady = true;
  currentPoint = RIDE_POINT_1;
  currentPointNumber = 1;
  isPointReady = true;
}

void loop() {
    if (isPointReceived)
    {
        isPointReceived = false;
        currentPointNumber++;
        BLE::currentPointNumber = currentPointNumber;
        currentPoint = String(currentPointNumber) + String(RIDE_POINT);
        isPointReady = true;
        // switch (cur)
        // {
        //     case 1:
        //         currentPoint = RIDE_POINT_1;
        //         isPointReady = true;
        //         break;
        //     case 2:
        //         currentPoint = RIDE_POINT_2;
        //         isPointReady = true;
        //         break;
        //     case 3:
        //         currentPoint = RIDE_POINT_3;
        //         isPointReady = true;
        //         break;
        //     case 4:
        //         currentPoint = RIDE_POINT_4;
        //         isPointReady = true;
        //         break;
        //     case 5:
        //         currentPoint = RIDE_POINT_5;
        //         isPointReady = true;
        //         break;
        //     default:
        //         break;
        // }
        Serial.println(String("Current point: ") + String(currentPoint));
        Serial.println("Completed Ride Point Ready to send");
    }
    serveurBLE->tick();
}

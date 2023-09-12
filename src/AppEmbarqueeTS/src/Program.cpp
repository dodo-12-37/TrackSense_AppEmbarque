#include "Program.h"



Program::Program() : 
    _TSProperties(nullptr), 
    // _lte(nullptr), 
    _gsm(nullptr), 
    _sdCard(nullptr), 
    _gyroscope(nullptr), 
    _compass(nullptr), 
    _accelerometer(nullptr), 
    _ble(nullptr), 
    _screen(nullptr), 
    _buzzer(nullptr)
{
    this->_TSProperties = new TSProperties();
    this->initProperties();

    this->_screen = new ScreenGC9A01(this->_TSProperties);
    this->_screen->tick();

    this->_controlerButtons = new ControlerButtons(this->_TSProperties);
    this->_ble = new BLE(this->_TSProperties);
    this->_sdCard = new SDCard(this->_TSProperties);
    this->_gsm = new GSMTiny(this->_TSProperties);
    // this->_lte = new LTE(this->_TSProperties);
    this->_gyroscope = new GyroscopeMPU6050(this->_TSProperties);
    this->_compass = new CompassHMC5883L(this->_TSProperties);
    this->_accelerometer = new AccelerometerMPU6050(this->_TSProperties);
    this->_buzzer = new Buzzer(this->_TSProperties);

    this->_gsm->init();

    this->_TSProperties->PropertiesTS._isInitializingTS = false;
    this->_TSProperties->PropertiesScreen._isNewActivePage = true;
    this->_TSProperties->PropertiesScreen._activeScreen = 1;
}

Program::~Program()
{
}

void Program::execute()
{
    this->_controlerButtons->tick();
    this->_buzzer->tick();
    this->_screen->tick();
    this->_ble->tick();
    this->_gsm->tick();
    this->_sdCard->tick();
    // this->_lte->tick();
    this->_gyroscope->tick();
    this->_compass->tick();
    this->_accelerometer->tick();
}

void Program::initProperties()
{
    // TS
    this->_TSProperties->PropertiesTS._isInitializingTS = true;

    // Battery
    this->_TSProperties->PropertiesBattery._batteryLevel = 0;

    // Buttons
    this->_TSProperties->PropertiesButtons._button1State = 0;
    this->_TSProperties->PropertiesButtons._button2State = 0;

    // Buzzer
    this->_TSProperties->PropertiesBuzzer._isBuzzerOn = false;

    // Screen
    this->_TSProperties->PropertiesScreen._activeScreen = 0;
    this->_TSProperties->PropertiesScreen._isDarkMode = true;
    this->_TSProperties->PropertiesScreen._screenRotation = 0;
    this->_TSProperties->PropertiesScreen._isNewActivePage = true;

    // Ride
    this->_TSProperties->PropertiesCurrentRide._isRideStarted = false;
    this->_TSProperties->PropertiesCurrentRide._isRidePaused = false;
    this->_TSProperties->PropertiesCurrentRide._isRideFinished = false;

    // BLE
    this->_TSProperties->PropertiesCompletedRideToSend._completedRideId = "00000000-0000-0000-0000-000000000000";
    this->_TSProperties->PropertiesCompletedRideToSend._stats = "";
    this->_TSProperties->PropertiesCompletedRideToSend._point = "";
    this->_TSProperties->PropertiesCompletedRideToSend._currentPoint = 0;
    this->_TSProperties->PropertiesCompletedRideToSend._nbPoints = 0;
    this->_TSProperties->PropertiesCompletedRideToSend._isPointReady = false;
    this->_TSProperties->PropertiesCompletedRideToSend._isPointReceived = false;
    this->_TSProperties->PropertiesCompletedRideToSend._isReady = false;
    this->_TSProperties->PropertiesCompletedRideToSend._isReceived = false;

    // GPS
    this->_TSProperties->PropertiesGPS.resetGPSValues();

    // Current Ride
    this->_TSProperties->PropertiesCurrentRide.resetCurrentRide();

}   

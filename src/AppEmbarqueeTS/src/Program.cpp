#include "Program.h"

Program::Program() : _TSProperties(nullptr),
                     // _lte(nullptr),
                     _gsm(nullptr),
                     _sdCard(nullptr),
                     _gyroscope(nullptr),
                     _compass(nullptr),
                     _accelerometer(nullptr),
                     _ble(nullptr),
                     _buzzer(nullptr),
                     _controlerButtons(nullptr),
                     _controlerScreen(nullptr)
{
    this->_TSProperties = new TSProperties();
    this->initProperties();

    this->_controlerScreen = new ControlerScreen(this->_TSProperties);
    this->_controlerScreen->tick();

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

    this->_TSProperties->PropertiesTS.IsInitializingTS = false;
    this->_TSProperties->PropertiesScreen.IsNewActivePage = true;
    this->_TSProperties->PropertiesScreen.ActiveScreen = 1;
}

Program::~Program()
{
}

void Program::execute()
{
    this->_controlerButtons->tick();
    this->_buzzer->tick();
    this->_controlerScreen->tick();
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
    this->_TSProperties->PropertiesTS.IsInitializingTS = true;

    // Battery
    this->_TSProperties->PropertiesBattery.BatteryLevel = 0;

    // Buttons
    this->_TSProperties->PropertiesButtons.Button1State = 0;
    this->_TSProperties->PropertiesButtons.Button2State = 0;

    // Buzzer
    this->_TSProperties->PropertiesBuzzer.IsBuzzerOn = false;

    // Screen
    this->_TSProperties->PropertiesScreen.ActiveScreen = INIT_TS_PAGE_ID;
    this->_TSProperties->PropertiesScreen.IsDarkMode = true;
    this->_TSProperties->PropertiesScreen.ScreenRotation = 0;
    this->_TSProperties->PropertiesScreen.IsNewActivePage = true;

    // Ride
    this->_TSProperties->PropertiesCurrentRide.IsRideStarted = false;
    this->_TSProperties->PropertiesCurrentRide.IsRidePaused = false;
    this->_TSProperties->PropertiesCurrentRide.IsRideFinished = false;

    // BLE
    this->_TSProperties->PropertiesCompletedRideToSend.CompletedRideId = "00000000-0000-0000-0000-000000000000";
    this->_TSProperties->PropertiesCompletedRideToSend.Stats = "";
    this->_TSProperties->PropertiesCompletedRideToSend.Point = "";
    this->_TSProperties->PropertiesCompletedRideToSend.CurrentPoint = 0;
    this->_TSProperties->PropertiesCompletedRideToSend.NbPoints = 0;
    this->_TSProperties->PropertiesCompletedRideToSend.IsPointReady = false;
    this->_TSProperties->PropertiesCompletedRideToSend.IsPointReceived = false;
    this->_TSProperties->PropertiesCompletedRideToSend.IsReady = false;
    this->_TSProperties->PropertiesCompletedRideToSend.IsReceived = false;

    // GPS
    this->_TSProperties->PropertiesGPS.resetGPSValues();

    // Current Ride
    this->_TSProperties->PropertiesCurrentRide.resetCurrentRide();
}

#include "Program.h"



Program::Program() : 
    _trackSenseProperties(nullptr), 
    // _lte(nullptr), 
    // _gps(nullptr), 
    _gsm(nullptr), 
    _sdCard(nullptr), 
    _gyroscope(nullptr), 
    _compass(nullptr), 
    _accelerometer(nullptr), 
    _ble(nullptr), 
    _screen(nullptr), 
    _buzzer(nullptr)
{
    this->_trackSenseProperties = new TrackSenseProperties();
    this->initProperties();


    this->_screen = new ScreenGC9A01(this->_trackSenseProperties);
    this->_controlerButtons = new ControlerButtons(this->_trackSenseProperties);
    this->_ble = new BLE(this->_trackSenseProperties);
    this->_sdCard = new SDCard(this->_trackSenseProperties);
    this->_gsm = new GSMTiny(this->_trackSenseProperties);
    // this->_gps = new GPSTinyPlus(this->_trackSenseProperties);
    // this->_lte = new LTE(this->_trackSenseProperties);
    this->_gyroscope = new GyroscopeMPU6050(this->_trackSenseProperties);
    this->_compass = new CompassHMC5883L(this->_trackSenseProperties);
    this->_accelerometer = new AccelerometerMPU6050(this->_trackSenseProperties);
    this->_buzzer = new Buzzer(this->_trackSenseProperties);

    this->_screen->tick();
    this->_gsm->init();

}

Program::~Program()
{
}

void Program::execute()
{
    this->_controlerButtons->tick();
    this->_screen->tick();
    this->_ble->tick();
    this->_gsm->tick();
    this->_sdCard->tick();
    // this->_gps->tick();
    // this->_lte->tick();
    this->_gyroscope->tick();
    this->_compass->tick();
    this->_accelerometer->tick();
    this->_buzzer->tick();
}

void Program::initProperties()
{
    // Buttons
    this->_trackSenseProperties->PropertiesButtons._button1State = 0;
    this->_trackSenseProperties->PropertiesButtons._button2State = 0;

    // Buzzer
    this->_trackSenseProperties->PropertiesBuzzer._isBuzzerOn = false;

    // Screen
    this->_trackSenseProperties->PropertiesScreen._activeScreen = 0;
    this->_trackSenseProperties->PropertiesScreen._isDarkMode = true;
    this->_trackSenseProperties->PropertiesScreen._screenRotation = 0;
    this->_trackSenseProperties->PropertiesScreen._isNewActivePage = true;

    // Ride
    this->_trackSenseProperties->PropertiesCurrentRide._isRideStarted = false;
    this->_trackSenseProperties->PropertiesCurrentRide._isRidePaused = false;
    this->_trackSenseProperties->PropertiesCurrentRide._isRideFinished = false;
}
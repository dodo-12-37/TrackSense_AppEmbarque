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
    this->_screen->tick();

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

    this->_gsm->init();

    this->_trackSenseProperties->PropertiesTS._isInitializingTS = false;
    this->_trackSenseProperties->PropertiesScreen._isNewActivePage = true;
    this->_trackSenseProperties->PropertiesScreen._activeScreen = 1;
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
    // TS
    this->_trackSenseProperties->PropertiesTS._isInitializingTS = true;

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

    // BLE
    this->_trackSenseProperties->PropertiesCompletedRideToSend._stats = "";
    this->_trackSenseProperties->PropertiesCompletedRideToSend._point = "";
    this->_trackSenseProperties->PropertiesCompletedRideToSend._currentPoint = 0;
    this->_trackSenseProperties->PropertiesCompletedRideToSend._nbPoints = 0;
    this->_trackSenseProperties->PropertiesCompletedRideToSend._isPointReady = false;
    this->_trackSenseProperties->PropertiesCompletedRideToSend._isPointReceived = false;
    this->_trackSenseProperties->PropertiesCompletedRideToSend._isReady = false;
    this->_trackSenseProperties->PropertiesCompletedRideToSend._isReceived = false;

    // Current Ride
    this->_trackSenseProperties->PropertiesCurrentRide._isRideStarted = false;
    this->_trackSenseProperties->PropertiesCurrentRide._isRidePaused = false;
    this->_trackSenseProperties->PropertiesCurrentRide._isRideFinished = false;
    this->_trackSenseProperties->PropertiesCurrentRide._completedRideId = "00000000-0000-0000-0000-000000000000";
    this->_trackSenseProperties->PropertiesCurrentRide._routeId = "00000000-0000-0000-0000-000000000000";
    this->_trackSenseProperties->PropertiesCurrentRide._maxSpeed = 0;
    this->_trackSenseProperties->PropertiesCurrentRide._avgSpeed = 0;
    this->_trackSenseProperties->PropertiesCurrentRide._distance = 0;
    this->_trackSenseProperties->PropertiesCurrentRide._duration = 0;
    this->_trackSenseProperties->PropertiesCurrentRide._dateBegin = "0000-00-00T00:00:00";
    this->_trackSenseProperties->PropertiesCurrentRide._dateEnd = "0000-00-00T00:00:00";
    this->_trackSenseProperties->PropertiesCurrentRide._currentPoint = "";
    this->_trackSenseProperties->PropertiesCurrentRide._nbPoints = 0;
    this->_trackSenseProperties->PropertiesCurrentRide._nbFalls = 0;
    this->_trackSenseProperties->PropertiesCurrentRide._isRideReadyToSave = false;
    this->_trackSenseProperties->PropertiesCurrentRide._isPointReadyToSave = false;

    this->_trackSenseProperties->PropertiesCurrentRide._latitude = 0;
    this->_trackSenseProperties->PropertiesCurrentRide._longitude = 0;
    this->_trackSenseProperties->PropertiesCurrentRide._altitude = 0;
    this->_trackSenseProperties->PropertiesCurrentRide._speed = 0;
    this->_trackSenseProperties->PropertiesCurrentRide._visibleSatellites = 0;
    this->_trackSenseProperties->PropertiesCurrentRide._usedSatellites = 0;
    this->_trackSenseProperties->PropertiesCurrentRide._accuracy = 0;
    this->_trackSenseProperties->PropertiesCurrentRide._year = 0;
    this->_trackSenseProperties->PropertiesCurrentRide._month = 0;
    this->_trackSenseProperties->PropertiesCurrentRide._day = 0;
    this->_trackSenseProperties->PropertiesCurrentRide._hour = 0;
    this->_trackSenseProperties->PropertiesCurrentRide._minute = 0;
    this->_trackSenseProperties->PropertiesCurrentRide._seconde = 0;
    this->_trackSenseProperties->PropertiesCurrentRide._TEST_counterGoodValue = 0;
    this->_trackSenseProperties->PropertiesCurrentRide._TEST_counterTotal = 0;

}   

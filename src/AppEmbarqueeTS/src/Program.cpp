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
    this->_controlerScreen = new ControlerScreen(this->_TSProperties);
    this->_controlerButtons = new ControlerButtons(this->_TSProperties);
    this->_ble = new BLE(this->_TSProperties);
    this->_sdCard = new SDCard(this->_TSProperties);
    this->_gsm = new GSMTiny(this->_TSProperties);
    // this->_lte = new LTE(this->_TSProperties);
    this->_gyroscope = new GyroscopeMPU6050(this->_TSProperties);
    this->_compass = new CompassHMC5883L(this->_TSProperties);
    this->_accelerometer = new AccelerometerMPU6050(this->_TSProperties);
    this->_buzzer = new Buzzer(this->_TSProperties);

    this->_TSProperties->PropertiesTS.IsInitializingTS = false;
    // this->_TSProperties->PropertiesScreen.IsNewActivePage = true;
    this->_TSProperties->PropertiesScreen.ActiveScreen = HOME_PAGE_ID;

    this->_controlerButtons->resetLastDateChangementStateButtons();
}

Program::~Program()
{
    ;
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

    delay(1000);
}

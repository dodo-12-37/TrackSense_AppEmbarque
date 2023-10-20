#include "Program.h"

Program::Program() : _TSProperties(nullptr),
                     _gsm(nullptr),
                     _sdCard(nullptr),
                     _gyroscope(nullptr),
                     _compass(nullptr),
                     _accelerometer(nullptr),
                     _ble(nullptr),
                     _buzzer(nullptr),
                     _battery(nullptr),
                     _controlerButtons(nullptr),
                     _controlerScreen(nullptr)
{
    this->_TSProperties = new TSProperties();
    this->_controlerScreen = new ControlerScreen(this->_TSProperties);
    this->_controlerButtons = new ControlerButtons(this->_TSProperties);
    this->_ble = new BLE(this->_TSProperties);
    this->_sdCard = new SDCard(this->_TSProperties);
    this->_gsm = new GSMTiny(this->_TSProperties);
    this->_gyroscope = new GyroscopeMPU6050(this->_TSProperties);
    this->_compass = new CompassHMC5883L(this->_TSProperties);
    this->_accelerometer = new AccelerometerMPU6050(this->_TSProperties);
    this->_buzzer = new Buzzer(this->_TSProperties);
    this->_battery = new Battery(this->_TSProperties);

    this->_TSProperties->PropertiesTS.IsInitializingTS = false;
    this->_TSProperties->PropertiesScreen.ActiveScreen = HOME_PAGE_ID;

    this->_controlerButtons->resetLastDateChangementStateButtons();
}

Program::~Program()
{
    ;
}

void Program::executeCore1()
{
    this->_controlerButtons->tick();
    this->_buzzer->tick();
    this->_battery->tick();
    // this->_controlerScreen->tick();
    this->_ble->tick();
    this->_gsm->tick();
    this->_sdCard->tick();
    this->_gyroscope->tick();
    this->_compass->tick();
    this->_accelerometer->tick();
}

void Program::executeCore0()
{
    this->_controlerScreen->tick();
}
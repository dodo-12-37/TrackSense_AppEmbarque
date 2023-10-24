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
    Serial.println("_controlerButtons");
    this->_controlerButtons->tick();

    Serial.println("_buzzer");
    this->_buzzer->tick();

    Serial.println("_battery");
    this->_battery->tick();

    Serial.println("_controlerScreen->tick()");
    this->_controlerScreen->tick();

    Serial.println("_ble");
    this->_ble->tick();

    Serial.println("_gsm");
    this->_gsm->tick();

    Serial.println("_sdCard");
    this->_sdCard->tick();

    Serial.println("_gyroscope");
    this->_gyroscope->tick();

    Serial.println("_compass");
    this->_compass->tick();

    Serial.println("_accelerometer");
    this->_accelerometer->tick();
}

void Program::executeCore0()
{
    Serial.println("                                _controlerScreen");
    this->_controlerScreen->printScreen();
}
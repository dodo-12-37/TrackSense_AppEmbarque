#include "Modules/GPSTinyPlus.h"



GPSTinyPlus::GPSTinyPlus(TrackSenseProperties* trackSenseProperties) : _trackSenseProperties(trackSenseProperties), _GPS(nullptr)
{
    this->_GPS = new TinyGPSPlus();
    // Serial2.begin(GPS_UART_BAUD, SERIAL_8N1, PIN_GPS_LTE_TX, PIN_GPS_LTE_RX);
    Serial2.begin(9600, SERIAL_8N1, PIN_GPS_LTE_TX, PIN_GPS_LTE_RX);
    // Serial2.begin(9600);
}

GPSTinyPlus::~GPSTinyPlus()
{
}

void GPSTinyPlus::tick()
{
    if (this->readDatas())
    {
        this->_trackSenseProperties->PropertiesGPS._latitude = this->_GPS->location.lat();
        this->_trackSenseProperties->PropertiesGPS._longitude = this->_GPS->location.lng();
        this->_trackSenseProperties->PropertiesGPS._altitude = this->_GPS->altitude.meters();
        this->_trackSenseProperties->PropertiesGPS._speed = this->_GPS->speed.kmph();
    }
    
}

bool GPSTinyPlus::readDatas() const
{
    bool result = false;

    while (Serial2.available() > 0)
    {
        result = this->_GPS->encode(Serial2.read());
    }

    return result;
}
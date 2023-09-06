#include "Modules/GPSTinyPlus.h"

GPSTinyPlus::GPSTinyPlus(TrackSenseProperties *trackSenseProperties) : _trackSenseProperties(trackSenseProperties), _GPS(nullptr)
{
    this->_GPS = new TinyGPSPlus();
    Serial2.begin(GPS_UART_BAUD, SERIAL_8N1, PIN_GPS_LTE_RX, PIN_GPS_LTE_TX);
    // Serial2.begin(9600, SERIAL_8N1, PIN_GPS_LTE_RX, PIN_GPS_LTE_TX);

    this->gpsPowerOn();
}

GPSTinyPlus::~GPSTinyPlus()
{
}

void GPSTinyPlus::tick()
{

    if (this->readDatas())
    {
        Serial.println("Write GPS");

        // if (this->_GPS->location.isValid())
        // {
            this->_trackSenseProperties->PropertiesGPS._locationIsValid = true;

            // Serial.println("Write GPS : Location is Valid");
            this->_trackSenseProperties->PropertiesGPS._latitude = this->_GPS->location.lat();
            this->_trackSenseProperties->PropertiesGPS._longitude = this->_GPS->location.lng();
            this->_trackSenseProperties->PropertiesGPS._altitude = this->_GPS->altitude.meters();
            this->_trackSenseProperties->PropertiesGPS._speed = this->_GPS->speed.kmph();
            
        // }
    }
    else
    {
        // Serial.println("Write GPS : Location is not Valid");
        this->_trackSenseProperties->PropertiesGPS._locationIsValid = false;
    }
}

bool GPSTinyPlus::readDatas() const
{
    bool result = false;

    while (Serial2.available() > 0)
    {
        result = this->_GPS->encode(Serial2.read());
    }

    Serial.print("Reading GPS : ");
    Serial.println(result);
    return result;
}

void GPSTinyPlus::gpsPowerOn()
{
    pinMode(PIN_GPS_LTE_PWR, OUTPUT);
    digitalWrite(PIN_GPS_LTE_PWR, LOW);
    delay(1000);
    digitalWrite(PIN_GPS_LTE_PWR, HIGH);
}

void GPSTinyPlus::gpsPowerOff()
{
    pinMode(PIN_GPS_LTE_PWR, OUTPUT);
    digitalWrite(PIN_GPS_LTE_PWR, LOW);
    delay(1500);
    digitalWrite(PIN_GPS_LTE_PWR, HIGH);
}

void GPSTinyPlus::gpsRestart()
{
    gpsPowerOff();
    delay(1000);
    gpsPowerOn();
}
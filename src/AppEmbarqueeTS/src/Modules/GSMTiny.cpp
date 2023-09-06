#include "Modules/GSMTiny.h"



GSMTiny::GSMTiny(TrackSenseProperties *trackSenseProperties) : _trackSenseProperties(trackSenseProperties), modem(nullptr)
{
    this->modem = new TinyGsm(SerialAT);
    Serial1.begin(GPS_UART_BAUD, SERIAL_8N1, PIN_GSM_RX, PIN_GSM_TX);

    this->gpsPowerOn();
}

GSMTiny::~GSMTiny()
{
}

void GSMTiny::tick()
{

    if (this->readDatas())
    {
        Serial.println("Write GPS");

        // if (this->_GPS->location.isValid())
        // {
            this->_trackSenseProperties->PropertiesGPS._locationIsValid = true;

            // Serial.println("Write GPS : Location is Valid");
            this->_trackSenseProperties->PropertiesGPS._latitude = this->modem->location.lat();
            this->_trackSenseProperties->PropertiesGPS._longitude = this->modem->location.lng();
            this->_trackSenseProperties->PropertiesGPS._altitude = this->modem->altitude.meters();
            this->_trackSenseProperties->PropertiesGPS._speed = this->modem->speed.kmph();
            
        // }
    }
    else
    {
        // Serial.println("Write GPS : Location is not Valid");
        this->_trackSenseProperties->PropertiesGPS._locationIsValid = false;
    }
}

bool GSMTiny::readDatas() const
{
    bool result = false;

    // while (Serial2.available() > 0)
    // {
    //     result = this->modem->encode(Serial2.read());
    // }

    Serial.print("Reading GPS : ");
    Serial.println(result);
    return result;
}

void GSMTiny::gpsPowerOn()
{
    pinMode(PIN_GSM_PWR, OUTPUT);
    digitalWrite(PIN_GSM_PWR, LOW);
    delay(1000);
    digitalWrite(PIN_GSM_PWR, HIGH);
}

void GSMTiny::gpsPowerOff()
{
    pinMode(PIN_GSM_PWR, OUTPUT);
    digitalWrite(PIN_GSM_PWR, LOW);
    delay(1500);
    digitalWrite(PIN_GSM_PWR, HIGH);
}

void GSMTiny::gpsRestart()
{
    gpsPowerOff();
    delay(1000);
    gpsPowerOn();
}
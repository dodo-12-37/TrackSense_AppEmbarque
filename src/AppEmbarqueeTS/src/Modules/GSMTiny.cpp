#include "Modules/GSMTiny.h"

GSMTiny::GSMTiny(TrackSenseProperties *trackSenseProperties) : _trackSenseProperties(trackSenseProperties), modem(nullptr)
{
    this->modem = new TinyGsm(SerialAT);
    // Set GSM module baud rate
    SerialAT.begin(GPS_UART_BAUD, SERIAL_8N1, PIN_GSM_RX, PIN_GSM_TX);
}

GSMTiny::~GSMTiny()
{
}

void GSMTiny::init()
{
    // Set GSM module baud rate
    SerialAT.begin(GPS_UART_BAUD, SERIAL_8N1, PIN_GSM_RX, PIN_GSM_TX);

    // Restart takes quite some time
    // To skip it, call init() instead of restart()
    Serial.println("Initializing modem...");
    if (!this->modem->restart())
    {
        Serial.println("Failed to restart modem, attempting to continue without restarting");
        // this->modem.init();
    }

    this->gpsPowerOn();
    modem->enableGPS();
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
        // this->_trackSenseProperties->PropertiesGPS._latitude = this->modem->location.lat();
        // this->_trackSenseProperties->PropertiesGPS._longitude = this->modem->location.lng();
        // this->_trackSenseProperties->PropertiesGPS._altitude = this->modem->altitude.meters();
        // this->_trackSenseProperties->PropertiesGPS._speed = this->modem->speed.kmph();

        // }
    }
    else
    {
        // Serial.println("Write GPS : Location is not Valid");
        this->_trackSenseProperties->PropertiesGPS._locationIsValid = false;
    }
}

bool GSMTiny::readDatas()
{
    bool result = false;

    if (this->modem->getGPS(&this->_lat, &this->_long, &this->_speed, &this->_alt, &this->_vsat, &this->_usat,
                            &this->_accuracy, &this->_year, &this->_month, &this->_day, &this->_hour, &this->_min, &this->_sec))
    {
        result = true;
    }

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
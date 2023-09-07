#include "Modules/GSMTiny.h"

GSMTiny::GSMTiny(TrackSenseProperties *trackSenseProperties) : _trackSenseProperties(trackSenseProperties),
                                                               modem(nullptr),
                                                               _isInitialized(false),
                                                               _TEST_counterGoodValue(0),
                                                               _TEST_counterTotal(0),
                                                               _latitude(0),
                                                               _longitude(0),
                                                               _speed(0),
                                                               _altitude(0),
                                                               _visibleSatellites(0),
                                                               _usedSatellites(0),
                                                               _accuracy(0),
                                                               _year(0),
                                                               _month(0),
                                                               _day(0),
                                                               _hour(0),
                                                               _minute(0),
                                                               _seconde(0),
                                                               _isGpsOn(false),
                                                               _isFixIsValid(false)
{
    this->modem = new TinyGsm(SerialAT);
    // Set GSM module baud rate
    // SerialAT.begin(GPS_UART_BAUD, SERIAL_8N1, PIN_GSM_RX, PIN_GSM_TX);
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
    // this->modem->enableGPS();

    this->_isInitialized = true;
}

void GSMTiny::tick()
{
    if (this->_trackSenseProperties->PropertiesCurrentRide._isRideStarted && this->_trackSenseProperties->PropertiesCurrentRide._isRideFinished == false)
    {
        if (this->readDatas())
        {
            Serial.println("Write GPS");

            if (this->isFixValid())
            {
                // this->_trackSenseProperties->PropertiesCurrentRide._locationIsValid = true;

                Serial.println("Write GPS : Location is Valid");
                this->_trackSenseProperties->PropertiesCurrentRide._latitude = this->_latitude;
                this->_trackSenseProperties->PropertiesCurrentRide._longitude = this->_longitude;
                this->_trackSenseProperties->PropertiesCurrentRide._altitude = this->_altitude;
                this->_trackSenseProperties->PropertiesCurrentRide._speed = this->_speed;
                this->_trackSenseProperties->PropertiesCurrentRide._visibleSatellites = this->_visibleSatellites;
                this->_trackSenseProperties->PropertiesCurrentRide._usedSatellites = this->_usedSatellites;
                this->_trackSenseProperties->PropertiesCurrentRide._accuracy = this->_accuracy;
                this->_trackSenseProperties->PropertiesCurrentRide._year = this->_year;
                this->_trackSenseProperties->PropertiesCurrentRide._month = this->_month;
                this->_trackSenseProperties->PropertiesCurrentRide._day = this->_day;
                this->_trackSenseProperties->PropertiesCurrentRide._hour = this->_hour;
                this->_trackSenseProperties->PropertiesCurrentRide._minute = this->_minute;
                this->_trackSenseProperties->PropertiesCurrentRide._seconde = this->_seconde;

                this->_trackSenseProperties->PropertiesCurrentRide._currentPoint = String();
            }
        }
        else
        {
            // Serial.println("Write GPS : Location is not Valid");
            // this->_trackSenseProperties->PropertiesCurrentRide._locationIsValid = false;
        }
    }
}

bool GSMTiny::readDatas()
{
    bool result = false;

    if (this->_isInitialized && this->_isGpsOn)
    {
        Serial.println("=======================================");
        Serial.println("Requesting current GPS/GNSS/GLONASS location");

        if (this->modem->getGPS(&this->_latitude, &this->_longitude, &this->_speed, &this->_altitude, &this->_visibleSatellites, &this->_usedSatellites,
                                &this->_accuracy, &this->_year, &this->_month, &this->_day, &this->_hour, &this->_minute, &this->_seconde))
        {
            result = true;
            this->_TEST_counterGoodValue++;

#if DEBUG_GSM
            Serial.println("Latitude: " + String(this->_latitude, 10) + "\tLongitude: " + String(this->_longitude, 10));
            Serial.println("Speed: " + String(this->_speed) + "\tAltitude: " + String(this->_altitude));
            Serial.println("Visible Satellites: " + String(this->_visibleSatellites) + "\tUsed Satellites: " + String(this->_usedSatellites));
            Serial.println("Accuracy: " + String(this->_accuracy));
            Serial.println("Year: " + String(this->_year) + "\tMonth: " + String(this->_month) + "\tDay: " + String(this->_day));
            Serial.println("Hour: " + String(this->_hour) + "\tMinute: " + String(this->_minute) + "\tSecond: " + String(this->_seconde));

            Serial.println();
            Serial.println("Retrieving GPS/GNSS/GLONASS location again as a string");
            String gps_raw = this->modem->getGPSraw();
            Serial.println("GPS/GNSS Based Location String: " + gps_raw);

            // Serial.println("=======================================");
            // delay(5000L);
#endif
        }
        else
        {
            Serial.println("Couldn't get GPS/GNSS/GLONASS location, retrying in 10s.");
            // delay(10000L);
        }

        Serial.println("=======================================");
        this->_TEST_counterTotal++;
        this->_trackSenseProperties->PropertiesCurrentRide._TEST_counterGoodValue++;
    }

    return result;
}

bool GSMTiny::isFixValid()
{
    bool result = false;

    if (this->_latitude != 0 && this->_longitude != 0 && this->_usedSatellites >= 4)
    {
        result = true;
    }

    return result;
}

void GSMTiny::saveFixToTSProperties()
{
    this->_trackSenseProperties->PropertiesCurrentRide._latitude = this->_latitude;
    this->_trackSenseProperties->PropertiesCurrentRide._longitude = this->_longitude;
    this->_trackSenseProperties->PropertiesCurrentRide._altitude = this->_altitude;
    this->_trackSenseProperties->PropertiesCurrentRide._speed = this->_speed;
    this->_trackSenseProperties->PropertiesCurrentRide._visibleSatellites = this->_visibleSatellites;
    this->_trackSenseProperties->PropertiesCurrentRide._usedSatellites = this->_usedSatellites;
    this->_trackSenseProperties->PropertiesCurrentRide._accuracy = this->_accuracy;
    this->_trackSenseProperties->PropertiesCurrentRide._year = this->_year;
    this->_trackSenseProperties->PropertiesCurrentRide._month = this->_month;
    this->_trackSenseProperties->PropertiesCurrentRide._day = this->_day;
    this->_trackSenseProperties->PropertiesCurrentRide._hour = this->_hour;
    this->_trackSenseProperties->PropertiesCurrentRide._minute = this->_minute;
    this->_trackSenseProperties->PropertiesCurrentRide._seconde = this->_seconde;

    // idPoint;lat;long;alt;temperature;speed;date;effectiveTime(durée)
    this->_trackSenseProperties->PropertiesCurrentRide._currentPoint = String(23);
}

String GSMTiny::getDate()
{
    String result = String(this->_year) + "-" + String(this->_month) + "-" + String(this->_day);
    Serial.println("Date : " + result);
    return result;
}

String GSMTiny::getTime()
{
    String result = String(this->_hour) + ":" + String(this->_minute) + ":" + String(this->_seconde);
    Serial.println("Time : " + result);
    return result;
}

String GSMTiny::getDatetime()
{
    // AppMobile doit recevoir ceci : 2023-09-03T14:30:00
    String result = this->getDate() + "T" + this->getTime();
    Serial.println("Datetime : " + result);
    return result;
}

void GSMTiny::gpsPowerOn()
{
    pinMode(PIN_GSM_PWR, OUTPUT);
    digitalWrite(PIN_GSM_PWR, LOW);
    delay(1000);
    digitalWrite(PIN_GSM_PWR, HIGH);
    this->_isGpsOn = true;
}

void GSMTiny::gpsPowerOff()
{
    pinMode(PIN_GSM_PWR, OUTPUT);
    digitalWrite(PIN_GSM_PWR, LOW);
    delay(1500);
    digitalWrite(PIN_GSM_PWR, HIGH);
    this->_isGpsOn = false;
}

void GSMTiny::gpsRestart()
{
    gpsPowerOff();
    delay(1000);
    gpsPowerOn();
}

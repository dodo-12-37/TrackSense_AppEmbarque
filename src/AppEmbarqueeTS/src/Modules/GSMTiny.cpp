#include "Modules/GSMTiny.h"

GSMTiny::GSMTiny(TSProperties *TSProperties) : _TSProperties(TSProperties),
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
                                               _isModemOn(false),
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
    this->modemPowerOn();

    // Set GSM module baud rate
    SerialAT.begin(GPS_UART_BAUD, SERIAL_8N1, PIN_GSM_RX, PIN_GSM_TX);

    // Restart takes quite some time
    // To skip it, call init() instead of restart()
    Serial.println("Initializing modem...");

    if (this->modem->testAT())
    {
        Serial.println("Modem is finally functional");
        Serial.println("Modem initialized.");
    }
    else
    {
        if (!this->modem->restart())
        {
            Serial.println("Failed to restart modem, attempting to continue without restarting");

            if (!this->modem->init())
            {
                Serial.println("Failed to initialize modem.");
            }
        }
        Serial.println("Modem is not functional");
        Serial.println("Modem not initialized.");
    }

    this->gpsRestart();
    this->setWorkModeGPS(); // TODO : Activer paramètres GLONASS et GALILEO //
    this->_isInitialized = true;
    this->_TSProperties->PropertiesTS._isInitializedGSM = true;
}

void GSMTiny::tick()
{

    /* PropertiesBattery */
    this->_TSProperties->PropertiesBattery._batteryLevel = this->modem->getBattPercent();

    Serial.println("=======================================");
#if DEBUG_GSM
    Serial.println("Tick GSM");
    Serial.println("_isRideStarted : " + String(this->_TSProperties->PropertiesCurrentRide._isRideStarted));
    Serial.println("_isRideFinished : " + String(this->_TSProperties->PropertiesCurrentRide._isRideFinished));
#endif

    if (this->_TSProperties->PropertiesCurrentRide._isRideStarted && this->_TSProperties->PropertiesCurrentRide._isRideFinished == false)
    {
        if (this->_isGpsOn == false && this->_isModemOn == true && this->_isInitialized == true)
        {
            this->gpsPowerOn();
        }

        if (this->readDatas())
        {
            this->saveFixToTSProperties();
            // if (this->isFixValid())
            // {
            //     this->saveFixToTSProperties();
            //     // this->_TEST_counterGoodValue++;
            //     this->_TSProperties->PropertiesGPS._TEST_counterGoodValue++;
            // }
            // else
            // {
            //     this->saveFixToTSProperties();
            //     this->_TSProperties->PropertiesCurrentRide._isPointReadyToSave = false;
            // }
        }
        else
        {
            Serial.println("Write GPS : Location is not Valid");
            // this->_TSProperties->PropertiesCurrentRide._locationIsValid = false;
        }
    }
    else
    {
        Serial.println("Write GPS : Ride is not Started");
        if (this->_isGpsOn == true && this->_isModemOn == true && this->_isInitialized == true)
        {
            this->gpsPowerOff();
        }
    }
}

bool GSMTiny::readDatas()
{
    bool result = false;

    if (this->_isInitialized && this->_isGpsOn)
    {
        Serial.println("Requesting current GPS/GNSS/GLONASS location");

        if (this->modem->getGPS(&this->_latitude, &this->_longitude, &this->_speed, &this->_altitude, &this->_visibleSatellites, &this->_usedSatellites,
                                &this->_accuracy, &this->_year, &this->_month, &this->_day, &this->_hour, &this->_minute, &this->_seconde))
        {
            result = true;
            // // this->_TEST_counterGoodValue++;
            // this->_TSProperties->PropertiesGPS._TEST_counterGoodValue++;

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
            Serial.println("Couldn't get GPS/GNSS/GLONASS location.");
            // delay(10000L);
        }

        Serial.println("=======================================");
        // this->_TEST_counterTotal++;
        this->_TSProperties->PropertiesGPS._TEST_counterTotal++;
    }

    return result;
}

bool GSMTiny::isFixValid()
{
    bool result = false;

    if (this->_latitude != 0 && this->_longitude != 0 && this->_usedSatellites >= 4 && this->_speed != -9999.00)
    {
        result = true;
    }

    return result;
}

void GSMTiny::saveFixToTSProperties()
{
    this->_TSProperties->PropertiesGPS._latitude = this->_latitude;
    this->_TSProperties->PropertiesGPS._longitude = this->_longitude;
    this->_TSProperties->PropertiesGPS._altitude = this->_altitude;
    this->_TSProperties->PropertiesGPS._speed = this->_speed;
    this->_TSProperties->PropertiesGPS._visibleSatellites = this->_visibleSatellites;
    this->_TSProperties->PropertiesGPS._usedSatellites = this->_usedSatellites;
    this->_TSProperties->PropertiesGPS._accuracy = this->_accuracy;
    this->_TSProperties->PropertiesGPS._year = this->_year;
    this->_TSProperties->PropertiesGPS._month = this->_month;
    this->_TSProperties->PropertiesGPS._day = this->_day;
    this->_TSProperties->PropertiesGPS._hour = this->_hour;
    this->_TSProperties->PropertiesGPS._minute = this->_minute;
    this->_TSProperties->PropertiesGPS._seconde = this->_seconde;
    this->_TSProperties->PropertiesGPS.IsValid = this->isFixValid();

    if (this->_TSProperties->PropertiesGPS.IsValid)
    {
        if (this->_TSProperties->PropertiesCurrentRide._dateBegin == "0000-00-00T00:00:00")
        {
            this->_TSProperties->PropertiesCurrentRide._dateBegin = this->getDatetime();
        }

        this->_TSProperties->PropertiesCurrentRide._pointID++;
        this->_TSProperties->PropertiesCurrentRide._dateEnd = this->getDatetime();
        this->_TSProperties->PropertiesCurrentRide._temperature = this->_TSProperties->PropertiesTemperature._temperature;
        this->_TSProperties->PropertiesCurrentRide._durationS = (millis() - this->_TSProperties->PropertiesCurrentRide._startTimeMS) / 1000;
        // idPoint;lat;long;alt;temperature;speed;date;effectiveTime(durée)
        this->_TSProperties->PropertiesCurrentRide._currentPoint = String(this->_TSProperties->PropertiesCurrentRide._pointID) + ";" +
                                                                   String(this->_latitude, 10) + ";" +
                                                                   String(this->_longitude, 10) + ";" +
                                                                   String(this->_altitude) + ";" +
                                                                   String(this->_TSProperties->PropertiesCurrentRide._temperature) + ";" +
                                                                   String(this->_speed) + ";" +
                                                                   this->getDatetime() + ";" +
                                                                   String(this->_TSProperties->PropertiesCurrentRide._durationS);
        this->_TSProperties->PropertiesCurrentRide._isPointReadyToSave = true;
    }
}

String GSMTiny::getDate()
{
    String month = String(this->_month);
    if (month.length() == 1)
    {
        month = "0" + month;
    }
    String day = String(this->_day);
    if (day.length() == 1)
    {
        day = "0" + day;
    }

    String result = String(this->_year) + "-" + month + "-" + day;
    Serial.println("Date : " + result);
    return result;
}

String GSMTiny::getTime()
{
    String hour = String(this->_hour);
    if (hour.length() == 1)
    {
        hour = "0" + hour;
    }
    String minute = String(this->_minute);
    if (minute.length() == 1)
    {
        minute = "0" + minute;
    }
    String seconde = String(this->_seconde);
    if (seconde.length() == 1)
    {
        seconde = "0" + seconde;
    }

    String result = hour + ":" + minute + ":" + seconde;
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
    /*
        Parameters :
        <operation>
            0 Set the GPIO function including the GPIO output .
            1 Read the GPIO level. Please note that only when the gpio is set as input, user can use parameter 1 to read the GPIO level, otherwise the module will return "ERROR".

        <pin>
            The PIN index you want to be set. (It has relations with the hardware, please refer to the hardware manual)

        <function>
            Only when <operation> is set to 0, this option takes effect.
            0 Set the GPIO to input.
            1 Set the GPIO to output.

        <level>
            0 Set the GPIO low level
            1 Set the GPIO high level
    */

    // Set SIM7000G GPIO4 HIGH ,turn on GPS power
    // CMD:AT+SGPIO=0,4,1,1
    // Only in version 20200415 is there a function to control GPS power
    this->modem->sendAT("+SGPIO=0,4,1,1");
    if (this->modem->waitResponse(10000L) != 1)
    {
        Serial.println(" SGPIO=0,4,1,1 false ");
    }

    this->modem->enableGPS();
    this->_isGpsOn = true;
    delay(1000);
}

void GSMTiny::gpsPowerOff()
{
    Serial.println("Disabling GPS");
    this->modem->disableGPS();

    // Set SIM7000G GPIO4 LOW ,turn off GPS power
    // CMD:AT+SGPIO=0,4,1,0
    // Only in version 20200415 is there a function to control GPS power.
    // Version 20200415 (Version 1.1)
    // Version 20191227 (Version 1.0)
    // Revision:1529B08SIM7000G
    this->modem->sendAT("+SGPIO=0,4,1,0"); // devrait pt être "+CGPIO=0,4,1,0"
    if (this->modem->waitResponse(10000L) != 1)
    {
        Serial.println(" SGPIO=0,4,1,0 false ");
    }

    delay(200);
    this->_isGpsOn = false;
}

void GSMTiny::gpsRestart()
{
    gpsPowerOff();
    delay(1000);
    gpsPowerOn();
}

void GSMTiny::modemPowerOn()
{
    pinMode(PIN_GSM_PWR, OUTPUT);
    digitalWrite(PIN_GSM_PWR, LOW);
    delay(300);
    digitalWrite(PIN_GSM_PWR, HIGH);
    // this->modem->enableGPS();
    this->_isModemOn = true;
    delay(1000);
}

void GSMTiny::modemPowerOff()
{
    // this->modem->disableGPS();
    pinMode(PIN_GSM_PWR, OUTPUT);
    digitalWrite(PIN_GSM_PWR, LOW);
    delay(300);
    digitalWrite(PIN_GSM_PWR, HIGH);
    this->_isModemOn = false;
}

void GSMTiny::modemRestart()
{
    modemPowerOff();
    delay(1000);
    modemPowerOn();
}

/*
    Set work mode of SIM7000G GPS with AT Command "AT+CGNSMOD=1,1,1,1"

    Type of commands :
    Test Command : AT+CGNSMOD=?
    Read Command : AT+CGNSMOD?
    Set Command  : AT+CGNSMOD=<GPS mode>,<glonass mode>,<beidou mode>,<galieo mode>

    Parameters :
    <GPS mode>     :    1 - Enable GPS
    <glonass mode> :    0 - Disable GLONASS     1 - Enable GLONASS
    <beidou mode>  :    0 - Disable BeiDou      1 - Enable BeiDou
    <galieo mode>  :    0 - Disable Galileo     1 - Enable Galileo
*/
void GSMTiny::setWorkModeGPS()
{
    this->modem->sendAT("+CGNSMOD=1,1,1,1");
    if (this->modem->waitResponse(10000L) != 1)
    {
        Serial.print(" CGNSMOD=1,1,1,1 ");
        Serial.println(" Activate GPS, GLONASS, BeiDou, Galileo work mode.");
    }
}

bool GSMTiny::isInitialized()
{
    return this->_isInitialized;
}

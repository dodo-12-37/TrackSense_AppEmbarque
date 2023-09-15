#pragma once
#include <Arduino.h>
#include "TSProperties.h"

class TSProperties
{
public:
    /* Datas TrackSense */
    struct TSPropertiesTS
    {
        bool _isInitializingTS;
        bool _isInitializedGSM;
    } PropertiesTS;

    /* datas Current ride */
    struct TSPropertiesCurrentRide
    {
        bool _isRideStarted;
        bool _isRidePaused;
        bool _isRideFinished;

        String _completedRideId;
        String _plannedRideId;
        double _maxSpeed;
        double _avgSpeed;
        double _distance;

        unsigned long _durationS;
        unsigned long _startTimeMS;
        unsigned long _endTimeMS;
        
        String _dateBegin;
        String _dateEnd;
        String _currentPoint;
        int _nbPoints;
        int _pointID;
        int _nbFalls;
        bool _isRideReadyToSave;
        bool _isPointReadyToSave;
        float _temperature;


        void resetCurrentRide()
        {
            this->_isRideStarted = false;
            this->_isRidePaused = false;
            this->_isRideFinished = false;
            
            this->_completedRideId = "00000000-0000-0000-0000-000000000000";
            this->_plannedRideId = "00000000-0000-0000-0000-000000000000";
            this->_maxSpeed = 0;
            this->_avgSpeed = 0;
            this->_distance = 0;
            this->_durationS = 0;
            this->_dateBegin = "0000-00-00T00:00:00";
            this->_dateEnd = "0000-00-00T00:00:00";
            this->_currentPoint = "";
            this->_nbPoints = 0;
            this->_pointID = 0;
            this->_nbFalls = 0;
            this->_isRideReadyToSave = false;
            this->_isPointReadyToSave = false;
            this->_temperature = 0;
            this->_startTimeMS = 0;
            this->_endTimeMS = 0;
        }
    } PropertiesCurrentRide;

    /* datas GPS */
    struct TSPropertiesGPS
    {
        // datas brute GPS
        float _latitude;
        float _longitude;
        float _altitude;
        float _speed;
        int _visibleSatellites;
        int _usedSatellites;
        float _accuracy;
        int _year;
        int _month;
        int _day;
        int _hour;
        int _minute;
        int _seconde;
        bool IsValid;

        int _TEST_counterGoodValue;
        int _TEST_counterTotal;

        float mph() { return 0.621371 * _speed; }
        float miles() { return 0.00062137112 * _altitude; }

        void resetGPSValues()
        {
            this->_latitude = 0;
            this->_longitude = 0;
            this->_altitude = 0;
            this->_speed = 0;
            this->_visibleSatellites = 0;
            this->_usedSatellites = 0;
            this->_accuracy = 0;
            this->_year = 0;
            this->_month = 0;
            this->_day = 0;
            this->_hour = 0;
            this->_minute = 0;
            this->_seconde = 0;
            this->_TEST_counterGoodValue = 0;
            this->_TEST_counterTotal = 0;
            this->IsValid = false;
        }
    } PropertiesGPS;

    /* datas Buttons */
    struct TSPropertiesButtons
    {
        // bool _isButton1Pressed;
        // bool _isButton2Pressed;
        int _button1State;
        int _button2State;
    } PropertiesButtons;

    /* datas Screen */
    struct TSPropertiesScreen
    {
        /*
            0 : Init TS Page
            1 : Home Page
            2 : Compass Page
            3 : Ride Direction Page
            4 : Ride Page
            5 : Global Statistics Page
            6 : Go Home Page
            7 : Ride Statistics Page
            -1 : No Page (error)
        */
        uint8_t _activeScreen;
        bool _isNewActivePage;
        bool _isDarkMode;

        /*
            0 : Pins vers le haut
            1 : Pins vers la gauche
            2 : Pins vers le bas
            3 : Pins vers la droite
        */
        uint8_t _screenRotation;

    } PropertiesScreen;

    /* datas SD Card */
    struct TSPropertiesSDCard
    {
        ;
    } PropertiesSDCard;

    /* datas Bluetooth */
    struct TSPropertiesBluetooth
    {
        bool _isDeviceBluetoothConnected;

        // bool _isBluetoothConnected;
        // bool _isBluetoothActivated;
    } PropertiesBluetooth;

    /* datas LTE */
    struct TSPropertiesLTE
    {
        bool _isDeviceLTEConnected;
    } PropertiesLTE;

    /* datas Wifi */
    struct TSPropertiesWifi
    {
        ;
    } PropertiesWifi;

    /* datas Compass */
    struct TSPropertiesCompass
    {
        double _heading_angle; // PositionNord
        double _declinationAngle;
        // double _calibrationCompassX;
        // double _calibrationCompassY;
        // double _calibrationCompassZ;
    } PropertiesCompass;

    /* datas Gyroscope */
    struct TSPropertiesGyroscope
    {
        double _roll_angle;  // PositionRoulis
        double _pitch_angle; // PositionTangage
        double _yaw_angle;   // PositionLacet
    } PropertiesGyroscope;

    /* datas Accelerometer */
    struct TSPropertiesAccelerometer
    {
        double _acceleration_x;
        double _acceleration_y;
        double _acceleration_z;
    } PropertiesAccelerometer;

    /* datas Temperature */
    struct TSPropertiesTemperature
    {
        double _temperature;
    } PropertiesTemperature;

    /* datas Battery */
    struct TSPropertiesBattery
    {
        double _batteryLevel;
    } PropertiesBattery;

    /* datas Buzzer */
    struct TSPropertiesBuzzer
    {
        bool _isBuzzerOn;
    } PropertiesBuzzer;

    /* datas CompletedRide to send */
    struct TSPropertiesCompletedRideToSend
    {
        String _completedRideId;
        String _stats;
        String _point;
        int _currentPoint;
        int _nbPoints;

        bool _isPointReady;
        bool _isPointReceived;

        bool _isReady;
        bool _isReceived;
    } PropertiesCompletedRideToSend;

    /* Methods */
    TSProperties();
    ~TSProperties();
};

#pragma once
#include <Arduino.h>
#include "TrackSenseProperties.h"

class TrackSenseProperties
{
public:
    /* Datas TrackSense */
    struct TrackSensePropertiesTS
    {
        String _currentRideId;
        bool _isInitializingTS;
    } PropertiesTS;

    /* datas Current ride */
    struct TrackSensePropertiesCurrentRide
    {
        bool _isRideStarted;
        bool _isRidePaused;
        bool _isRideFinished;

        String _completedRideId; 
        String _routeId;    //
        double _maxSpeed;
        double _avgSpeed;
        double _distance;
        double _duration;
        String _dateBegin;    //
        String _dateEnd;    //
        String _currentPoint;   //
        int _nbPoints;
        int _nbFalls;
        bool _isRideReadyToSave;
        bool _isPointReadyToSave; 

        // datas brute
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

        int _TEST_counterGoodValue;
        int _TEST_counterTotal;
    } PropertiesCurrentRide;

    /* datas Buttons */
    struct TrackSensePropertiesButtons
    {
        // bool _isButton1Pressed;
        // bool _isButton2Pressed;
        int _button1State;
        int _button2State;
    } PropertiesButtons;

    /* datas Screen */
    struct TrackSensePropertiesScreen
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
            1 : Pins vers la droite (???)
            2 : Pins vers le bas (???)
            3 : Pins vers la gauche (???)

            0 : Right to left
            1 : Reverse Mode
            2 : Bottom to top
            3 : 
        */
       uint8_t _screenRotation;
        
    } PropertiesScreen;

    /* datas SD Card */
    struct TrackSensePropertiesSDCard
    {
        ;
    } PropertiesSDCard;

    /* datas Bluetooth */
    struct TrackSensePropertiesBluetooth
    {
        bool _isDeviceBluetoothConnected;

        // bool _isBluetoothConnected;
        // bool _isBluetoothActivated;
    } PropertiesBluetooth;

    /* datas LTE */
    struct TrackSensePropertiesLTE
    {
        bool _isDeviceLTEConnected;
    } PropertiesLTE;

    /* datas Wifi */
    struct TrackSensePropertiesWifi
    {
        ;
    } PropertiesWifi;

    /* datas GPS */
    struct TrackSensePropertiesGPS
    {
        // float _latitude;
        // float _longitude;
        // float _altitude;
        // float _speed;
        // int _visibleSatellites;
        // int _usedSatellites;
        // float _accuracy;
        // int _year;
        // int _month;
        // int _day;
        // int _hour;
        // int _minute;
        // int _seconde;


        // float mph() { return 0.621371 * _speed; }
        // float miles() { return 0.00062137112 * _altitude; }

        // int _TEST_counterGoodValue;
        // int _TEST_counterTotal;
    } PropertiesGPS;

    /* datas Compass */
    struct TrackSensePropertiesCompass
    {
        double _heading_angle; // PositionNord
        double _declinationAngle;
        // double _calibrationCompassX;
        // double _calibrationCompassY;
        // double _calibrationCompassZ;
    } PropertiesCompass;

    /* datas Gyroscope */
    struct TrackSensePropertiesGyroscope
    {
        double _roll_angle;  // PositionRoulis
        double _pitch_angle; // PositionTangage
        double _yaw_angle;   // PositionLacet
    } PropertiesGyroscope;

    /* datas Accelerometer */
    struct TrackSensePropertiesAccelerometer
    {
        double _acceleration_x;
        double _acceleration_y;
        double _acceleration_z;
    } PropertiesAccelerometer;

    /* datas Temperature */
    struct TrackSensePropertiesTemperature
    {
        double _temperature;
    } PropertiesTemperature;

    /* datas Battery */
    struct TrackSensePropertiesBattery
    {
        double _batteryLevel;
    } PropertiesBattery;

    /* datas Buzzer */
    struct TrackSensePropertiesBuzzer
    {
        bool _isBuzzerOn;
    } PropertiesBuzzer;

    /* datas CompletedRide to send */
    struct TrackSensePropertiesCompletedRideToSend
    {
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
    TrackSenseProperties();
    ~TrackSenseProperties();
};

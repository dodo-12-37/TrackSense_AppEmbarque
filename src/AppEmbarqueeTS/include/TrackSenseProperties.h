#pragma once
#include <Arduino.h>
#include "TrackSenseProperties.h"

class TrackSenseProperties
{
public:
    /* Datas TrackSense */
    struct TrackSensePropertiesTS
    {
        bool _isRideStarted;
        bool _isRidePaused;
        bool _isRideFinished;
        
        // bool _isRideSaved;
        // bool _isRideDeleted;

        String _currentRideId;

        // VRAIMENT NECESSAIRE ?? //
        // bool _isWIFIConnected;
        // bool _isBluetoothConnected;
        // bool _isLTEConnected;
        // bool _isSDCardConnected;
        // bool _isScreenConnected;
        // bool _isGPSConnected;
        // bool _isCompassConnected;
        // bool _isGyroscopeConnected;
        // bool _isAccelerometerConnected;
        // bool _isTemperatureConnected;
        // bool _isBatteryConnected;
        // bool _isButton1Connected;
        // bool _isButton2Connected;
        // bool _isBuzzerConnected;
    } PropertiesTS;

    /* datas Current ride */
    struct TrackSensePropertiesCurrentRide
    {
        String _completedRideId;
        String _routeId;
        double _maxSpeed;
        double _avgSpeed;
        double _distance;
        double _duration;
        String _dateBegin;
        String _dateEnd;
        String _currentPoint;
        int _nbPoints;
        int _nbFalls;
        bool _isRideReadyToSave;
        bool _isPointReadyToSave;
    } PropertiesCurrentRide;

    /* datas Buttons */
    struct TrackSensePropertiesButton
    {
        // bool _isButton1Pressed;
        // bool _isButton2Pressed;
        int _TEST_Button1State;
        int _TEST_Button2State;
    } PropertiesButtons;

    /* datas Screen */
    struct TrackSensePropertiesScreen
    {
        /*
            1 : Home Page
            2 : Compass Page
            3 : Ride Direction Page
            4 : Ride Page
            5 : Global Statistics Page
            6 : Go Home Page
            7 : Ride Statistics Page
            0 : No Page (error)
        */
        uint8_t _activeScreen;
        bool _isDarkMode;

        
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
        double _latitude;
        double _longitude;
        double _altitude;
        double _speed;
        String _date;
        String _time;
        bool _locationIsValid;

        double mph() { return 0.621371 * _speed; }
        double miles() { return 0.00062137112 * _altitude; }
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
    // struct TrackSensePropertiesCompletedRideToSend
    // {
    //     String _completedRideId;
    //     String _routeId;
    //     double _maxSpeed;
    //     double _avgSpeed;
    //     double _distance;
    //     double _duration;
    //     String _dateBegin;
    //     String _dateEnd;
    //     String _points;
    //     int _nbPoints;
    //     int _nbFalls;
    //     bool _isReady;
    //     bool _isReceived;
    // } PropertiesCompletedRideToSend;
    /* datas CompletedRide to send */
    struct TrackSensePropertiesCompletedRideToSend
    {
        String _stats;
        String _points;
        bool _isReady;
        bool _isReceived;
    } PropertiesCompletedRideToSend;

    /* Methods */
    TrackSenseProperties();
    ~TrackSenseProperties();
};

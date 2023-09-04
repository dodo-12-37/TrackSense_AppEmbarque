#pragma once
#include <Arduino.h>
#include "TrackSenseProperties.h"



class TrackSenseProperties
{
// private:
public:
    /* Datas TrackSense */
    bool _isRideStarted;
    bool _isRidePaused;
    bool _isRideStopped;
    // bool _isRideSaved;
    // bool _isRideDeleted;

    String _currentRideId;


    bool _TEST_isButton1Pressed;
    bool _TEST_isButton2Pressed;

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

    bool _isBuzzerOn;



    /* datas GPS */
    double _latitude;
    double _longitude;
    double _altitude;
    double _speed;

    /* datas Compass */
    double _heading_angle;  //PositionNord
    double _declinationAngle;
    // double _calibrationCompassX;
    // double _calibrationCompassY;
    // double _calibrationCompassZ;

    /* datas Gyroscope */
    double _roll_angle;     //PositionRoulis
    double _pitch_angle;    //PositionTangage
    double _yaw_angle;      //PositionLacet

    /* datas Accelerometer */
    double _acceleration_x;
    double _acceleration_y;
    double _acceleration_z;

    /* datas Temperature */
    double _temperature;

    /* datas Battery */

    /* datas SD Card */

    /* datas Screen */
    bool _isHomePage;
    bool _isCompassPage;
    bool _isRideDirectionPage;
    bool _isRidePage;
    bool _isGlobalStatisticsPage;
    bool _isGoHomePage;
    bool _isRideStatisticsPage;
    bool _isDarkMode;

    /* datas Wifi */

    /* datas Bluetooth */
    bool _isDeviceConnected;


    /* datas LTE */

    /* datas Button */

    /* datas LED */

    /* datas Buzzer */



// public:
    TrackSenseProperties();
    ~TrackSenseProperties();
};

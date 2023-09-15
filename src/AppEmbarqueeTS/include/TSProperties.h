#pragma once
#include <Arduino.h>
#include "TSProperties.h"

class TSProperties
{
public:
    /* Datas TrackSense */
    struct TSPropertiesTS
    {
        bool IsInitializingTS;
        bool IsInitializedGSM;
    } PropertiesTS;

    /* datas Current ride */
    struct TSPropertiesCurrentRide
    {
        bool IsRideStarted;
        bool IsRidePaused;
        bool IsRideFinished;

        String CompletedRideId;
        String PlannedRideId;
        double MaxSpeed;
        double AvgSpeed;
        double Distance;

        unsigned long DurationS;
        unsigned long StartTimeMS;
        unsigned long EndTimeMS;
        
        String DateBegin;
        String DateEnd;
        String CurrentPoint;
        int NbPoints;
        int PointID;
        int NbFalls;
        bool IsRideReadyToSave;
        bool IsPointReadyToSave;
        float Temperature;


        void resetCurrentRide()
        {
            this->IsRideStarted = false;
            this->IsRidePaused = false;
            this->IsRideFinished = false;
            
            this->CompletedRideId = "00000000-0000-0000-0000-000000000000";
            this->PlannedRideId = "00000000-0000-0000-0000-000000000000";
            this->MaxSpeed = 0;
            this->AvgSpeed = 0;
            this->Distance = 0;
            this->DurationS = 0;
            this->DateBegin = "0000-00-00T00:00:00";
            this->DateEnd = "0000-00-00T00:00:00";
            this->CurrentPoint = "";
            this->NbPoints = 0;
            this->PointID = 0;
            this->NbFalls = 0;
            this->IsRideReadyToSave = false;
            this->IsPointReadyToSave = false;
            this->Temperature = 0;
            this->StartTimeMS = 0;
            this->EndTimeMS = 0;
        }
    } PropertiesCurrentRide;

    /* datas GPS */
    struct TSPropertiesGPS
    {
        // datas brute GPS
        float Latitude;
        float Longitude;
        float Altitude;
        float Speed;
        int VisibleSatellites;
        int UsedSatellites;
        float Accuracy;
        int Year;
        int Month;
        int Day;
        int Hour;
        int Minute;
        int Seconde;
        bool IsValid;

        int CounterGoodValue;
        int CounterTotal;

        float mph() { return 0.621371 * Speed; }
        float miles() { return 0.00062137112 * Altitude; }

        void resetGPSValues()
        {
            this->Latitude = 0;
            this->Longitude = 0;
            this->Altitude = 0;
            this->Speed = 0;
            this->VisibleSatellites = 0;
            this->UsedSatellites = 0;
            this->Accuracy = 0;
            this->Year = 0;
            this->Month = 0;
            this->Day = 0;
            this->Hour = 0;
            this->Minute = 0;
            this->Seconde = 0;
            this->CounterGoodValue = 0;
            this->CounterTotal = 0;
            this->IsValid = false;
        }
    } PropertiesGPS;

    /* datas Buttons */
    struct TSPropertiesButtons
    {
        // bool IsButton1Pressed;
        // bool IsButton2Pressed;
        int Button1State;
        int Button2State;
    } PropertiesButtons;

    /* datas Screen */
    struct TSPropertiesScreen
    {
        /*
            0 : Home Page
            1 : Ride Page
            2 : Ride Statistics Page
            3 : Compass Page
            4 : Ride Direction Page
            5 : Global Statistics Page
            6 : Go Home Page
            -1 : Init TS Page
            -2 : No Page (error)
        */
        int ActiveScreen;
        bool IsNewActivePage;
        bool IsDarkMode;

        /*
            0 : Pins vers le haut
            1 : Pins vers la gauche
            2 : Pins vers le bas
            3 : Pins vers la droite
        */
        uint8_t ScreenRotation;

    } PropertiesScreen;

    /* datas SD Card */
    struct TSPropertiesSDCard
    {
        ;
    } PropertiesSDCard;

    /* datas Bluetooth */
    struct TSPropertiesBluetooth
    {
        bool IsDeviceBluetoothConnected;

        // bool IsBluetoothConnected;
        // bool IsBluetoothActivated;
    } PropertiesBluetooth;

    /* datas LTE */
    struct TSPropertiesLTE
    {
        bool IsDeviceLTEConnected;
    } PropertiesLTE;

    /* datas Wifi */
    struct TSPropertiesWifi
    {
        ;
    } PropertiesWifi;

    /* datas Compass */
    struct TSPropertiesCompass
    {
        double Heading_angle; // PositionNord
        double DeclinationAngle;
        // double CalibrationCompassX;
        // double CalibrationCompassY;
        // double CalibrationCompassZ;
    } PropertiesCompass;

    /* datas Gyroscope */
    struct TSPropertiesGyroscope
    {
        double RollAngle;  // PositionRoulis
        double PitchAngle; // PositionTangage
        double YawAngle;   // PositionLacet
    } PropertiesGyroscope;

    /* datas Accelerometer */
    struct TSPropertiesAccelerometer
    {
        double Acceleration_x;
        double Acceleration_y;
        double Acceleration_z;
    } PropertiesAccelerometer;

    /* datas Temperature */
    struct TSPropertiesTemperature
    {
        double Temperature;
    } PropertiesTemperature;

    /* datas Battery */
    struct TSPropertiesBattery
    {
        double BatteryLevel;
    } PropertiesBattery;

    /* datas Buzzer */
    struct TSPropertiesBuzzer
    {
        bool IsBuzzerOn;
    } PropertiesBuzzer;

    /* datas CompletedRide to send */
    struct TSPropertiesCompletedRideToSend
    {
        String CompletedRideId;
        String Stats;
        String Point;
        int CurrentPoint;
        int NbPoints;

        bool IsPointReady;
        bool IsPointReceived;

        bool IsReady;
        bool IsReceived;
    } PropertiesCompletedRideToSend;

    /* Methods */
    TSProperties();
    ~TSProperties();
};

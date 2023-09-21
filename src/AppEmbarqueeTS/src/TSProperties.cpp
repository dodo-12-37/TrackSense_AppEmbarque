#include "TSProperties.h"



TSProperties::TSProperties()
{
    this->initProperties();
}

TSProperties::~TSProperties()
{
    ;
}

void TSProperties::initProperties()
{
    // TS
    this->PropertiesTS.IsInitializingTS = true;

    // Battery
    this->PropertiesBattery.BatteryLevel = 0;

    // Buttons
    this->PropertiesButtons.Button1State = 0;
    this->PropertiesButtons.Button2State = 0;

    // Buzzer
    this->PropertiesBuzzer.IsBuzzerOn = false;

    // Screen
    this->PropertiesScreen.ActiveScreen = INIT_TS_PAGE_ID;
    this->PropertiesScreen.IsDarkMode = true;
    this->PropertiesScreen.ScreenRotation = 0;
    this->PropertiesScreen.IsNewActivePage = true;

    // Ride
    this->PropertiesCurrentRide.IsRideStarted = false;
    this->PropertiesCurrentRide.IsRidePaused = false;
    this->PropertiesCurrentRide.IsRideFinished = false;

    // BLE
    this->PropertiesCompletedRideToSend.CompletedRideId = "00000000-0000-0000-0000-000000000000";
    this->PropertiesCompletedRideToSend.Stats = "";
    this->PropertiesCompletedRideToSend.Point = "";
    this->PropertiesCompletedRideToSend.CurrentPoint = 0;
    this->PropertiesCompletedRideToSend.NbPoints = 0;
    this->PropertiesCompletedRideToSend.IsPointReady = false;
    this->PropertiesCompletedRideToSend.IsPointReceived = false;
    this->PropertiesCompletedRideToSend.IsReady = false;
    this->PropertiesCompletedRideToSend.IsReceived = false;

    // GPS
    this->PropertiesGPS.resetGPSValues();

    // Current Ride
    this->PropertiesCurrentRide.resetCurrentRide();
}
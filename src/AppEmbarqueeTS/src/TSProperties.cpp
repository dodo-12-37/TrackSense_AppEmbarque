#include "TSProperties.h"



TSProperties::TSProperties() : PropertiesTS(),
                               PropertiesBattery(),
                               PropertiesButtons(),
                               PropertiesBuzzer(),
                               PropertiesScreen(),
                               PropertiesCurrentRide(),
                               PropertiesCompletedRideToSend(),
                               PropertiesGPS()
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
    this->PropertiesTS.IsInitializedGSM = true;

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

    // Current Ride
    this->PropertiesCurrentRide.IsRideStarted = false;
    this->PropertiesCurrentRide.IsRidePaused = false;
    this->PropertiesCurrentRide.IsRideFinished = false;
    this->PropertiesCurrentRide.IsRideReadyToSave = false;
    this->PropertiesCurrentRide.resetCurrentRide();
    
    // BLE
    this->PropertiesCompletedRideToSend.CompletedRideId = "00000000-0000-0000-0000-000000000000";
    this->PropertiesCompletedRideToSend.Stats = "";
    this->PropertiesCompletedRideToSend.Point = "";
    this->PropertiesCompletedRideToSend.CurrentPointNumber = 0;
    this->PropertiesCompletedRideToSend.NbPoints = 0;
    this->PropertiesCompletedRideToSend.IsPointReady = false;
    this->PropertiesCompletedRideToSend.IsPointReceived = false;
    this->PropertiesCompletedRideToSend.IsReady = false;
    this->PropertiesCompletedRideToSend.IsReceived = false;

    // GPS
    this->PropertiesGPS.resetGPSValues();

}
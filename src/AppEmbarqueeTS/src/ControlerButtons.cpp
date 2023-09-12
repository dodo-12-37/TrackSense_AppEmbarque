#include "ControlerButtons.h"

ControlerButtons::ControlerButtons(TSProperties *TSProperties) : _TSProperties(TSProperties),
                                                                                 _button1(nullptr),
                                                                                 _button2(nullptr),
                                                                                 // _isPressedButton1(false),
                                                                                 // _isPressedButton2(false),
                                                                                 _finalStateButton1(0),
                                                                                 _finalStateButton2(0),
                                                                                 _guidGenerator(nullptr)
{
    this->_button1 = new ButtonTactile(PIN_BUTTON1, _TSProperties);
    this->_button2 = new ButtonTactile(PIN_BUTTON2, _TSProperties);
    this->_guidGenerator = new UUID();
}

ControlerButtons::~ControlerButtons()
{
}

void ControlerButtons::tick()
{
    // this->_isPressedButton1 = this->_button1->getIsPressedButton();   // 0 == not pressed    // 1 == pressed
    // this->_isPressedButton2 = this->_button2->getIsPressedButton();

    this->_finalStateButton1 = this->_button1->getFinalState(); // 0 == not pressed    // 1 == short press    // 2 == long press    // 3 == double short press
    this->_finalStateButton2 = this->_button2->getFinalState();

    this->_TSProperties->PropertiesButtons._button1State = this->_finalStateButton1;
    this->_TSProperties->PropertiesButtons._button2State = this->_finalStateButton2;

    int controlerState = this->_finalStateButton1 + 4 * this->_finalStateButton2;

    switch (controlerState)
    {
    case 0:
        /* Nothing Happened... */
        Serial.println("No button pressed");
        break;

    case 1:
        /* Change Page Up */
        Serial.println("Button 1 SHORT press");
        this->changePageUp();
        break;

    case 2:
        /* Start/Stop Ride */
        Serial.println("Button 1 LONG press");

        // if (this->_TSProperties->PropertiesCurrentRide._isRideFinished == false)
        // {
            if (this->_TSProperties->PropertiesCurrentRide._isRideStarted)
            {
                this->finishRide();
            }
            else
            {
                this->startRide();
            }
        // }
        break;

    case 3:
        /* Trigger The Buzzer */
        Serial.println("Button 1 DOUBLE SHORT press");
        this->makeNoiseBuzzer();
        break;

    case 4:
        /* Change Page Down */
        Serial.println("Button 2 SHORT press");
        this->changePageDown();
        break;

    case 5:
        /* Activate GoHome Mode */
        Serial.println("Buttons 1 and 2 SHORT press");
        this->goHome();
        break;

    case 8:
        /* Pause/Restart Ride */
        Serial.println("Button 2 LONG press");

        if (this->_TSProperties->PropertiesCurrentRide._isRideStarted)
        {
            if (this->_TSProperties->PropertiesCurrentRide._isRidePaused)
            {
                this->restartRide();
            }
            else
            {
                this->pauseRide();
            }
        }
        break;

    case 10:
        /* Trigger The Buzzer */
        Serial.println("Buttons 1 and 2 LONG press");
        this->makeNoiseBuzzer();
        break;

    case 12:
        /* Trigger The Buzzer */
        Serial.println("Button 2 DOUBLE SHORT press");
        this->makeNoiseBuzzer();
        break;

    default:
        /* Nothing Good Happened... */
        Serial.println("BUTTONS ERROR !!!");
        break;
    }
}

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
void ControlerButtons::changePageUp()
{
    this->_TSProperties->PropertiesScreen._activeScreen = 1;
    this->_TSProperties->PropertiesScreen._isNewActivePage = true;
}

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
void ControlerButtons::changePageDown()
{
    this->_TSProperties->PropertiesScreen._activeScreen = 4;
    this->_TSProperties->PropertiesScreen._isNewActivePage = true;
}

void ControlerButtons::startRide()
{
    if (this->_TSProperties->PropertiesCurrentRide._isRideStarted == false)
    {
        Serial.println("===================== Start Ride =====================");
        this->_TSProperties->PropertiesCurrentRide.resetCurrentRide();
        this->_TSProperties->PropertiesGPS.resetGPSValues();

        this->_TSProperties->PropertiesCurrentRide._isRideStarted = true;
        this->_TSProperties->PropertiesCurrentRide._isRideFinished = false;

        this->_TSProperties->PropertiesCurrentRide._startTimeMS = millis();

        this->_guidGenerator->generate();
        this->_TSProperties->PropertiesCurrentRide._completedRideId = this->_guidGenerator->toCharArray();

        this->_TSProperties->PropertiesScreen._activeScreen = 4;
        this->_TSProperties->PropertiesScreen._isNewActivePage = true;

    }
}

void ControlerButtons::finishRide()
{
    if (this->_TSProperties->PropertiesCurrentRide._isRideStarted)
    {
        this->_TSProperties->PropertiesCurrentRide._isRideFinished = true;
        this->_TSProperties->PropertiesCurrentRide._isRideStarted = false;

        this->_TSProperties->PropertiesCurrentRide._endTimeMS = millis();
        this->_TSProperties->PropertiesCurrentRide._duration = (this->_TSProperties->PropertiesCurrentRide._endTimeMS - this->_TSProperties->PropertiesCurrentRide._startTimeMS) / 60000;

        this->_TSProperties->PropertiesCurrentRide._isRideReadyToSave = true;

        this->_TSProperties->PropertiesScreen._activeScreen = 1;
        this->_TSProperties->PropertiesScreen._isNewActivePage = true;

        this->_TSProperties->PropertiesGPS._TEST_counterTotal = 0;
        this->_TSProperties->PropertiesGPS._TEST_counterGoodValue = 0;
        
        Serial.println("===================== Finish Ride =====================");
    }
}

void ControlerButtons::pauseRide()
{
    if (this->_TSProperties->PropertiesCurrentRide._isRideStarted)
    {
        this->_TSProperties->PropertiesCurrentRide._isRidePaused = true;
    }
}

void ControlerButtons::restartRide()
{
    if (this->_TSProperties->PropertiesCurrentRide._isRideStarted)
    {
        this->_TSProperties->PropertiesCurrentRide._isRidePaused = false;
    }
}

void ControlerButtons::makeNoiseBuzzer()
{
    this->_TSProperties->PropertiesBuzzer._isBuzzerOn = true;
}

void ControlerButtons::goHome()
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
    this->_TSProperties->PropertiesScreen._activeScreen = 6;
}

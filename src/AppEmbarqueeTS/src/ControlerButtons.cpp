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

    this->_TSProperties->PropertiesButtons.Button1State = this->_finalStateButton1;
    this->_TSProperties->PropertiesButtons.Button2State = this->_finalStateButton2;

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

        if (this->_TSProperties->PropertiesCurrentRide.IsRideStarted)
        {
            this->finishRide();
        }
        else
        {
            this->startRide();
        }
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

        if (this->_TSProperties->PropertiesCurrentRide.IsRideStarted)
        {
            if (this->_TSProperties->PropertiesCurrentRide.IsRidePaused)
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
void ControlerButtons::changePageUp()
{
    this->_TSProperties->PropertiesScreen.ActiveScreen++;

    if (this->_TSProperties->PropertiesScreen.ActiveScreen >= NB_ACTIVE_PAGES)
    {
        this->_TSProperties->PropertiesScreen.ActiveScreen = 0;
    }

    // this->_TSProperties->PropertiesScreen.IsNewActivePage = true;
}

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
void ControlerButtons::changePageDown()
{
    this->_TSProperties->PropertiesScreen.ActiveScreen--;

    if (this->_TSProperties->PropertiesScreen.ActiveScreen < 0)
    {
        this->_TSProperties->PropertiesScreen.ActiveScreen = NB_ACTIVE_PAGES - 1;
    }

    // this->_TSProperties->PropertiesScreen.IsNewActivePage = true;
}

void ControlerButtons::startRide()
{
    if (this->_TSProperties->PropertiesCurrentRide.IsRideStarted == false)
    {
        Serial.println("===================== Start Ride =====================");
        this->_TSProperties->PropertiesCurrentRide.resetCurrentRide();
        this->_TSProperties->PropertiesGPS.resetGPSValues();

        this->_TSProperties->PropertiesCurrentRide.IsRideStarted = true;
        this->_TSProperties->PropertiesCurrentRide.IsRideFinished = false;

        this->_TSProperties->PropertiesCurrentRide.StartTimeMS = millis();

        this->_guidGenerator->seed(this->_TSProperties->PropertiesCurrentRide.StartTimeMS);
        this->_guidGenerator->generate();
        this->_TSProperties->PropertiesCurrentRide.CompletedRideId = this->_guidGenerator->toCharArray();

        this->_TSProperties->PropertiesScreen.ActiveScreen = RIDE_PAGE_ID;
        // this->_TSProperties->PropertiesScreen.IsNewActivePage = true;
    }
}

void ControlerButtons::finishRide()
{
    if (this->_TSProperties->PropertiesCurrentRide.IsRideStarted)
    {
        this->_TSProperties->PropertiesCurrentRide.IsRideFinished = true;
        this->_TSProperties->PropertiesCurrentRide.IsRideStarted = false;

        this->_TSProperties->PropertiesCurrentRide.EndTimeMS = millis();
        this->_TSProperties->PropertiesCurrentRide.DurationS = (this->_TSProperties->PropertiesCurrentRide.EndTimeMS - this->_TSProperties->PropertiesCurrentRide.StartTimeMS) / 1000;

        this->_TSProperties->PropertiesCurrentRide.IsRideReadyToSave = true;

        // this->_TSProperties->PropertiesScreen.ActiveScreen = HOME_PAGE_ID;
        this->_TSProperties->PropertiesScreen.ActiveScreen = ENDING_RIDE_PAGE_ID;
        // this->_TSProperties->PropertiesScreen.IsNewActivePage = true;

        this->_TSProperties->PropertiesGPS.CounterTotal = 0;
        this->_TSProperties->PropertiesGPS.CounterGoodValue = 0;

        Serial.println("===================== Finish Ride =====================");
    }
}

void ControlerButtons::pauseRide()
{
    if (this->_TSProperties->PropertiesCurrentRide.IsRideStarted)
    {
        this->_TSProperties->PropertiesCurrentRide.IsRidePaused = true;
    }
}

void ControlerButtons::restartRide()
{
    if (this->_TSProperties->PropertiesCurrentRide.IsRideStarted)
    {
        this->_TSProperties->PropertiesCurrentRide.IsRidePaused = false;
    }
}

void ControlerButtons::makeNoiseBuzzer()
{
    this->_TSProperties->PropertiesBuzzer.IsBuzzerOn = true;
}

void ControlerButtons::goHome()
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
    this->_TSProperties->PropertiesScreen.ActiveScreen = GO_HOME_PAGE_ID;
}

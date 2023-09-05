#include "ControlerButtons.h"

ControlerButtons::ControlerButtons(TrackSenseProperties *trackSenseProperties) : _trackSenseProperties(trackSenseProperties),
                                                                                 _button1(nullptr),
                                                                                 _button2(nullptr),
                                                                                 // _isPressedButton1(false),
                                                                                 // _isPressedButton2(false),
                                                                                 _finalStateButton1(0),
                                                                                 _finalStateButton2(0)
{
    this->_button1 = new ButtonTactile(PIN_BUTTON1);
    this->_button2 = new ButtonTactile(PIN_BUTTON2);
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

    this->_trackSenseProperties->PropertiesButtons._TEST_Button1State = this->_finalStateButton1;
    this->_trackSenseProperties->PropertiesButtons._TEST_Button2State = this->_finalStateButton2;

    if (this->_finalStateButton1 == 0 & this->_finalStateButton2 == 0) // not pressed
    {
        Serial.println("No button pressed");
    }
    else if (this->_finalStateButton1 == 1 & this->_finalStateButton2 == 0) // short press button 1
    {
        /* Change Screen Menu Up */
        Serial.println("Button 1 SHORT press");
        this->changePageUp();
    }
    else if (this->_finalStateButton1 == 0 & this->_finalStateButton2 == 1) // short press button 2
    {
        /* Change Screen Menu Down */
        Serial.println("Button 2 SHORT press");
        this->changePageDown();
    }
    else if (this->_finalStateButton1 == 2 & this->_finalStateButton2 == 0) // long press button 1
    {
        /* Start/Stop Ride */
        Serial.println("Button 1 LONG press");

        if (this->_trackSenseProperties->PropertiesTS._isRideFinished == false)
        {
            if (this->_trackSenseProperties->PropertiesTS._isRideStarted)
            {
                this->finishRide();
            }
            else
            {
                this->startRide();
            }
        }
    }
    else if (this->_finalStateButton1 == 0 & this->_finalStateButton2 == 2) // long press button 2
    {
        /* Pause/Restart Ride */
        Serial.println("Button 2 LONG press");

        if (this->_trackSenseProperties->PropertiesTS._isRideStarted)
        {
            if (this->_trackSenseProperties->PropertiesTS._isRidePaused)
            {
                this->restartRide();
            }
            else
            {
                this->pauseRide();
            }
        }
    }
    else if (this->_finalStateButton1 == 3 & this->_finalStateButton2 == 0) // double short press button 1
    {
        /* Trigger The Buzzer */
        Serial.println("Button 1 DOUBLE SHORT press");
        this->makeNoiseBuzzer();
    }
    else if (this->_finalStateButton1 == 0 & this->_finalStateButton2 == 3) // double short press button 2
    {
        /* Trigger The Buzzer */
        Serial.println("Button 2 DOUBLE SHORT press");
        this->makeNoiseBuzzer();
    }
    else if (this->_finalStateButton1 == 1 & this->_finalStateButton2 == 1) // short press button 1 and 2
    {
        /* Activate GoHome Mode */
        Serial.println("Buttons 1 and 2 SHORT press");
        this->goHome();
    }
    else if (this->_finalStateButton1 == 2 & this->_finalStateButton2 == 2) // long press button 1 and 2
    {
        /* Trigger The Buzzer */
        Serial.println("Buttons 1 and 2 LONG press");
        this->makeNoiseBuzzer();
    }
    else
    {
        /* Nothing Good Happened... */
        Serial.println("BUTTONS ERROR !!!");
    }
}

void ControlerButtons::changePageUp()
{
    // this->_trackSenseProperties->PropertiesScreen.nextPage();
}

void ControlerButtons::changePageDown()
{
}

void ControlerButtons::startRide()
{
    this->_trackSenseProperties->PropertiesTS._isRideStarted = true;
    this->_trackSenseProperties->PropertiesTS._isRideFinished = false;
}

void ControlerButtons::finishRide()
{
    this->_trackSenseProperties->PropertiesTS._isRideFinished = true;
    // this->_trackSenseProperties->PropertiesTS._isRideStarted = false;
}

void ControlerButtons::pauseRide()
{
    this->_trackSenseProperties->PropertiesTS._isRidePaused = true;
}

void ControlerButtons::restartRide()
{
    this->_trackSenseProperties->PropertiesTS._isRidePaused = false;
}

void ControlerButtons::makeNoiseBuzzer()
{
    this->_trackSenseProperties->PropertiesBuzzer._isBuzzerOn = true;
}

void ControlerButtons::goHome()
{
    this->_trackSenseProperties->PropertiesScreen._isHomePage = true;
}

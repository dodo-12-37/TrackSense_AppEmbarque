#include "ControlerButtons.h"



ControlerButtons::ControlerButtons(TrackSenseProperties* trackSenseProperties) : 
    _trackSenseProperties(trackSenseProperties), 
    _button1(nullptr), 
    _button2(nullptr),
    // _isButton1Pressed(false), 
    // _isButton2Pressed(false),
    _stateButton1(0),
    _stateButton2(0) 
{
    this->_button1 = new ButtonTactile(PIN_BUTTON1);
    this->_button2 = new ButtonTactile(PIN_BUTTON2);
}

ControlerButtons::~ControlerButtons()
{
}


void ControlerButtons::tick() 
{
    this->_stateButton1 = this->_button1->getState();   // 0 == not pressed    // 1 == short press    // 2 == long press    // 3 == double short press
    this->_stateButton2 = this->_button2->getState();

    // this->_trackSenseProperties->_TEST_isButton1Pressed = this->_stateButton1;
    // this->_trackSenseProperties->_TEST_isButton2Pressed = this->_stateButton2;

    if (this->_stateButton1 == 0 & this->_stateButton2 == 0)    // not pressed
    {
        Serial.println("No button pressed");
    }
    else if (this->_stateButton1 == 1 & this->_stateButton2 == 0)   // short press button 1
    {
        /* Change Screen Menu Up */
        Serial.println("Button 1 SHORT press");
    }
    else if (this->_stateButton1 == 0 & this->_stateButton2 == 1)   // short press button 2
    {
        /* Change Screen Menu Down */
        Serial.println("Button 2 SHORT press");
    }
    else if (this->_stateButton1 == 2 & this->_stateButton2 == 0)   // long press button 1
    {
        /* Start/Stop Ride */
        Serial.println("Button 1 LONG press");
        this->startRide();
    }
    else if (this->_stateButton1 == 0 & this->_stateButton2 == 2)   // long press button 2
    {
        /* Pause/Restart Ride */
        Serial.println("Button 2 LONG press");

        // this->_trackSenseProperties->PropertiesTS._isRideStarted = false;

        if (this->_trackSenseProperties->PropertiesTS._isRideStarted)
        {
            this->pauseRide();
            
        }
        
        this->restartRide();

    }
    else if (this->_stateButton1 == 3 & this->_stateButton2 == 0)   // double short press button 1
    {
        /* Trigger The Buzzer */
        Serial.println("Button 1 DOUBLE SHORT press");
    }
    else if (this->_stateButton1 == 0 & this->_stateButton2 == 3)   // double short press button 2
    {
        /* Trigger The Buzzer */
        Serial.println("Button 2 DOUBLE SHORT press");
    }
    else if (this->_stateButton1 == 1 & this->_stateButton2 == 1)   // short press button 1 and 2
    {
        /* Activate GoHome Mode */
        Serial.println("Buttons 1 and 2 SHORT press");
    }
    else if (this->_stateButton1 == 2 & this->_stateButton2 == 2)   // long press button 1 and 2
    {
        /* Trigger The Buzzer */
        Serial.println("Buttons 1 and 2 LONG press");
    }
    else
    {
        /* Nothing Good Happened... */
        Serial.println("BUTTONS ERROR !!!");
    }
}

void ControlerButtons::changePage()
{
}

void ControlerButtons::startRide()
{
}

void ControlerButtons::pauseRide()
{
}

void ControlerButtons::finishRide()
{
}

void ControlerButtons::restartRide()
{
}

void ControlerButtons::makeNoiseBuzzer()
{
}






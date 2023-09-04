#include "ControlerButtons.h"



ControlerButtons::ControlerButtons(TrackSenseProperties* trackSenseProperties) : 
    _trackSenseProperties(trackSenseProperties), 
    _button1(nullptr), 
    _button2(nullptr),
    _isPressedButton1(false), 
    _isPressedButton2(false),
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
    this->_isPressedButton1 = this->_button1->getIsPressedButton();   // 0 == not pressed    // 1 == pressed
    this->_isPressedButton2 = this->_button2->getIsPressedButton();

    this->_finalStateButton1 = this->_button1->getFinalState(this->_isPressedButton2);   // 0 == not pressed    // 1 == short press    // 2 == long press    // 3 == double short press
    this->_finalStateButton2 = this->_button2->getFinalState(this->_isPressedButton1);

    // if (this->_isPressedButton1 == true & this->_isPressedButton2 == true)
    // {
    //     this->_finalStateButton1 = 1;
    //     this->_finalStateButton2 = 1;
    // }
    // if (this->_isPressedButton1 == true & this->_isPressedButton2 == false)
    // {
    //     // this->_finalStateButton1 = 1;
    //     this->_finalStateButton2 = 0;
    // }
    // else if (this->_isPressedButton1 == false & this->_isPressedButton2 == true)
    // {
    //     this->_finalStateButton1 = 0;
    //     // this->_finalStateButton2 = 1;
    // }
    // else if (this->_isPressedButton1 == false & this->_isPressedButton2 == false)
    // {
    //     this->_finalStateButton1 = 0;
    //     this->_finalStateButton2 = 0;
    // }
    // else
    // {
    //     this->_finalStateButton1 = 0;
    //     this->_finalStateButton2 = 0;
    // }

    

    this->_trackSenseProperties->PropertiesButtons._TEST_Button1State = this->_finalStateButton1;
    this->_trackSenseProperties->PropertiesButtons._TEST_Button2State = this->_finalStateButton2;

    if (this->_finalStateButton1 == 0 & this->_finalStateButton2 == 0)    // not pressed
    {
        Serial.println("No button pressed");
    }
    else if (this->_finalStateButton1 == 1 & this->_finalStateButton2 == 0 & this->_isPressedButton2 == false)   // short press button 1
    {
        /* Change Screen Menu Up */
        Serial.println("Button 1 SHORT press");
    }
    else if (this->_finalStateButton1 == 0 & this->_finalStateButton2 == 1 & this->_isPressedButton1 == false)   // short press button 2
    {
        /* Change Screen Menu Down */
        Serial.println("Button 2 SHORT press");
    }
    else if (this->_finalStateButton1 == 2 & this->_finalStateButton2 == 0 & this->_isPressedButton2 == false)   // long press button 1
    {
        /* Start/Stop Ride */
        Serial.println("Button 1 LONG press");
        // this->startRide();
    }
    else if (this->_finalStateButton1 == 0 & this->_finalStateButton2 == 2 & this->_isPressedButton1 == false)   // long press button 2
    {
        /* Pause/Restart Ride */
        Serial.println("Button 2 LONG press");

        // this->_trackSenseProperties->PropertiesTS._isRideStarted = false;

        // if (this->_trackSenseProperties->PropertiesTS._isRideStarted)
        // {
        //     this->pauseRide();
            
        // }
        
        // this->restartRide();

    }
    else if (this->_finalStateButton1 == 3 & this->_finalStateButton2 == 0)   // double short press button 1
    {
        /* Trigger The Buzzer */
        Serial.println("Button 1 DOUBLE SHORT press");
    }
    else if (this->_finalStateButton1 == 0 & this->_finalStateButton2 == 3)   // double short press button 2
    {
        /* Trigger The Buzzer */
        Serial.println("Button 2 DOUBLE SHORT press");
    }
    else if (this->_finalStateButton1 == 1 & this->_finalStateButton2 == 1 & this->_isPressedButton1 == false & this->_isPressedButton2 == false)   // short press button 1 and 2
    {
        /* Activate GoHome Mode */
        Serial.println("Buttons 1 and 2 SHORT press");
    }
    else if (this->_finalStateButton1 == 2 & this->_finalStateButton2 == 2 & this->_isPressedButton1 == false & this->_isPressedButton2 == false)   // long press button 1 and 2
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






#include "ControlerButtons.h"



ControlerButtons::ControlerButtons(TrackSenseProperties* trackSenseProperties) : 
    _trackSenseProperties(trackSenseProperties), 
    _isButton1Pressed(false), 
    _isButton2Pressed(false), 
    _button1(nullptr), 
    _button2(nullptr)
{
    // this->_button1 = new ButtonTactile(PIN_BUTTON1, &_trackSenseProperties);
    // this->_button2 = new ButtonTactile(PIN_BUTTON2, &_trackSenseProperties);
    this->_button1 = new ButtonTactile(PIN_BUTTON1);
    this->_button2 = new ButtonTactile(PIN_BUTTON2);
}

ControlerButtons::~ControlerButtons()
{
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

void ControlerButtons::stopRide()
{
}

void ControlerButtons::restartRide()
{
}

void ControlerButtons::makeNoiseBuzzer()
{
}

void ControlerButtons::tick() 
{
    this->_isButton1Pressed = this->_button1->getState();
    this->_isButton2Pressed = this->_button2->getState();

    // this->_trackSenseProperties->_TEST_isButton1Pressed = this->_isButton1Pressed;
    // this->_trackSenseProperties->_TEST_isButton2Pressed = this->_isButton2Pressed;

    if (this->_isButton1Pressed == false & this->_isButton2Pressed == false)
    {
        this->_trackSenseProperties->_TEST_isButton1Pressed = false;
        this->_trackSenseProperties->_TEST_isButton2Pressed = false;
        Serial.println("No button pressed");
    }
    else if (this->_isButton1Pressed == true & this->_isButton2Pressed == false)
    {
        this->_trackSenseProperties->_TEST_isButton1Pressed = true;
        this->_trackSenseProperties->_TEST_isButton2Pressed = false;
        Serial.println("Button 1 pressed");
    }
    else if (this->_isButton1Pressed == false & this->_isButton2Pressed == true)
    {
        this->_trackSenseProperties->_TEST_isButton1Pressed = false;
        this->_trackSenseProperties->_TEST_isButton2Pressed = true;
        Serial.println("Button 2 pressed");
    }
    else if (this->_isButton1Pressed == true & this->_isButton2Pressed == true)
    {
        this->_trackSenseProperties->_TEST_isButton1Pressed = true;
        this->_trackSenseProperties->_TEST_isButton2Pressed = true;
        Serial.println("Buttons 1 and 2 pressed");
    }
    else
    {
        Serial.println("Error");
    }
}




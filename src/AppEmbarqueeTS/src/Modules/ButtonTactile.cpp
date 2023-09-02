#include "Modules/ButtonTactile.h"



// ButtonTactile::ButtonTactile(uint8_t pinButton, TrackSenseProperties& trackSenseProperties) : _pinButton(pinButton), _trackSenseProperties(&trackSenseProperties)
ButtonTactile::ButtonTactile(uint8_t pinButton) : _pinButton(pinButton)
{
    pinMode(this->_pinButton, INPUT);
}

ButtonTactile::~ButtonTactile()
{
}


bool ButtonTactile::getState()
{
    // if (digitalRead(_pinButton) == HIGH)
    // {
    //     if (!_trackSenseProperties->_isButton1Pressed)
    //     {
    //         _trackSenseProperties->_isButton1Pressed = true;
    //         Serial.println("Button pressed");
    //     }
    // }
    // else
    // {
    //     if (_trackSenseProperties->_isButton1Pressed)
    //     {
    //         _trackSenseProperties->_isButton1Pressed = false;
    //         Serial.println("Button released");
    //     }
    // }
    return digitalRead(this->_pinButton) == HIGH;
}
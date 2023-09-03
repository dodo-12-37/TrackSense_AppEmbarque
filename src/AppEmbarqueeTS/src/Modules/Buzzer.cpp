#include "Modules/Buzzer.h"



Buzzer::Buzzer(TrackSenseProperties* trackSenseProperties) : _trackSenseProperties(trackSenseProperties)
{
    pinMode(PIN_BUZZER, OUTPUT);
}

Buzzer::~Buzzer()
{
}

void Buzzer::tick() const
{
    if (this->_trackSenseProperties->_isBuzzerOn)
    {
        tone(PIN_BUZZER, 500, 100);
        this->_trackSenseProperties->_isBuzzerOn = false;
    }
}

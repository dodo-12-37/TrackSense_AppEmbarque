#include "Modules/GPSTinyPlus.h"



GPSTinyPlus::GPSTinyPlus(TrackSenseProperties* trackSenseProperties) : _trackSenseProperties(trackSenseProperties)
{
}

GPSTinyPlus::~GPSTinyPlus()
{
}


// void GPSTinyPlus::test() const
// {
//     Serial.println("GPSTinyPlus::test()");
//     Serial.println("GPSTinyPlus::test() - _trackSenseProperties->_TEST_isButton1Pressed: " + String(_trackSenseProperties->_TEST_isButton1Pressed));
//     Serial.println("GPSTinyPlus::test() - _trackSenseProperties->_TEST_isButton2Pressed: " + String(_trackSenseProperties->_TEST_isButton2Pressed));
// }

void GPSTinyPlus::tick() const
{
    ;
}

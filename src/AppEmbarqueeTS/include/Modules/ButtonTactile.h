#pragma once
#include <Arduino.h>
#include "Interfaces/IButton.h"
#include "Configurations.h"
// #include "TrackSenseProperties.h"



class ButtonTactile : public IButton
{
private:
    // TrackSenseProperties* _trackSenseProperties;
    uint8_t _pinButton;

public:
    // ButtonTactile(int pinButton, TrackSenseProperties& trackSenseProperties);
    ButtonTactile(uint8_t pinButton);
    ~ButtonTactile();

    bool getState() override;    // true == pressed  // false == not pressed
};

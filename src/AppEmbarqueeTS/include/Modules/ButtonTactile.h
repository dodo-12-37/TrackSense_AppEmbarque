#pragma once
#include <Arduino.h>
#include "Interfaces/IButton.h"
#include "Configurations.h"



class ButtonTactile : public IButton
{
private:
    // TrackSenseProperties* _trackSenseProperties;
    uint8_t _pinButton;
    int _lastStateButton;
    long _lastDateChange;
    int _lastStableStateButton;
    uint16_t _durationDebounce;
    int _buttonState;

public:
    ButtonTactile(const uint8_t pinButton);
    ~ButtonTactile();

    int getFinalState() override;    // 0 == not pressed    // 1 == short press    // 2 == long press    // 3 == double short press
    // bool getIsPressedButton() override;    // 0 == not pressed    // 1 == pressed
};

#include "Modules/ButtonTactile.h"

ButtonTactile::ButtonTactile(const uint8_t pinButton) : _pinButton(pinButton),
                                                        _lastStateButton(LOW),
                                                        _lastDateChange(0),
                                                        _lastStableStateButton(LOW),
                                                        _durationDebounce(25)
{
    pinMode(this->_pinButton, INPUT);
}

ButtonTactile::~ButtonTactile()
{
}

int ButtonTactile::getFinalState()
{
    this->_buttonState = digitalRead(this->_pinButton);
    long actualTime = millis();
    int finalState = 0; // 0 == not pressed    // 1 == short press    // 2 == long press    // 3 == double short press

    if (actualTime - this->_lastDateChange > this->_durationDebounce)
    {

        if (this->_lastStableStateButton == HIGH && this->_buttonState == LOW && actualTime - this->_lastDateChange < BUTTON_LONG_PRESS_DURATION_MS)
        {
            finalState = 1; // 1 == short press
        }

        if (this->_lastStableStateButton == HIGH && this->_buttonState == LOW && actualTime - this->_lastDateChange >= BUTTON_LONG_PRESS_DURATION_MS)
        {
            finalState = 2; // 2 == long press
        }

        /* Manque gestion des double pressions longues et courtes ...  */

#if DEBUG_BUTTONS == true
        if (this->_pinButton == 33)
        {
            Serial.println("==================START===================");
            Serial.print("actualTime = ");
            Serial.println(actualTime);
            Serial.print("_lastDateChange = ");
            Serial.println(this->_lastDateChange);
            Serial.print("actualTime - _lastDateChange = ");
            Serial.println(actualTime - this->_lastDateChange);
            Serial.print("ButtonState = ");
            Serial.println(this->_buttonState);
            Serial.print("lastStableStateButton = ");
            Serial.println(this->_lastStableStateButton);
            Serial.print("finalState = ");
            Serial.println(finalState);
            Serial.println("===================END==================");
        }
#endif

        this->_lastStableStateButton = this->_buttonState;
    }

    if (this->_buttonState != this->_lastStateButton)
    {
        this->_lastDateChange = actualTime;
        this->_lastStateButton = this->_buttonState;
    }

    return finalState;
}

// bool ButtonTactile::getIsPressedButton()
// {
//     return this->_buttonState == HIGH;
// }

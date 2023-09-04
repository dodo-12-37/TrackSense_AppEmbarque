#include "Modules/ButtonTactile.h"



ButtonTactile::ButtonTactile(const uint8_t pinButton) : 
    _pinButton(pinButton),
    _lastStateButton(LOW),
    _lastDateChange(0),
    _lastStableStateButton(LOW),
    _durationDebounce(0),
    _timeFirstPress(0)
{
    pinMode(this->_pinButton, INPUT);
}

ButtonTactile::~ButtonTactile()
{
}


int ButtonTactile::getState()
{
    int buttonState = digitalRead(this->_pinButton);
    long actualTime = millis();
    int finalState = 0;     // 0 == not pressed    // 1 == short press    // 2 == long press    // 3 == double short press

    if (buttonState != this->_lastStateButton)
    {
        this->_lastDateChange = actualTime;
        this->_lastStateButton = buttonState;
    }

    if (actualTime - this->_lastDateChange > this->_durationDebounce)
    {
        if (this->_lastStableStateButton == HIGH && buttonState == LOW)
        {
            // Serial.print("Short Pressed Button Pin=");
            // Serial.println(this->_pinButton);
            finalState = 1; // 1 == short press
        }

        if (buttonState == LOW && (actualTime - this->_lastDateChange > BUTTON_LONG_PRESS_DURATION_MS))
        {
            // Serial.print("Long Pressed Button Pin=");
            // Serial.println(this->_pinButton);
            finalState = 2; // 2 == long press
            this->_lastDateChange = actualTime;
        }

        /* Manque gestion des double pressions longues et courtes ...  */

        this->_lastStableStateButton = buttonState;
    }

    Serial.println(finalState);
    return finalState;
}

// int ButtonTactile::getState()
// {
//     int buttonState = digitalRead(this->_pinButton);
//     long actualTime = millis();
//     int finalState = 0;     // 0 == not pressed    // 1 == short press    // 2 == long press    // 3 == double short press

//     if (buttonState != this->_lastStateButton) 
//     {
//         this->_lastDateChange = actualTime;
//         this->_lastStateButton = buttonState;
//     }

//     if(actualTime - this->_lastDateChange > this->_durationDebounce) 
//     {
//         if (_lastStableStateButton == HIGH && buttonState == LOW) 
//         {
//             // _actionPressionCourte->executer();
//             finalState = 1; // 1 == short press
//             // this->_timeFirstPress = millis();
//         } 

//         if((actualTime - this->_lastDateChange > BUTTON_LONG_PRESS_DURATION_MS) && buttonState == LOW)
//         {
//             // _actionPressionLongue->executer();
//             finalState = 2; // 2 == long press
//             this->_lastDateChange = actualTime;
//             // this->_timeFirstPress = 0;
//         }

//         this->_lastStableStateButton = buttonState;
//     }

//     return finalState;
// }
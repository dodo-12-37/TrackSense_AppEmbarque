#include "Modules/ButtonTactile.h"



ButtonTactile::ButtonTactile(uint8_t pinButton) : 
    _pinButton(pinButton),
    _lastStateButton(HIGH),
    _lastDateChange(0),
    _lastStableStateButton(HIGH),
    _minimumPressDuration(25)
{
    pinMode(this->_pinButton, INPUT);
}

ButtonTactile::~ButtonTactile()
{
}


int ButtonTactile::getState()
{
    int etatBouton = digitalRead(this->_pinButton);
    long dateActuelle = millis();
    int finalState = 0;     // 0 == not pressed    // 1 == short press    // 2 == long press    // 3 == double short press

    if (etatBouton != this->_lastStateButton)
    {
        this->_lastDateChange = dateActuelle;
        this->_lastStateButton = etatBouton;
    }
    // else if (etatBouton == HIGH && (dateActuelle - this->_lastDateChange > BUTTON_INACTIVITY_TIME_MS))
    // {
        // this->_actionInactivite->executer();
    // }

    if (dateActuelle - this->_lastDateChange > this->_minimumPressDuration)
    {
        if (this->_lastStableStateButton == HIGH && etatBouton == LOW)
        {
            Serial.println("Short Pressed Button");
            finalState = 1; // 1 == short press
        }

        if (this->_lastStableStateButton == LOW && etatBouton == LOW && (dateActuelle - this->_lastDateChange > BUTTON_LONG_PRESS_DURATION_MS))
        {
            Serial.println("Long Pressed Button");
            finalState = 2; // 2 == long press
            this->_lastDateChange = dateActuelle;
        }

        this->_lastStableStateButton = etatBouton;
    }
}
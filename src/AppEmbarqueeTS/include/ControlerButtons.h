#pragma once
#include <Arduino.h>



class ControlerButtons
{
private:
    /* data */
public:
    ControlerButtons();
    ~ControlerButtons();

    void changePage();
    void startRide();
    void pauseRide();
    void stopRide();
    void restartRide();
    void makeNoiseBuzzer();
};

#pragma once
#include <Arduino.h>
#include "Configurations.h"
#include "TrackSenseProperties.h"
#include "Interfaces/IButton.h"
#include "Modules/ButtonTactile.h"



class ControlerButtons
{
private:
    TrackSenseProperties* _trackSenseProperties;
    IButton* _button1;
    IButton* _button2;

    // bool _isPressedButton1;
    // bool _isPressedButton2;

    int _finalStateButton1;
    int _finalStateButton2;    

public:
    ControlerButtons(TrackSenseProperties* trackSenseProperties);
    ~ControlerButtons();

    void changePage();
    void startRide();
    void pauseRide();
    void finishRide();
    void restartRide();
    void makeNoiseBuzzer();

    void tick();
};

#pragma once
#include <Arduino.h>
#include "Configurations.h"
#include "TrackSenseProperties.h"
#include "Interfaces/IButton.h"
#include "Modules/ButtonTactile.h"
#include <UUID.h>



class ControlerButtons
{
private:
    TrackSenseProperties* _trackSenseProperties;
    IButton* _button1;
    IButton* _button2;

    UUID* _guidGenerator;

    // bool _isPressedButton1;
    // bool _isPressedButton2;

    int _finalStateButton1;
    int _finalStateButton2;    

public:
    ControlerButtons(TrackSenseProperties* trackSenseProperties);
    ~ControlerButtons();

    void changePageUp();
    void changePageDown();
    void startRide();
    void finishRide();
    void pauseRide();
    void restartRide();
    void makeNoiseBuzzer();
    void goHome();

    void tick();
};

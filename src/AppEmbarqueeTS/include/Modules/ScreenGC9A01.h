#pragma once
#include <Arduino.h>
#include "Interfaces/IScreen.h"
#include "Configurations.h"
#include "TrackSenseProperties.h"

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_GC9A01A.h>



class ScreenGC9A01 : IScreen
{
private:
    TrackSenseProperties* _trackSenseProperties;
    Adafruit_GC9A01A* tft;

    void testMaisonScreen();

public:
    ScreenGC9A01(TrackSenseProperties* trackSenseProperties);
    ~ScreenGC9A01();

    void tick() override;

};

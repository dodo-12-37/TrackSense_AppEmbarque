#pragma once
#include <Arduino.h>
#include "Interfaces/IScreen.h"
#include "Configurations.h"
#include "TrackSenseProperties.h"

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_GC9A01A.h>

class ScreenGC9A01 : public IScreen
{
private:
    TrackSenseProperties *_trackSenseProperties;
    Adafruit_GC9A01A *tft;

    void testButtonsScreen();

    /* Pages */
    void drawInitTSPage0();
    void drawHomePage1();
    void drawCompassPage2();
    void drawRideDirectionPage3();
    void drawRidePage4();
    void drawGlobalStatisticsPage5();
    void drawGoHomePage6();
    void drawRideStatisticsPage7();
    void drawErrorPage();

    /* Elements */
    void drawBattery(int16_t coordX, int16_t coordY, int16_t largeurX, int pourcentage);
    // void drawSignal();
    // void drawTime();
    // void drawDate();

    /* Drawing tools */
    void drawBackgroundColor(int darkModeColor = TFT_DARK_MODE_BACKGROUND_COLOR, int lightModeColor = TFT_LIGHT_MODE_BACKGROUND_COLOR);
    void drawBackgroundImage();
    void setTextColor(int textDarkModeColor = TFT_DARK_MODE_TEXT_COLOR,
                      int backgroundDarkModeColor = TFT_DARK_MODE_BACKGROUND_COLOR,
                      int textLightModeColor = TFT_LIGHT_MODE_TEXT_COLOR,
                      int backgroundLightModeColor = TFT_LIGHT_MODE_BACKGROUND_COLOR);

public:
    ScreenGC9A01(TrackSenseProperties *trackSenseProperties);
    ~ScreenGC9A01();

    /*
        0 : Init TS Page
        1 : Home Page
        2 : Compass Page
        3 : Ride Direction Page
        4 : Ride Page
        5 : Global Statistics Page
        6 : Go Home Page
        7 : Ride Statistics Page
        -1 : No Page (error)
    */
    void tick() override;
};

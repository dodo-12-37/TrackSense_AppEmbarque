#pragma once
#include <Arduino.h>
#include "Interfaces/IScreen.h"
#include "Configurations.h"
#include "TSProperties.h"

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_GC9A01A.h>

class ScreenGC9A01 : public IScreen
{
private:
    TSProperties *_TSProperties;
    Adafruit_GC9A01A *tft;

    /* Tests */
    void testButtonsScreen();
    void testGPS();

    /* Pages */
    void drawInitTSPage();
    void drawHomePage();
    void drawCompassPage();
    void drawRideDirectionPage();
    void drawRidePage();
    void drawGlobalStatisticsPage();
    void drawGoHomePage();
    void drawRideStatisticsPage();
    void drawErrorPage();

    /* Elements */
    void drawLogoTS();
    void drawBattery(int16_t coordX, int16_t coordY, int16_t largeurX, int pourcentage);
    // void drawSignal();

    /* Drawing tools */
    int calculateXCoordTextToCenter(String text);
    int calculateXCoordItemToCenter(uint16_t lengthInPixels);
    void drawBackgroundColor(int darkModeColor = TFT_DARK_MODE_BACKGROUND_COLOR, int lightModeColor = TFT_LIGHT_MODE_BACKGROUND_COLOR);
    void drawBackgroundImage();
    void setTextColor(int textDarkModeColor = TFT_DARK_MODE_TEXT_COLOR,
                      int backgroundDarkModeColor = TFT_DARK_MODE_BACKGROUND_COLOR,
                      int textLightModeColor = TFT_LIGHT_MODE_TEXT_COLOR,
                      int backgroundLightModeColor = TFT_LIGHT_MODE_BACKGROUND_COLOR);

public:
    ScreenGC9A01(TSProperties *TSProperties);
    ~ScreenGC9A01();

    /*
        0 : Init TS Page
        1 : Home Page
        2 : Ride Page
        3 : Ride Statistics Page
        4 : Compass Page
        5 : Ride Direction Page
        6 : Global Statistics Page
        7 : Go Home Page
        -1 : No Page (error)
    */
    void tick() override;
};

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
    GFXcanvas16 *canvas;
    int _currentActivePage;
    int _lastActivePage;
    // int _lastLastActivePage;
    // int _counterSamePage;

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
    void drawIsRideStarted(int16_t coordX, int16_t coordY, int16_t largeurX);
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

    void drawRect(int16_t x, int16_t y, int16_t width, int16_t height,
                  uint16_t darkModeColor = TFT_DARK_MODE_TEXT_COLOR,
                  uint16_t lightModeColor = TFT_LIGHT_MODE_TEXT_COLOR);

    void drawFillRect(int16_t x, int16_t y, int16_t width, int16_t height,
                      uint16_t darkModeColor = TFT_DARK_MODE_TEXT_COLOR,
                      uint16_t lightModeColor = TFT_LIGHT_MODE_TEXT_COLOR);

public:
    ScreenGC9A01(TSProperties *TSProperties);
    ~ScreenGC9A01();

    /*
        0 : Home Page
        1 : Ride Page
        2 : Ride Statistics Page
        3 : Compass Page
        4 : Ride Direction Page
        5 : Global Statistics Page
        6 : Go Home Page
        -1 : Init TS Page
        -2 : No Page (error)
    */
    void tick() override;
};

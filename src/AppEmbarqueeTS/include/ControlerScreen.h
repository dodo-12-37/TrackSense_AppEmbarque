#pragma once
#include <Arduino.h>
#include "Interfaces/IControlerScreen.h"
#include "Configurations.h"
#include "TSProperties.h"

#include "Modules/ScreenGC9A01.h"



class ControlerScreen : public IControlerScreen
{
private:
    TSProperties *_TSProperties;
    ScreenGC9A01 *_screen;
    int _currentActivePage;
    int _lastActivePage;
    // int _lastLastActivePage;
    // int _counterSamePage;

    /* Pages */
    void drawInitTSPage() override;
    void drawHomePage() override;
    void drawCompassPage() override;
    void drawRideDirectionPage() override;
    void drawRidePage() override;
    void drawGlobalStatisticsPage() override;
    void drawGoHomePage() override;
    void drawRideStatisticsPage() override;
    void drawErrorPage() override;

    /* Showing modes */
    // void setRotation(u_int8_t rotation) override;
    // void setBackgroudColor(uint16_t darkModeColor = TFT_DARK_MODE_BACKGROUND_COLOR, uint16_t lightModeColor = TFT_LIGHT_MODE_BACKGROUND_COLOR) override;

public:
    ControlerScreen(TSProperties *TSProperties);
    ~ControlerScreen();

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

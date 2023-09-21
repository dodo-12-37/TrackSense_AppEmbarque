#pragma once
#include "TSProperties.h"
#include "Configurations.h"

class IControlerScreen
{
private:
    /*
        Draw Pages
    */
    virtual void drawInitTSPage() = 0;
    virtual void drawHomePage() = 0;
    virtual void drawCompassPage() = 0;
    virtual void drawRideDirectionPage() = 0;
    virtual void drawRidePage() = 0;
    virtual void drawGlobalStatisticsPage() = 0;
    virtual void drawGoHomePage() = 0;
    virtual void drawRideStatisticsPage() = 0;
    virtual void drawErrorPage() = 0;

public:
    virtual void tick() = 0;


    /*
        Showing modes
    */
    // virtual void setRotation(u_int8_t rotation) = 0;
    // virtual void setBackgroudColor(uint16_t darkModeColor, uint16_t lightModeColor) = 0;
};

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

    uint16_t _lastBuffer;
    uint _lastBatteryLevel;

    uint16_t calculateScreenBuffer();
    // int arrondiPourcentageAux5UnitesPres(int pourcentage);

public:
    ScreenGC9A01(TSProperties *TSProperties);
    ~ScreenGC9A01();

    /* Tests */
    void testButtonsScreen() override;
    void testGPS() override;

    /* Elements */
    void drawLogoTS() override;
    void drawBattery(int16_t coordX, int16_t coordY, int16_t largeurX, uint pourcentage) override;
    void drawIsRideStarted(int16_t coordX, int16_t coordY, int16_t largeurX) override;
    void drawError() override;
    void drawIsGPSValid(int16_t coordX, int16_t coordY, int16_t largeurX) override;
    void drawStatistics(String title, String value, String unit, int16_t titleCoordX, int16_t valueCoordX, int16_t unitCoordX, int16_t coordY) override;
    // void drawSignal();

    /* Calculations */
    int calculateXCoordTextToCenter(String text) override;
    int calculateXCoordItemToCenter(uint16_t lengthInPixels) override;

    /* Drawing tools */
    void drawOnScreen() override;
    void drawBackgroundColor(uint16_t darkModeColor = TFT_DARK_MODE_BACKGROUND_COLOR, uint16_t lightModeColor = TFT_LIGHT_MODE_BACKGROUND_COLOR) override;
    // void drawBackgroundImage();
    void setRotation(u_int8_t rotation) override;
    void setFont(uint id) override;
    void printText(String text, int16_t coordX, int16_t coordY) override;
    void setTextSize(uint8_t size) override;
    void setTextWrap(boolean wrap) override;
    void setTextColor(uint16_t textDarkModeColor = TFT_DARK_MODE_TEXT_COLOR,
                      uint16_t backgroundDarkModeColor = TFT_DARK_MODE_BACKGROUND_COLOR,
                      uint16_t textLightModeColor = TFT_LIGHT_MODE_TEXT_COLOR,
                      uint16_t backgroundLightModeColor = TFT_LIGHT_MODE_BACKGROUND_COLOR) override;

    void drawRect(int16_t x, int16_t y, int16_t width, int16_t height,
                  uint16_t darkModeColor = TFT_DARK_MODE_TEXT_COLOR,
                  uint16_t lightModeColor = TFT_LIGHT_MODE_TEXT_COLOR) override;

    void drawFillRect(int16_t x, int16_t y, int16_t width, int16_t height,
                      uint16_t darkModeColor = TFT_DARK_MODE_TEXT_COLOR,
                      uint16_t lightModeColor = TFT_LIGHT_MODE_TEXT_COLOR) override;
};

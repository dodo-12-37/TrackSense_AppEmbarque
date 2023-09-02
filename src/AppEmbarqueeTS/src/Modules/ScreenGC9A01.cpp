#include "Modules/ScreenGC9A01.h"



ScreenGC9A01::ScreenGC9A01(TrackSenseProperties* trackSenseProperties) : _trackSenseProperties(trackSenseProperties)
{
    this->tft = new Adafruit_GC9A01A(TFT_CS_SS, TFT_DC, TFT_SDA_DIN_MOSI, TFT_SCL_CLK_SCK, TFT_RES_RST);
    this->tft->begin();
    this->tft->fillScreen(GC9A01A_BLACK);
    this->tft->setRotation(0);

    // this->tft->setTextColor(GC9A01A_RED, GC9A01A_BLACK);
    // this->tft->setTextSize(3);
    // this->tft->setCursor(20, 140);
    // this->tft->printf("ScreenGC9A01\n");
}

ScreenGC9A01::~ScreenGC9A01()
{
    delete this->tft;
}

void ScreenGC9A01::tick()
{
    this->testMaisonScreen();
}

void ScreenGC9A01::testMaisonScreen()
{
    this->tft->setCursor(10, 100);
    this->tft->setTextSize(2);

    // int isButton1Pressed = digitalRead(PIN_BUTTON1); // 33
    int isButton1Pressed = this->_trackSenseProperties->_TEST_isButton1Pressed;
    int isButton2Pressed = this->_trackSenseProperties->_TEST_isButton2Pressed;

    if (isButton1Pressed == false & isButton2Pressed == false)
    {
        this->tft->setTextColor(GC9A01A_WHITE, GC9A01A_BLACK);   // mettre GC9A01A_BLACK pour le fond
        this->tft->printf("%-27s", "No button pressed !");
        // Serial.println("No button pressed !");
    }
    else if (isButton1Pressed == true & isButton2Pressed == false)
    {
        this->tft->setTextColor(GC9A01A_WHITE, GC9A01A_BLACK);
        this->tft->printf("%-27s", "Button 1 pressed !");
        // Serial.println("Button 1 pressed !");
    }
    else if (isButton1Pressed == false & isButton2Pressed == true)
    {
        this->tft->setTextColor(GC9A01A_WHITE, GC9A01A_BLACK);
        this->tft->printf("%-27s", "Button 2 pressed !");
        // Serial.println("Button 2 pressed !");
    }
    else if (isButton1Pressed == true & isButton2Pressed == true)
    {
        this->tft->setTextColor(GC9A01A_WHITE, GC9A01A_BLACK);
        this->tft->printf("%-27s", "Buttons 1 and 2 pressed !");
        // Serial.println("Buttons 1 and 2 pressed !");
    }
    else
    {
        Serial.println("Error");
    }
}

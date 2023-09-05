#include "Modules/ScreenGC9A01.h"



ScreenGC9A01::ScreenGC9A01(TrackSenseProperties* trackSenseProperties) : _trackSenseProperties(trackSenseProperties)
{
    this->tft = new Adafruit_GC9A01A(TFT_CS_SS, TFT_DC, TFT_SDA_DIN_MOSI, TFT_SCL_CLK_SCK, TFT_RES_RST);
    this->tft->begin();
    this->tft->fillScreen(GC9A01A_BLACK);
    this->tft->setRotation(0);

}

ScreenGC9A01::~ScreenGC9A01()
{
    delete this->tft;
}

void ScreenGC9A01::tick()
{
    this->testMaisonScreen();

    this->tft->setCursor(20, 140);
    this->tft->setTextSize(2);
    this->tft->setTextColor(GC9A01A_WHITE, GC9A01A_BLACK);
    this->tft->printf("%-28s", "Latitude : %f", this->_trackSenseProperties->PropertiesGPS._latitude);

    this->tft->setCursor(20, 160);
    this->tft->setTextSize(2);
    this->tft->setTextColor(GC9A01A_WHITE, GC9A01A_BLACK);
    this->tft->printf("%-28s", "Longitude : %f", this->_trackSenseProperties->PropertiesGPS._longitude);

    this->tft->setCursor(20, 180);
    this->tft->setTextSize(2);
    this->tft->setTextColor(GC9A01A_WHITE, GC9A01A_BLACK);
    this->tft->printf("%-28s", "Altitude : %f", this->_trackSenseProperties->PropertiesGPS._altitude);

    this->tft->setCursor(20, 200);
    this->tft->setTextSize(2);
    this->tft->setTextColor(GC9A01A_WHITE, GC9A01A_BLACK);
    this->tft->printf("%-28s", "Speed : %f", this->_trackSenseProperties->PropertiesGPS._speed);

}

void ScreenGC9A01::testMaisonScreen()
{
    this->tft->setCursor(2, 100);
    this->tft->setTextSize(2);

    // int isButton1Pressed = digitalRead(PIN_BUTTON1); // 33
    int isButton1Pressed = this->_trackSenseProperties->PropertiesButtons._TEST_Button1State;
    int isButton2Pressed = this->_trackSenseProperties->PropertiesButtons._TEST_Button2State;

    if (isButton1Pressed == 0 & isButton2Pressed == 0)    // not pressed
    {
        /* Nothing */
        this->tft->setTextColor(GC9A01A_WHITE, GC9A01A_BLACK);
        this->tft->printf("%-28s", "No button pressed !");
        // Serial.println("No button pressed");
    }
    else if (isButton1Pressed == 1 & isButton2Pressed == 0)   // short press button 1
    {
        /* Change Screen Menu Up */
        this->tft->setTextColor(GC9A01A_WHITE, GC9A01A_BLACK);
        this->tft->printf("%-28s", "Button 1 SHORT press !");
        // Serial.println("Button 1 SHORT press");
    }
    else if (isButton1Pressed == 0 & isButton2Pressed == 1)   // short press button 2
    {
        /* Change Screen Menu Down */
        this->tft->setTextColor(GC9A01A_WHITE, GC9A01A_BLACK);
        this->tft->printf("%-28s", "Button 2 SHORT press !");
        // Serial.println("Button 2 SHORT press");
    }
    else if (isButton1Pressed == 2 & isButton2Pressed == 0)   // long press button 1
    {
        /* Start/Stop Ride */
        this->tft->setTextColor(GC9A01A_WHITE, GC9A01A_BLACK);
        this->tft->printf("%-28s", "Button 1 LONG press !");
        // Serial.println("Button 1 LONG press");
    }
    else if (isButton1Pressed == 0 & isButton2Pressed == 2)   // long press button 2
    {
        /* Pause/Restart Ride */
        this->tft->setTextColor(GC9A01A_WHITE, GC9A01A_BLACK);
        this->tft->printf("%-28s", "Button 2 LONG press !");
        // Serial.println("Button 2 LONG press");
    }
    else if (isButton1Pressed == 3 & isButton2Pressed == 0)   // double short press button 1
    {
        /* Trigger The Buzzer */
        this->tft->setTextColor(GC9A01A_WHITE, GC9A01A_BLACK);
        this->tft->printf("%-28s", "Button 1 DOUBLE SHORT press !");
        // Serial.println("Button 1 DOUBLE SHORT press");
    }
    else if (isButton1Pressed == 0 & isButton2Pressed == 3)   // double short press button 2
    {
        /* Trigger The Buzzer */
        this->tft->setTextColor(GC9A01A_WHITE, GC9A01A_BLACK);
        this->tft->printf("%-28s", "Button 2 DOUBLE SHORT press !");
        // Serial.println("Button 2 DOUBLE SHORT press");
    }
    else if (isButton1Pressed == 1 & isButton2Pressed == 1)   // short press button 1 and 2
    {
        /* Activate GoHome Mode */
        this->tft->setTextColor(GC9A01A_WHITE, GC9A01A_BLACK);
        this->tft->printf("%-28s", "Buttons 1 and 2 SHORT press !");
        // Serial.println("Buttons 1 and 2 SHORT press");
    }
    else if (isButton1Pressed == 2 & isButton2Pressed == 2)   // long press button 1 and 2
    {
        /* Trigger The Buzzer */
        this->tft->setTextColor(GC9A01A_WHITE, GC9A01A_BLACK);
        this->tft->printf("%-28s", "Buttons 1 and 2 LONG press !");
        // Serial.println("Buttons 1 and 2 LONG press");
    }
    else
    {
        /* Nothing Good Happened... */
        this->tft->setTextColor(GC9A01A_WHITE, GC9A01A_BLACK);
        this->tft->printf("%-28s", "BUTTONS ERROR !!!");
        // Serial.println("BUTTONS ERROR !!!");
    }
}

#include "Modules/ScreenGC9A01.h"

ScreenGC9A01::ScreenGC9A01(TrackSenseProperties *trackSenseProperties) : _trackSenseProperties(trackSenseProperties)
{
    this->tft = new Adafruit_GC9A01A(TFT_CS_SS, TFT_DC, TFT_SDA_DIN_MOSI, TFT_SCL_CLK_SCK, TFT_RES_RST);
    this->tft->begin();
    this->tft->setRotation(this->_trackSenseProperties->PropertiesScreen._screenRotation);
    this->drawBackgroundColor();
}

ScreenGC9A01::~ScreenGC9A01()
{
    delete this->tft;
}

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
void ScreenGC9A01::tick()
{
    if (this->_trackSenseProperties->PropertiesTS._isInitializedGSM)
    {
        this->_trackSenseProperties->PropertiesScreen._activeScreen = -1;
        this->_trackSenseProperties->PropertiesScreen._isNewActivePage = false;
    }

    this->tft->setRotation(this->_trackSenseProperties->PropertiesScreen._screenRotation);

    if (this->_trackSenseProperties->PropertiesScreen._isNewActivePage)
    {
        this->drawBackgroundColor();
        this->_trackSenseProperties->PropertiesScreen._isNewActivePage = false;
    }

    switch (this->_trackSenseProperties->PropertiesScreen._activeScreen)
    {
    case 0:
        this->drawInitTSPage0();
        break;

    case 1:
        this->drawHomePage1();
        break;

    case 2:
        this->drawCompassPage2();
        break;

    case 3:
        this->drawRideDirectionPage3();
        break;

    case 4:
        if (this->_trackSenseProperties->PropertiesCurrentRide._isRideStarted)
        {
            this->drawRidePage4();
        }
        else
        {
            this->_trackSenseProperties->PropertiesScreen._activeScreen = -1;
            this->_trackSenseProperties->PropertiesBuzzer._isBuzzerOn = true; ////////////////////////////
        }
        break;

    case 5:
        this->drawGlobalStatisticsPage5();
        break;

    case 6:
        this->drawGoHomePage6();
        break;

    case 7:
        this->drawRideStatisticsPage7();
        break;

    default:
        this->drawErrorPage();
        break;
    }
}

/*
    Draw Pages
*/
#pragma region DrawPages

void ScreenGC9A01::drawInitTSPage0()
{
    /*
        @brief    Helper to determine size of a PROGMEM string with current
    font/size. Pass string and a cursor position, returns UL corner and W,H.
        @param    str     The flash-memory ascii string to measure
        @param    x       The current cursor X
        @param    y       The current cursor Y
        @param    x1      The boundary X coordinate, set by function
        @param    y1      The boundary Y coordinate, set by function
        @param    w      The boundary width, set by function
        @param    h      The boundary height, set by function
    */
    // this->tft->getTextBounds("Initializing", 10, 150); // Pour centrer le texte ???
    this->setTextColor();
    this->tft->setTextSize(3);
    this->tft->setCursor(10, 90);
    this->tft->printf("%-13s", "Initializing");
    this->tft->setCursor(30, 120);
    this->tft->printf("%-11s", "TrackSense");
}

void ScreenGC9A01::drawHomePage1()
{
    this->setTextColor();
    this->tft->setTextSize(3);
    this->tft->setCursor(35, 50);
    this->tft->printf("%-10s", "Home Page");

    this->drawBattery(70, 140, 100, this->_trackSenseProperties->PropertiesBattery._batteryLevel);

    this->testButtonsScreen();
}

void ScreenGC9A01::drawCompassPage2()
{
    ;
}

void ScreenGC9A01::drawRideDirectionPage3()
{
    ;
}

void ScreenGC9A01::drawRidePage4()
{
    char *formatChar = (char *)"%-19s";
    bool locationIsValid = false;

    if (this->_trackSenseProperties->PropertiesCurrentRide._latitude != 0 && this->_trackSenseProperties->PropertiesCurrentRide._longitude != 0)
    {
        locationIsValid = true;
    }

    if (locationIsValid && this->_trackSenseProperties->PropertiesCurrentRide._usedSatellites >= 4)
    {
        this->setTextColor(GC9A01A_GREEN, GC9A01A_BLACK, GC9A01A_DARKGREEN, GC9A01A_WHITE);
    }
    else if (locationIsValid && this->_trackSenseProperties->PropertiesCurrentRide._usedSatellites < 4)
    {
        this->setTextColor(GC9A01A_CYAN, GC9A01A_BLACK, GC9A01A_DARKCYAN, GC9A01A_WHITE);
    }
    else
    {
        this->setTextColor(GC9A01A_RED, GC9A01A_BLACK, GC9A01A_RED, GC9A01A_WHITE);
    }

    tft->setTextSize(2);

    tft->setCursor(40, 40);
    String strCounterGoodValue = "Good : " + String(this->_trackSenseProperties->PropertiesCurrentRide._TEST_counterGoodValue);
    tft->printf("%-15s", strCounterGoodValue.c_str());

    tft->setCursor(30, 60);
    String strCounterTotal = "Total : " + String(this->_trackSenseProperties->PropertiesCurrentRide._TEST_counterTotal);
    tft->printf("%-11s", strCounterTotal.c_str());

    tft->setCursor(15, 85);
    String strUsedSatellite = "Used Sat : " + String(this->_trackSenseProperties->PropertiesCurrentRide._usedSatellites);
    tft->printf(formatChar, strUsedSatellite.c_str());

    tft->setCursor(2, 110);
    String strLatitude = "Lat : " + String(this->_trackSenseProperties->PropertiesCurrentRide._latitude, 10);
    tft->printf(formatChar, strLatitude.c_str());

    tft->setCursor(2, 130);
    String strLongitude = "Lon : " + String(this->_trackSenseProperties->PropertiesCurrentRide._longitude, 10);
    tft->printf(formatChar, strLongitude.c_str());

    tft->setCursor(12, 150);
    String strAltitude = "Alt : " + String(this->_trackSenseProperties->PropertiesCurrentRide._altitude, 8);
    tft->printf(formatChar, strAltitude.c_str());

    tft->setCursor(20, 170);
    String strSpeed = "Speed : " + String(this->_trackSenseProperties->PropertiesCurrentRide._speed, 4);
    tft->printf(formatChar, strSpeed.c_str());

    tft->setCursor(40, 190);
    String strAccuracy = "Accu : " + String(this->_trackSenseProperties->PropertiesCurrentRide._accuracy, 4);
    tft->printf(formatChar, strAccuracy.c_str());

    this->drawBattery(100, 5, 50, this->_trackSenseProperties->PropertiesBattery._batteryLevel);
}

void ScreenGC9A01::drawGlobalStatisticsPage5()
{
    ;
}

void ScreenGC9A01::drawGoHomePage6()
{
    ;
}

void ScreenGC9A01::drawRideStatisticsPage7()
{
    ;
}

void ScreenGC9A01::drawErrorPage()
{
    this->tft->fillScreen(GC9A01A_RED);
    this->setTextColor(GC9A01A_BLACK, GC9A01A_RED, GC9A01A_WHITE, GC9A01A_RED);
    this->tft->setTextSize(5);
    this->tft->setCursor(15, 110);
    this->tft->printf("%-8s", "ERROR !");
}

#pragma endregion DrawPages

/*
    Elements
*/
#pragma region Elements

void ScreenGC9A01::drawBattery(int16_t coordX, int16_t coordY, int16_t largeurX, int pourcentage)
{
    double hauteurY = largeurX / 2;
    double zoneBarreVerteX = largeurX * 0.875;
    double barreVerteX = zoneBarreVerteX / 3;
    double barreVerteY = hauteurY * 0.8;
    double coordBarreVerteX = coordX + (barreVerteX - barreVerteX * 0.875);
    double coordBarreVerteY = coordY + (hauteurY - barreVerteY) / 2;

    // tft.drawRect(coordX, coordY, largeurX, hauteurY, GC9A01A_RED);  // Contour
    tft->drawRect(coordX, coordY, zoneBarreVerteX, hauteurY, GC9A01A_WHITE);                                   // Contour
    tft->fillRect(coordX + zoneBarreVerteX, coordY + hauteurY / 4, hauteurY / 4, hauteurY / 2, GC9A01A_WHITE); // ti boute        + hauteurY / 2 - 16/2

    switch (pourcentage)
    {
    case 0 ... 20:
        tft->fillRect((coordBarreVerteX), coordBarreVerteY, (barreVerteX * 0.8125), barreVerteY, GC9A01A_RED); // niveau #1
        break;

    case 21 ... 40:
        tft->fillRect((coordBarreVerteX), coordBarreVerteY, (barreVerteX * 0.8125), barreVerteY, GC9A01A_YELLOW); // niveau #1
        break;

    case 41 ... 60:
        tft->fillRect((coordBarreVerteX), coordBarreVerteY, (barreVerteX * 0.8125), barreVerteY, GC9A01A_GREEN);               // niveau #1
        tft->fillRect((coordBarreVerteX + barreVerteX), coordBarreVerteY, (barreVerteX * 0.8125), barreVerteY, GC9A01A_GREEN); // niveau #2
        break;

    case 61 ... 80:
        tft->fillRect((coordBarreVerteX), coordBarreVerteY, (barreVerteX * 0.8125), barreVerteY, GC9A01A_GREEN);               // niveau #1
        tft->fillRect((coordBarreVerteX + barreVerteX), coordBarreVerteY, (barreVerteX * 0.8125), barreVerteY, GC9A01A_GREEN); // niveau #2
        break;

    case 81 ... 100:
        tft->fillRect((coordBarreVerteX), coordBarreVerteY, (barreVerteX * 0.8125), barreVerteY, GC9A01A_GREEN);                   // niveau #1
        tft->fillRect((coordBarreVerteX + barreVerteX), coordBarreVerteY, (barreVerteX * 0.8125), barreVerteY, GC9A01A_GREEN);     // niveau #2
        tft->fillRect((coordBarreVerteX + barreVerteX * 2), coordBarreVerteY, (barreVerteX * 0.8125), barreVerteY, GC9A01A_GREEN); // niveau #3
        break;

    default:
        break;
    }

    if (largeurX < 100)
    {
        tft->setTextSize(1);
    }
    else if (largeurX < 200)
    {
        tft->setTextSize(2);
    }
    else
    {
        tft->setTextSize(3);
    }
    

    // this->setTextColor(GC9A01A_BLACK, GC9A01A_WHITE, GC9A01A_WHITE, GC9A01A_BLACK);
    this->setTextColor();
    tft->setCursor((coordBarreVerteX + (barreVerteX)), coordBarreVerteY + hauteurY / 3);
    String strBatteryLevel = String(this->_trackSenseProperties->PropertiesBattery._batteryLevel, 0) + "%";
    tft->printf("%-3s", strBatteryLevel.c_str());
}

#pragma endregion Elements

/*
    Drawing Tools
*/
#pragma region DrawingTools

void ScreenGC9A01::drawBackgroundColor(int darkModeColor, int lightModeColor)
{
    if (this->_trackSenseProperties->PropertiesScreen._isDarkMode)
    {
        this->tft->fillScreen(darkModeColor);
    }
    else
    {
        this->tft->fillScreen(lightModeColor);
    }
}

void ScreenGC9A01::setTextColor(int textDarkModeColor,
                                int backgroundDarkModeColor,
                                int textLightModeColor,
                                int backgroundLightModeColor)
{
    if (this->_trackSenseProperties->PropertiesScreen._isDarkMode)
    {
        this->tft->setTextColor(textDarkModeColor, backgroundDarkModeColor);
    }
    else
    {
        this->tft->setTextColor(textLightModeColor, backgroundLightModeColor);
    }
}

#pragma endregion DrawingTools

/*
    Test maison
*/
#pragma region TestMaison

void ScreenGC9A01::testButtonsScreen()
{
    char *formatChar = (char *)"%-29s";

    this->tft->setCursor(2, 100);
    this->tft->setTextSize(2);
    this->setTextColor();

    // int isButton1Pressed = digitalRead(PIN_BUTTON1); // 33
    int isButton1Pressed = this->_trackSenseProperties->PropertiesButtons._button1State;
    int isButton2Pressed = this->_trackSenseProperties->PropertiesButtons._button2State;

    if (isButton1Pressed == 0 & isButton2Pressed == 0) // not pressed
    {
        /* Nothing */
        this->tft->printf(formatChar, "No button pressed !");
        // Serial.println("No button pressed");
    }
    else if (isButton1Pressed == 1 & isButton2Pressed == 0) // short press button 1
    {
        /* Change Screen Menu Up */
        this->tft->printf(formatChar, "Button 1 SHORT press !");
        // Serial.println("Button 1 SHORT press");
    }
    else if (isButton1Pressed == 0 & isButton2Pressed == 1) // short press button 2
    {
        /* Change Screen Menu Down */
        this->tft->printf(formatChar, "Button 2 SHORT press !");
        // Serial.println("Button 2 SHORT press");
    }
    else if (isButton1Pressed == 2 & isButton2Pressed == 0) // long press button 1
    {
        /* Start/Stop Ride */
        this->tft->printf(formatChar, "Button 1 LONG press !");
        // Serial.println("Button 1 LONG press");
    }
    else if (isButton1Pressed == 0 & isButton2Pressed == 2) // long press button 2
    {
        /* Pause/Restart Ride */
        this->tft->printf(formatChar, "Button 2 LONG press !");
        // Serial.println("Button 2 LONG press");
    }
    else if (isButton1Pressed == 3 & isButton2Pressed == 0) // double short press button 1
    {
        /* Trigger The Buzzer */
        this->tft->printf(formatChar, "Button 1 DOUBLE SHORT press !");
        // Serial.println("Button 1 DOUBLE SHORT press");
    }
    else if (isButton1Pressed == 0 & isButton2Pressed == 3) // double short press button 2
    {
        /* Trigger The Buzzer */
        this->tft->printf(formatChar, "Button 2 DOUBLE SHORT press !");
        // Serial.println("Button 2 DOUBLE SHORT press");
    }
    else if (isButton1Pressed == 1 & isButton2Pressed == 1) // short press button 1 and 2
    {
        /* Activate GoHome Mode */
        this->tft->printf(formatChar, "Buttons 1 and 2 SHORT press !");
        // Serial.println("Buttons 1 and 2 SHORT press");
    }
    else if (isButton1Pressed == 2 & isButton2Pressed == 2) // long press button 1 and 2
    {
        /* Trigger The Buzzer */
        this->tft->printf(formatChar, "Buttons 1 and 2 LONG press !");
        // Serial.println("Buttons 1 and 2 LONG press");
    }
    else
    {
        /* Nothing Good Happened... */
        this->tft->printf(formatChar, "BUTTONS ERROR !!!");
        // Serial.println("BUTTONS ERROR !!!");
    }
}

#pragma endregion TestMaison
#include "Modules/ScreenGC9A01.h"

ScreenGC9A01::ScreenGC9A01(TSProperties *TSProperties) : _TSProperties(TSProperties)
{
    this->tft = new Adafruit_GC9A01A(TFT_CS_SS, TFT_DC, TFT_SDA_DIN_MOSI, TFT_SCL_CLK_SCK, TFT_RES_RST);
    this->tft->begin();
    this->tft->setRotation(this->_TSProperties->PropertiesScreen.ScreenRotation);
    this->drawBackgroundColor();
}

ScreenGC9A01::~ScreenGC9A01()
{
    delete this->tft;
}

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
void ScreenGC9A01::tick()
{
    this->_currentActivePage = this->_TSProperties->PropertiesScreen.ActiveScreen;

    // this->_TSProperties->PropertiesScreen.IsNewActivePage = !(this->_currentActivePage == this->_lastActivePage);
    if (this->_lastActivePage == this->_lastLastActivePage)
    {
        this->_counterSamePage++;
    }
    else
    {
        this->_counterSamePage = 0;
    }
    
    

    if (this->_currentActivePage == this->_lastActivePage)
    {
        this->_TSProperties->PropertiesScreen.IsNewActivePage = false;
        // this->_counterSamePage++;
    }
    else
    {
        this->_TSProperties->PropertiesScreen.IsNewActivePage = true;
        // this->_counterSamePage = 0;
    }

    if (!this->_TSProperties->PropertiesTS.IsInitializedGSM)
    {
        this->_TSProperties->PropertiesScreen.ActiveScreen = ERROR_PAGE_ID;
        // this->_TSProperties->PropertiesScreen.IsNewActivePage = false;
    }

    this->tft->setRotation(this->_TSProperties->PropertiesScreen.ScreenRotation);

    if (this->_TSProperties->PropertiesScreen.IsNewActivePage)
    {
        this->drawBackgroundColor();
        // this->_TSProperties->PropertiesScreen.IsNewActivePage = false;
    }

    switch (this->_TSProperties->PropertiesScreen.ActiveScreen)
    {
    case INIT_TS_PAGE_ID: // 0
        this->drawInitTSPage();
        break;

    case HOME_PAGE_ID: // 1
        this->drawHomePage();
        break;

    case RIDE_PAGE_ID: // 2
        if (this->_TSProperties->PropertiesCurrentRide.IsRideStarted)
        {
            this->drawRidePage();
        }
        else
        {
            this->_TSProperties->PropertiesScreen.ActiveScreen = HOME_PAGE_ID;
            // this->_TSProperties->PropertiesScreen.IsNewActivePage = true;
        }
        break;

    case RIDE_STATISTICS_PAGE_ID: // 3
        if (this->_TSProperties->PropertiesCurrentRide.IsRideStarted)
        {
            this->drawRideStatisticsPage();
        }
        else
        {
            this->_TSProperties->PropertiesScreen.ActiveScreen = HOME_PAGE_ID;
            // this->_TSProperties->PropertiesScreen.IsNewActivePage = true;
        }
        break;

    case COMPASS_PAGE_ID: // 4
        this->drawCompassPage();
        break;

    case RIDE_DIRECTION_PAGE_ID: // 5
        this->drawRideDirectionPage();
        break;

    case GLOBAL_STATISTICS_PAGE_ID: // 6
        this->drawGlobalStatisticsPage();
        break;

    case GO_HOME_PAGE_ID: // 7
        this->drawGoHomePage();
        break;

    default:                   // -1
        this->drawErrorPage(); // TODO : Enlever l'affichage de la page d'erreur pour la production
        break;
    }

    // this->_TSProperties->PropertiesScreen.IsNewActivePage = false;
    this->_lastLastActivePage = this->_lastActivePage;
    this->_lastActivePage = this->_currentActivePage;
}

/*


    Draw Pages


*/
#pragma region DrawPages

void ScreenGC9A01::drawInitTSPage()
{
    // this->setTextColor();
    // this->tft->setTextSize(3);
    // this->tft->setCursor(10, 90);
    // this->tft->printf("%-13s", "Initializing");
    // this->tft->setCursor(30, 120);
    // this->tft->printf("%-11s", "TrackSense");

    this->drawLogoTS();
}

void ScreenGC9A01::drawHomePage()
{
#if DEBUG_BUTTONS
    this->setTextColor();
    this->tft->setTextSize(3);
    this->tft->setCursor(35, 50);
    this->tft->printf("%-10s", "Home Page");

    this->drawBattery(70, 140, 100, this->_TSProperties->PropertiesBattery.BatteryLevel);
    this->testButtonsScreen();
#else
    this->drawLogoTS();

    int batteryLengthInPixels = 70;
    this->drawBattery(this->calculateXCoordItemToCenter(batteryLengthInPixels),
                      20,
                      batteryLengthInPixels,
                      this->_TSProperties->PropertiesBattery.BatteryLevel);

    int rideStartedLengthInPixels = 40;
    this->drawIsRideStarted(this->calculateXCoordItemToCenter(rideStartedLengthInPixels), 185, rideStartedLengthInPixels);
#endif
}

void ScreenGC9A01::drawCompassPage()
{
    ;
}

void ScreenGC9A01::drawRideDirectionPage()
{
    ;
}

void ScreenGC9A01::drawRidePage()
{
#if DEBUG_GSM
    this->testGPS();
#else
    this->setTextColor();
    this->tft->setTextSize(3);
    this->tft->setCursor(35, 50);
    this->tft->printf("%-10s", "Ride Page");

    this->drawBattery(70, 140, 70, this->_TSProperties->PropertiesBattery.BatteryLevel);
#endif
}

void ScreenGC9A01::drawGlobalStatisticsPage()
{
    ;
}

void ScreenGC9A01::drawGoHomePage()
{
    ;
}

void ScreenGC9A01::drawRideStatisticsPage()
{
    int batteryLengthInPixels = 150;
    this->drawBattery(this->calculateXCoordItemToCenter(batteryLengthInPixels),
                      100,
                      batteryLengthInPixels,
                      this->_TSProperties->PropertiesBattery.BatteryLevel);
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

void ScreenGC9A01::drawLogoTS() // TODO : Ajouter des fonctions pour dessiner le logo TS en Light Mode : this->drawfillCircle()
{
    int16_t coordX = 17; // "T" coordX = 16
    int16_t coordY = 65; // "T" coordX = 65

    tft->setTextSize(7);

    uint16_t width = 42;  // "T" width = 42
    uint16_t height = 56; // "T" height = 56

    tft->getTextBounds("T", coordX, coordY, &coordX, &coordY, &width, &height);

    int widthWithoutSpace = width * 0.80952381; // widthWithoutSpace = 42 * 0.80952381 = 34
    int heightWithoutSpace = height * 0.875;    // heightWithoutSpace = 56 * 0.875 = 49

    int coordY2 = coordY + height + 1; // "premier E" coordX = 122     // 65 + 56 = 121

    // Draw "TRA"
    this->setTextColor();
    tft->setCursor(coordX, coordY);
    tft->printf("%-3s", "TRA");
    // Draw "C" of "TRACK"
    this->setTextColor(GC9A01A_RED, GC9A01A_BLACK, GC9A01A_RED, GC9A01A_WHITE);
    tft->setCursor(coordX + width * 3, coordY);
    tft->printf("%-1s", "C");
    // Draw "K" of "TRACK"
    this->setTextColor();
    tft->setCursor(coordX + width * 4, coordY);
    tft->printf("%-1s", "K");

    // Draw special "S"
    tft->fillCircle(coordX + width * 0.761904762, coordY2 + height * 0.160714286, 4, GC9A01A_RED);
    tft->fillCircle(coordX + width * 0.547619048, coordY2 + height * 0.053571429, 4, GC9A01A_WHITE);
    tft->fillCircle(coordX + width * 0.285714286, coordY2 + height * 0.089285714, 4, GC9A01A_WHITE);
    tft->fillCircle(coordX + width * 0.142857143, coordY2 + height * 0.250000000, 4, GC9A01A_WHITE);
    tft->fillCircle(coordX + width * 0.309523810, coordY2 + height * 0.392857143, 4, GC9A01A_WHITE);
    tft->fillCircle(coordX + width * 0.523809524, coordY2 + height * 0.500000000, 4, GC9A01A_WHITE);
    tft->fillCircle(coordX + width * 0.714285714, coordY2 + height * 0.642857143, 4, GC9A01A_WHITE);
    tft->fillCircle(coordX + width * 0.547619048, coordY2 + height * 0.803571429, 4, GC9A01A_WHITE);
    tft->fillCircle(coordX + width * 0.285714286, coordY2 + height * 0.839285714, 4, GC9A01A_WHITE);
    tft->fillCircle(coordX + width * 0.095238095, coordY2 + height * 0.714285714, 4, GC9A01A_RED);

    // Draw "ENSE"
    this->setTextColor();
    tft->setCursor(coordX + width, coordY2);
    tft->printf("%-4s", "ENSE");

    // Draw circle
    // Comme le nombre de pixel est pair (240), le centre est entre 2 pixels. On ne peut pas mettre de fraction de pixel... Donc pour avoir un cercle centré, il faut dessiner 4 cercles...
    tft->drawCircle(119, 119, 120, GC9A01A_WHITE); // Center X = 119.5 (0 to 239)    // Center Y = 119.5 (0 to 239)    // rayon = 120
    tft->drawCircle(120, 120, 120, GC9A01A_WHITE); // Center X = 119.5 (0 to 239)    // Center Y = 119.5 (0 to 239)    // rayon = 120
    tft->drawCircle(119, 120, 120, GC9A01A_WHITE); // Center X = 119.5 (0 to 239)    // Center Y = 119.5 (0 to 239)    // rayon = 120
    tft->drawCircle(120, 119, 120, GC9A01A_WHITE); // Center X = 119.5 (0 to 239)    // Center Y = 119.5 (0 to 239)    // rayon = 120
}

void ScreenGC9A01::drawBattery(int16_t coordX, int16_t coordY, int16_t largeurX, int pourcentage)
{
    double hauteurY = largeurX / 2;
    double zoneBarreVerteX = largeurX * 0.875;
    double barreVerteX = zoneBarreVerteX * 0.9;
    double barreVerteY = hauteurY * 0.8;
    double coordBarreVerteX = coordX + (zoneBarreVerteX - barreVerteX) / 2;
    double coordBarreVerteY = coordY + (hauteurY - barreVerteY) / 2;

    this->drawRect(coordX, coordY, zoneBarreVerteX, hauteurY);                                       // Contour
    this->drawFillRect(coordX + zoneBarreVerteX, coordY + hauteurY / 4, hauteurY / 4, hauteurY / 2); // ti boute        + hauteurY / 2 - 16/2

    switch (pourcentage)
    {
    case 0 ... 20:
        tft->fillRect(coordBarreVerteX, coordBarreVerteY, (barreVerteX * pourcentage / 100), barreVerteY, GC9A01A_RED); // niveau #1
        break;

    case 21 ... 40:
        tft->fillRect(coordBarreVerteX, coordBarreVerteY, (barreVerteX * pourcentage / 100), barreVerteY, GC9A01A_YELLOW); // niveau #1
        break;

    case 41 ... 100:
        tft->fillRect(coordBarreVerteX, coordBarreVerteY, (barreVerteX * pourcentage / 100), barreVerteY, GC9A01A_GREEN); // niveau #1
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

    tft->setCursor((coordX + largeurX) * 1.05, coordBarreVerteY + hauteurY / 4);
    this->setTextColor();
    const String strBatteryLevel = String(this->_TSProperties->PropertiesBattery.BatteryLevel, 0) + "%";
    tft->printf("%-3s", strBatteryLevel.c_str());
}

void ScreenGC9A01::drawIsRideStarted(int16_t coordX, int16_t coordY, int16_t largeurX)
{
    double hauteurY = largeurX;

    if (this->_TSProperties->PropertiesCurrentRide.IsRideStarted)
    {
        // if (this->_currentActivePage == this->_lastActivePage && this->_lastActivePage == this->_lastLastActivePage)
        // if (this->_currentActivePage == this->_lastLastActivePage)
        if (this->_counterSamePage == 1)
        {
            this->tft->fillRect(coordX -5, coordY - 5, largeurX + 10, hauteurY + 10, GC9A01A_BLACK);
        }
        this->tft->fillTriangle(coordX, coordY, coordX + largeurX, coordY + hauteurY / 2, coordX, coordY + hauteurY, GC9A01A_GREEN);
    }
    else
    {
        // if (this->_currentActivePage == this->_lastLastActivePage)
        if (this->_counterSamePage == 1)
        {
            this->tft->fillRect(coordX -5, coordY - 5, largeurX + 10, hauteurY + 10, GC9A01A_BLACK);
        }
        this->tft->fillRect(coordX, coordY, largeurX, hauteurY, GC9A01A_RED);
    }
}

#pragma endregion Elements

/*


    Drawing Tools


*/
#pragma region DrawingTools

int ScreenGC9A01::calculateXCoordTextToCenter(String text)
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
    uint16_t textWidth, textHeight;

    this->tft->getTextBounds(text, 10, 10, 0, 0, &textWidth, &textHeight);

    return (TFT_WIDTH - textWidth) / 2;
}

int ScreenGC9A01::calculateXCoordItemToCenter(uint16_t lengthInPixels)
{
    return (TFT_WIDTH - lengthInPixels) / 2;
}

void ScreenGC9A01::drawBackgroundColor(int darkModeColor, int lightModeColor)
{
    if (this->_TSProperties->PropertiesScreen.IsDarkMode)
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
    if (this->_TSProperties->PropertiesScreen.IsDarkMode)
    {
        this->tft->setTextColor(textDarkModeColor, backgroundDarkModeColor);
    }
    else
    {
        this->tft->setTextColor(textLightModeColor, backgroundLightModeColor);
    }
}

void ScreenGC9A01::drawRect(int16_t x, int16_t y, int16_t width, int16_t height,
                            uint16_t darkModeColor,
                            uint16_t lightModeColor)
{
    if (this->_TSProperties->PropertiesScreen.IsDarkMode)
    {
        this->tft->drawRect(x, y, width, height, darkModeColor);
    }
    else
    {
        this->tft->drawRect(x, y, width, height, lightModeColor);
    }
}

void ScreenGC9A01::drawFillRect(int16_t x, int16_t y, int16_t width, int16_t height,
                                uint16_t darkModeColor,
                                uint16_t lightModeColor)
{
    if (this->_TSProperties->PropertiesScreen.IsDarkMode)
    {
        this->tft->fillRect(x, y, width, height, darkModeColor);
    }
    else
    {
        this->tft->fillRect(x, y, width, height, lightModeColor);
    }
}

#pragma endregion DrawingTools

/*


    Tests


*/
#pragma region Tests

void ScreenGC9A01::testGPS()
{
    char *formatChar = (char *)"%-19s";

    if (this->_TSProperties->PropertiesGPS.IsValid && this->_TSProperties->PropertiesGPS.UsedSatellites >= 4)
    {
        this->setTextColor(GC9A01A_GREEN, GC9A01A_BLACK, GC9A01A_DARKGREEN, GC9A01A_WHITE);
    }
    else if (this->_TSProperties->PropertiesGPS.IsValid && this->_TSProperties->PropertiesGPS.UsedSatellites < 4)
    {
        this->setTextColor(GC9A01A_CYAN, GC9A01A_BLACK, GC9A01A_DARKCYAN, GC9A01A_WHITE);
    }
    else
    {
        this->setTextColor(GC9A01A_RED, GC9A01A_BLACK, GC9A01A_RED, GC9A01A_WHITE);
    }

    tft->setTextSize(2);

    tft->setCursor(40, 40);
    String strCounterGoodValue = "Good: " + String(this->_TSProperties->PropertiesGPS.CounterGoodValue);
    tft->printf("%-15s", strCounterGoodValue.c_str());

    tft->setCursor(30, 60);
    String strCounterTotal = "Total: " + String(this->_TSProperties->PropertiesGPS.CounterTotal);
    tft->printf("%-11s", strCounterTotal.c_str());

    tft->setCursor(15, 85);
    String strUsedSatellite = "Used Sat: " + String(this->_TSProperties->PropertiesGPS.UsedSatellites);
    tft->printf(formatChar, strUsedSatellite.c_str());

    tft->setCursor(2, 110);
    String strLatitude = "Lat: " + String(this->_TSProperties->PropertiesGPS.Latitude, 10);
    tft->printf(formatChar, strLatitude.c_str());

    tft->setCursor(2, 130);
    String strLongitude = "Lon: " + String(this->_TSProperties->PropertiesGPS.Longitude, 10);
    tft->printf(formatChar, strLongitude.c_str());

    tft->setCursor(12, 150);
    String strAltitude = "Alt: " + String(this->_TSProperties->PropertiesGPS.Altitude, 8);
    tft->printf(formatChar, strAltitude.c_str());

    tft->setCursor(20, 170);
    String strSpeed = "Speed: " + String(this->_TSProperties->PropertiesGPS.Speed, 4);
    tft->printf(formatChar, strSpeed.c_str());

    tft->setCursor(40, 190);
    String strAccuracy = "Accu: " + String(this->_TSProperties->PropertiesGPS.Accuracy, 4);
    tft->printf(formatChar, strAccuracy.c_str());

    this->drawBattery(100, 5, 50, this->_TSProperties->PropertiesBattery.BatteryLevel);
}

void ScreenGC9A01::testButtonsScreen()
{
    char *formatChar = (char *)"%-29s";

    this->tft->setCursor(2, 100);
    this->tft->setTextSize(2);
    this->setTextColor();

    // int isButton1Pressed = digitalRead(PIN_BUTTON1); // 33
    int isButton1Pressed = this->_TSProperties->PropertiesButtons.Button1State;
    int isButton2Pressed = this->_TSProperties->PropertiesButtons.Button2State;

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

#pragma endregion Tests
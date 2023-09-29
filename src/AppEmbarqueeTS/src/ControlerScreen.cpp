#include "ControlerScreen.h"

ControlerScreen::ControlerScreen(TSProperties *TSProperties) : _TSProperties(TSProperties),
                                                               _screen(nullptr),
                                                               _currentActivePage(INIT_TS_PAGE_ID),
                                                               _lastActivePage(HOME_PAGE_ID)
{
    this->_screen = new ScreenGC9A01(this->_TSProperties);
    this->tick();
    // first tick() here ???
}

ControlerScreen::~ControlerScreen()
{
    delete this->_screen;
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
void ControlerScreen::tick()
{
    this->_currentActivePage = this->_TSProperties->PropertiesScreen.ActiveScreen;

    if (this->_currentActivePage == this->_lastActivePage)
    {
        this->_TSProperties->PropertiesScreen.IsNewActivePage = false;
    }
    else
    {
        this->_TSProperties->PropertiesScreen.IsNewActivePage = true;
    }

    if (!this->_TSProperties->PropertiesTS.IsInitializedGSM)
    {
        this->_TSProperties->PropertiesScreen.ActiveScreen = ERROR_PAGE_ID;
        // this->_TSProperties->PropertiesScreen.IsNewActivePage = false;
    }

    this->_screen->setRotation(this->_TSProperties->PropertiesScreen.ScreenRotation);

    // if (this->_TSProperties->PropertiesScreen.IsNewActivePage)
    // {
    //     this->_screen->drawBackgroundColor();
    //     // this->_TSProperties->PropertiesScreen.IsNewActivePage = false;
    // }

    Serial.print("Active Screen : ");
    Serial.println(this->_TSProperties->PropertiesScreen.ActiveScreen);

    switch (this->_TSProperties->PropertiesScreen.ActiveScreen)
    {
    case INIT_TS_PAGE_ID: // -1
        this->drawInitTSPage();
        break;

    case HOME_PAGE_ID: // 0
        this->drawHomePage();
        break;

    case RIDE_PAGE_ID: // 1
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

    case RIDE_STATISTICS_PAGE_ID: // 2
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

    case COMPASS_PAGE_ID: // 3
        this->drawCompassPage();
        break;

    case RIDE_DIRECTION_PAGE_ID: // 4
        this->drawRideDirectionPage();
        break;

    case GLOBAL_STATISTICS_PAGE_ID: // 5
        this->drawGlobalStatisticsPage();
        break;

    case GO_HOME_PAGE_ID: // 6
        this->drawGoHomePage();
        break;

    default:                   // -2
        this->drawErrorPage(); // TODO : Enlever l'affichage de la page d'erreur pour la production
        break;
    }

    this->_screen->drawOnScreen();

    // this->_TSProperties->PropertiesScreen.IsNewActivePage = false;
    this->_lastActivePage = this->_currentActivePage;
}

/*


    Draw Pages


*/
#pragma region DrawPages

void ControlerScreen::drawInitTSPage()
{
    // if (this->_TSProperties->PropertiesScreen.IsNewActivePage)
    // {
    this->_screen->drawLogoTS();

    this->_screen->setTextColor();
    this->_screen->setTextSize(1);
    this->_screen->setFont(3);
    this->_screen->printText("Initializing", this->_screen->calculateXCoordTextToCenter("Initializing"), 210);
    this->_screen->setFont(1);
    // }
}

void ControlerScreen::drawHomePage()
{
#if DEBUG_BUTTONS
    this->_screen->testButtonsScreen();
#else
    // if (this->_TSProperties->PropertiesScreen.IsNewActivePage)
    // {
    this->_screen->drawLogoTS();
    // }

    int batteryLengthInPixels = 50;
    this->_screen->drawBattery(this->_screen->calculateXCoordItemToCenter(batteryLengthInPixels),
                               15,
                               batteryLengthInPixels,
                               this->_TSProperties->PropertiesBattery.BatteryLevel);

    int rideStartedLengthInPixels = 40;
    this->_screen->drawIsRideStarted(this->_screen->calculateXCoordItemToCenter(rideStartedLengthInPixels), 185, rideStartedLengthInPixels);
#endif
}

void ControlerScreen::drawCompassPage()
{
    ;
}

void ControlerScreen::drawRideDirectionPage()
{
    ;
}

void ControlerScreen::drawRidePage()
{
#if DEBUG_GSM
    this->_screen->testGPS();
#else
    String speed = "";

    // if (this->_TSProperties->PropertiesScreen.IsNewActivePage)
    // {
    this->_screen->setTextColor();
    this->_screen->setTextSize(2);
    this->_screen->setFont(2);
    this->_screen->printText("Ride Page", this->_screen->calculateXCoordTextToCenter("Ride Page"), 65);

    this->_screen->setFont(1);
    this->_screen->setTextColor();
    this->_screen->setTextSize(2);
    this->_screen->printText("Km/h", this->_screen->calculateXCoordTextToCenter("Km/h"), 220);
    // }

    if (this->_TSProperties->PropertiesGPS.IsFixValid && this->_TSProperties->PropertiesGPS.IsGPSFixed)
    {
        this->_screen->setTextColor();
        speed = String(this->_TSProperties->PropertiesGPS.Speed, 1);
    }
    else if (!this->_TSProperties->PropertiesGPS.IsFixValid && this->_TSProperties->PropertiesGPS.IsGPSFixed)
    {
        this->_screen->setTextColor(GC9A01A_YELLOW, GC9A01A_BLACK, GC9A01A_YELLOW, GC9A01A_WHITE);
        speed = String(this->_TSProperties->PropertiesGPS.Speed, 1);
    }
    else
    {
        this->_screen->setTextColor();
        speed = "---";
    }

    this->_screen->setFont(2);
    this->_screen->setTextSize(4);
    this->_screen->printText(speed, this->_screen->calculateXCoordTextToCenter(speed), 155);

    this->_screen->setFont(1);
    int batteryLengthInPixels = 50;
    this->_screen->drawBattery(this->_screen->calculateXCoordItemToCenter(batteryLengthInPixels),
                               8,
                               batteryLengthInPixels,
                               this->_TSProperties->PropertiesBattery.BatteryLevel);

    // this->_screen->drawIsGPSValid(40, 170, 30);
#endif
}

void ControlerScreen::drawGlobalStatisticsPage()
{
    ;
}

void ControlerScreen::drawGoHomePage()
{
    ;
}

void ControlerScreen::drawRideStatisticsPage()
{
    this->_screen->setTextColor();
    this->_screen->setTextSize(2);
    this->_screen->setFont(2);
    this->_screen->printText("Statistics", this->_screen->calculateXCoordTextToCenter("Statistics"), 65);

    this->_screen->drawStatistics("Dist.:", String(this->_TSProperties->PropertiesCurrentRide.DistanceTotalMeters, 2), "Km", 10, 80, 185, 95);

    uint dureeHour = this->_TSProperties->PropertiesCurrentRide.DurationS / 3600;
    uint dureeMinutes = (this->_TSProperties->PropertiesCurrentRide.DurationS % 3600) / 60;
    uint dureeSecondes = this->_TSProperties->PropertiesCurrentRide.DurationS % 60;
    char buffer[8]; // Un tampon pour stocker la chaîne formatée
    sprintf(buffer, "%02d:%02d:%02d", dureeHour, dureeMinutes, dureeSecondes);
    this->_screen->drawStatistics("Duree:", String(buffer), "h:m:s", 10, 80, 185, 120);

    this->_screen->drawStatistics("V.Moy:", String(this->_TSProperties->PropertiesCurrentRide.AverageSpeed, 2), "Km/h", 10, 80, 185, 145);

    this->_screen->drawStatistics("V.Max:", String(this->_TSProperties->PropertiesCurrentRide.MaxSpeed, 2), "Km/h", 10, 80, 185, 170);
}

void ControlerScreen::drawErrorPage()
{
    this->_screen->drawError();
}

#pragma endregion DrawPages

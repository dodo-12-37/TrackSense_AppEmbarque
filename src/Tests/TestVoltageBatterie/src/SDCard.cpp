#include "SDCard.h"
// #include "Configurations.h"
// #include "StringQueue.h"

/*----- SD Card -----*/
#define PIN_SDCARD_MOSI 15
#define PIN_SDCARD_SCLK 14
#define PIN_SDCARD_CS 13
#define PIN_SDCARD_MISO 2
#define PIN_LED 12

#define SDCARD_ROOT_PATH "/testVBat"
#define SDCARD_FILE_EXTENSION ".csv"
// #define SDCARD_FILE_STATS_NAME "_stats"
#define SDCARD_FILE_POINTS_NAME "_points"
#define SDCARD_POSITION_NUMBER_OF_POINTS 9
#define SDCARD_NUMBER_ELEMENTS_OF_POINT 8

SDCard::SDCard() : _nbRidesInSDCard(0),
                   _isRideStarted(false),
                   _currentPointsFile(),
                   _currentPointsFileName(""),
                   _currentStatsFileName(""),
                   _currentFileSendPoints(),
                   _positionCursorFileSendPoints(0),
                   _isSendingRide(false),
                   _isSendingPoints(false),
                   IsSDCardConnected(false)
{
    this->init();

    this->createRideFiles();
    // this->_currentPointsFile = SD.open(this->_currentPointsFileName, FILE_WRITE);
};

SDCard::~SDCard(){};

void SDCard::init()
{
    Serial.println("========SDCard Detect.======");
    SPI.begin(PIN_SDCARD_SCLK, PIN_SDCARD_MISO, PIN_SDCARD_MOSI);

    this->IsSDCardConnected = SD.begin(PIN_SDCARD_CS);

    if (!this->IsSDCardConnected)
    {
        Serial.println("SDCard MOUNT FAIL");
    }
    else
    {
        uint32_t cardSize = SD.cardSize() / (1024 * 1024);
        String str = "SDCard Size: " + String(cardSize) + "MB";
        Serial.println(str);

        if (!SD.exists(SDCARD_ROOT_PATH))
        {
            SD.mkdir(SDCARD_ROOT_PATH);
        }

        // this->checkFiles();
    }
    Serial.println("===========================");
}

void SDCard::tick(float batteryVoltage, int batteryPourcent)
{
    if (this->IsSDCardConnected)
    {
        // this->processCurrentRide();
        // this->processSendRide();

        this->writePoint(batteryVoltage, batteryPourcent);
    }
};

void SDCard::createRideFiles()
{
    this->_currentPointsFileName =
        String(SDCARD_ROOT_PATH) + "/" + "TEST_VBAT" + SDCARD_FILE_POINTS_NAME + SDCARD_FILE_EXTENSION;

    SD.remove(this->_currentPointsFileName);
    File f = SD.open(this->_currentPointsFileName, FILE_READ);
    f.close();
};

void SDCard::writePoint(float batteryVoltage, int batteryPourcent)
{
    String content =
        String(millis()) + ";" +
        String(batteryVoltage, 2) + ";" +
        String(batteryPourcent) + ";";

    File file = SD.open(this->_currentPointsFileName, FILE_APPEND);

    file.println(content);
    file.close();
};

// void SDCard::writePoint(float batteryVoltage, int batteryPourcent)
// {
//     String content =
//         String(millis()) + ";" +
//         String(batteryVoltage, 2) + ";" +
//         String(batteryPourcent) + ";";

//     this->_currentPointsFile.println(content);
//     // this->_TSProperties->PropertiesCurrentRide.IsPointReadyToSave = false;
// };

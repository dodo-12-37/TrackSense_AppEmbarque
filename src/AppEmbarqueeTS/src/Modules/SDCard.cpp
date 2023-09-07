#include "Modules/SDCard.h"
#include "Configurations.h"


SDCard::SDCard(TrackSenseProperties* trackSenseProperties) 
    : _trackSenseProperties(trackSenseProperties),
    _nbFiles(0),
    _isRideStarted(false),
    _currentPointsFile(),
    _currentPointsFileName(""),
    _currentStatsFileName("")
{
    this->init();
}

SDCard::~SDCard()
{
}

void SDCard::init()
{
    Serial.println("========SDCard Detect.======");
    SPI.begin(PIN_SDCARD_SCLK, PIN_SDCARD_MISO, PIN_SDCARD_MOSI);

    if (!SD.begin(PIN_SDCARD_CS))
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

        this->checkFiles();
    }
    Serial.println("===========================");
}

void SDCard::tick()
{
    File f = SD.open(SDCARD_ROOT_PATH, FILE_WRITE);

    if (this->_trackSenseProperties->PropertiesCurrentRide._isRideStarted && !this->_isRideStarted)
    {
        this->_isRideStarted = true;

        this->createRideFiles();

        this->_currentPointsFile = SD.open(this->_currentPointsFileName, FILE_WRITE);

        if (this->_currentPointsFile) 
        {
            Serial.println("Start saving points to file.");
            _currentPointsFile.println("id;plannedRideId;maxSpeed;avgSpeed;distance;duration;dateBegin;dateEnd;nbPoints;nbFalls");

            // _currentPointsFile.close();

            Serial.println("End saving stats to file.");
        }

        delay(1000);
        
    }
    else if (this->_trackSenseProperties->PropertiesCurrentRide._isRideFinished && this->_isRideStarted)
    {
        this->_isRideStarted = false;

        if (this->_trackSenseProperties->PropertiesCurrentRide._isPointReadyToSave)
        {
            this->writePoint();
        }

        this->writeStatsFile();

        this->_currentPointsFile.close();
    }
    

        // this->setPointsToSendFromFile();
        // this->setStatsToSendFromFile();
        // this->_trackSenseProperties->PropertiesCompletedRideToSend._isReady = true;



    // Serial.println("SDCard");
    // Serial.println("Writing to test.txt...");
    // File file = SD.open("/test.txt", FILE_WRITE);
    // if (file)
    // {
    //     file.println("Testing 1, 2, 3.");
    //     file.close();
    //     Serial.println("done.");
    // }
    // else
    // {
    //     Serial.println("error opening test.txt");
    // }
    // Serial.println("Reading from test.txt...");
    // file = SD.open("/test.txt");
    // if (file)
    // {
    //     while (file.available())
    //     {
    //         Serial.write(file.read());
    //     }
    //     file.close();
    // }
    // else
    // {
    //     Serial.println("error opening test.txt");
    // }
}

void SDCard::checkFiles()
{
    this->_nbFiles = 0;
    File root = SD.open(SDCARD_ROOT_PATH);

    while (File file = root.openNextFile())
    {
        this->_nbFiles++;
        file.close();
    }
    root.close();
}

void SDCard::createRideFiles()
{
    this->_currentStatsFileName = 
            String(SDCARD_ROOT_PATH) + 
            "/" + 
            this->_trackSenseProperties->PropertiesTS._currentRideId + 
            SDCARD_FILE_STATS_NAME + SDCARD_FILE_EXTENSION;
    this->_currentPointsFileName = 
        String(SDCARD_ROOT_PATH) + 
        "/" + 
        this->_trackSenseProperties->PropertiesTS._currentRideId + 
        SDCARD_FILE_STATS_NAME + SDCARD_FILE_EXTENSION;

    File f = SD.open(this->_currentStatsFileName, FILE_READ);
    f.close();
    f = SD.open(this->_currentPointsFileName, FILE_READ);
    f.close();
}

void SDCard::writeStatsFile()
{
    String content = 
        this->_trackSenseProperties->PropertiesCurrentRide._completedRideId + ";" +
        this->_trackSenseProperties->PropertiesCurrentRide._routeId + ";" +
        this->_trackSenseProperties->PropertiesCurrentRide._maxSpeed + ";" +
        this->_trackSenseProperties->PropertiesCurrentRide._avgSpeed + ";" +
        this->_trackSenseProperties->PropertiesCurrentRide._dateBegin + ";" +
        this->_trackSenseProperties->PropertiesCurrentRide._dateEnd + ";" +
        this->_trackSenseProperties->PropertiesCurrentRide._duration + ";" +
        this->_trackSenseProperties->PropertiesCurrentRide._distance + ";" +
        this->_trackSenseProperties->PropertiesCurrentRide._nbPoints + ";" +
        this->_trackSenseProperties->PropertiesCurrentRide._nbFalls + ";";

    File file = SD.open(this->_currentStatsFileName, FILE_WRITE);

    file.println(content);
    file.close();
}

void SDCard::writePoint()
{
    this->_currentPointsFile.println(this->_trackSenseProperties->PropertiesCurrentRide._currentPoint);
    this->_trackSenseProperties->PropertiesCurrentRide._isPointReadyToSave = false;
}
#include "Modules/SDCard.h"
#include "Configurations.h"


SDCard::SDCard(TSProperties* TSProperties) 
    : _TSProperties(TSProperties),
    _nbFiles(0),
    _isRideStarted(false),
    _currentPointsFile(),
    _currentPointsFileName(""),
    _currentStatsFileName(""),
    _currentFileSendPoints(),
    _positionCursorFileSendPoints(0),
    _isSendingPoints(false)
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
    this->processCurrentRide();
    this->processSendRide();
    
    // this->setPointsToSendFromFile();
    // this->setStatsToSendFromFile();
    // this->_TSProperties->PropertiesCompletedRideToSend._isReady = true;
    // 
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
        String(SDCARD_ROOT_PATH) 
        + "/" 
        + this->_TSProperties->PropertiesCurrentRide._completedRideId 
        + SDCARD_FILE_STATS_NAME 
        + SDCARD_FILE_EXTENSION;
    this->_currentPointsFileName = 
        String(SDCARD_ROOT_PATH) 
        + "/" 
        + this->_TSProperties->PropertiesCurrentRide._completedRideId 
        + SDCARD_FILE_POINTS_NAME 
        + SDCARD_FILE_EXTENSION;

    File f = SD.open(this->_currentStatsFileName, FILE_READ);
    f.close();
    f = SD.open(this->_currentPointsFileName, FILE_READ);
    f.close();
}

void SDCard::processCurrentRide()
{
    if (this->_TSProperties->PropertiesCurrentRide._isRideStarted && !this->_isRideStarted)
    {
        this->_isRideStarted = true;

        this->createRideFiles();

        this->_currentPointsFile = SD.open(this->_currentPointsFileName, FILE_WRITE);        
    }
    else if (this->_TSProperties->PropertiesCurrentRide._isRideStarted 
                && this->_TSProperties->PropertiesCurrentRide._isPointReadyToSave)
    {
        this->writePoint();
    }
    else if (this->_TSProperties->PropertiesCurrentRide._isRideFinished && this->_isRideStarted)
    {
        this->_isRideStarted = false;

        if (this->_TSProperties->PropertiesCurrentRide._isPointReadyToSave)
        {
            this->writePoint();
        }

        this->writeStatsFile();

        this->_currentPointsFile.close();
    }
}

void SDCard::writeStatsFile()
{
    String content = 
        this->_TSProperties->PropertiesCurrentRide._completedRideId + ";" +
        this->_TSProperties->PropertiesCurrentRide._plannedRideId + ";" +
        this->_TSProperties->PropertiesCurrentRide._maxSpeed + ";" +
        this->_TSProperties->PropertiesCurrentRide._avgSpeed + ";" +
        this->_TSProperties->PropertiesCurrentRide._dateBegin + ";" +
        this->_TSProperties->PropertiesCurrentRide._dateEnd + ";" +
        this->_TSProperties->PropertiesCurrentRide._durationS + ";" +
        this->_TSProperties->PropertiesCurrentRide._distance + ";" +
        this->_TSProperties->PropertiesCurrentRide._nbPoints + ";" +
        this->_TSProperties->PropertiesCurrentRide._nbFalls + ";";

    File file = SD.open(this->_currentStatsFileName, FILE_WRITE);

    file.println(content);
    file.close();
}

void SDCard::writePoint()
{
    this->_currentPointsFile.println(this->_TSProperties->PropertiesCurrentRide._currentPoint);
    this->_TSProperties->PropertiesCurrentRide._isPointReadyToSave = false;
}

void SDCard::setStatsToSend()
{
    String content = 
        this->_TSProperties->PropertiesCurrentRide._completedRideId + ";" +
        this->_TSProperties->PropertiesCurrentRide._plannedRideId + ";" +
        this->_TSProperties->PropertiesCurrentRide._maxSpeed + ";" +
        this->_TSProperties->PropertiesCurrentRide._avgSpeed + ";" +
        this->_TSProperties->PropertiesCurrentRide._dateBegin + ";" +
        this->_TSProperties->PropertiesCurrentRide._dateEnd + ";" +
        this->_TSProperties->PropertiesCurrentRide._durationS + ";" +
        this->_TSProperties->PropertiesCurrentRide._distance + ";" +
        this->_TSProperties->PropertiesCurrentRide._nbPoints + ";" +
        this->_TSProperties->PropertiesCurrentRide._nbFalls + ";";

    this->_TSProperties->PropertiesCompletedRideToSend._completedRideId 
        = this->_TSProperties->PropertiesCurrentRide._completedRideId;
    this->_TSProperties->PropertiesCompletedRideToSend._stats = content;
    this->_TSProperties->PropertiesCompletedRideToSend._nbPoints 
        = this->_TSProperties->PropertiesCurrentRide._nbPoints;
    this->_TSProperties->PropertiesCompletedRideToSend._currentPoint = 0;
    this->_TSProperties->PropertiesCompletedRideToSend._isReady = true;
    this->_TSProperties->PropertiesCompletedRideToSend._isReceived  = false;
    this->_TSProperties->PropertiesCompletedRideToSend._isPointReceived  = false;
    this->_TSProperties->PropertiesCompletedRideToSend._isPointReady  = false;
}

void SDCard::setPointsToSendFromFile()
{
    if (this->_TSProperties->PropertiesCompletedRideToSend._currentPoint == 0)
    {
        String fileName = 
            String(SDCARD_ROOT_PATH) 
            + "/" 
            + this->_TSProperties->PropertiesCompletedRideToSend._completedRideId 
            + SDCARD_FILE_POINTS_NAME 
            + SDCARD_FILE_EXTENSION;

        this->_currentFileSendPoints = SD.open(this->_currentPointsFileName, FILE_READ);
        this->_positionCursorFileSendPoints = 0;
    }
    
    if (!this->_TSProperties->PropertiesCompletedRideToSend._isPointReady
                && this->_TSProperties->PropertiesCompletedRideToSend._currentPoint
                    < this->_TSProperties->PropertiesCompletedRideToSend._nbPoints)
    {
        ++this->_TSProperties->PropertiesCompletedRideToSend._currentPoint;

        this->_currentFileSendPoints.seek(this->_positionCursorFileSendPoints);
        String point = this->_currentFileSendPoints.readStringUntil('\n');
        this->_positionCursorFileSendPoints = this->_currentFileSendPoints.position();

        this->_TSProperties->PropertiesCompletedRideToSend._point = point;
        this->_TSProperties->PropertiesCompletedRideToSend._isPointReady = true;
        this->_TSProperties->PropertiesCompletedRideToSend._isPointReceived = false;
    }
    else if (this->_TSProperties->PropertiesCompletedRideToSend._currentPoint
                    >= this->_TSProperties->PropertiesCompletedRideToSend._nbPoints)
    {
        this->_currentFileSendPoints.close();
        this->_isSendingPoints = false;
        this->_TSProperties->PropertiesCompletedRideToSend._isPointReady = false;
        this->_TSProperties->PropertiesCompletedRideToSend._isPointReceived = false;
    }
}

void SDCard::processSendRide()
{
    if (this->_TSProperties->PropertiesCurrentRide._isRideFinished)
    {
        if (!this->_TSProperties->PropertiesCompletedRideToSend._isReady)
        {
            this->setStatsToSend();
            this->_isSendingPoints = true;
        }
        else if (this->_isSendingPoints)
        {
            this->setPointsToSendFromFile();
        }
    }
}


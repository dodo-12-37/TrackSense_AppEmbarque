#include "Modules/SDCard.h"
#include "Configurations.h"


SDCard::SDCard(TrackSenseProperties* trackSenseProperties) 
    : trackSenseProperties(trackSenseProperties),
    _nbFiles(0)
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

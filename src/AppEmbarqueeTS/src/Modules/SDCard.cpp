#include "Modules/SDCard.h"



SDCard::SDCard(TrackSenseProperties* trackSenseProperties) : trackSenseProperties(trackSenseProperties)
{
    this->init();
}

SDCard::~SDCard()
{
}

void SDCard::init()
{
    Serial.println("Initializing SD card...");
    SPI.begin(PIN_SDCARD_SCLK, PIN_SDCARD_MISO, PIN_SDCARD_MOSI);

    if (!SD.begin(PIN_SDCARD_CS))
    {
        Serial.println("initialization failed!");
        return;
    }
    Serial.println("initialization done.");
}

void SDCard::tick()
{
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

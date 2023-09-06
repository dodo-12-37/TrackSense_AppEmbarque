/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/lilygo-t-sim7000g-esp32-gps-data/

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/
#define DISABLE_GPS_AND_MODEM FALSE

void printGPSOnScreen(float lat, float lon, float speed, float alt, int counterTotal, int counterGoodValue);
void enableGPSAndModem();
void disableGPSAndModem();

#define TINY_GSM_MODEM_SIM7000
#define TINY_GSM_RX_BUFFER 1024 // Set RX buffer to 1Kb

#include <Arduino.h>
#include <TinyGsmClient.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_GC9A01A.h>

// LilyGO T-SIM7000G Pinout
#define UART_BAUD 115200
#define PIN_DTR 25
#define PIN_TX 27
#define PIN_RX 26
#define PWR_PIN 4

#define LED_PIN 12

// Set serial for debug console (to Serial Monitor, default speed 115200)
#define SerialMon Serial
// Set serial for AT commands
#define SerialAT Serial1

TinyGsm modem(SerialAT);

/* Screen */
#define TFT_BL_BLK -1
#define TFT_CS_SS 05
#define TFT_DC 00
#define TFT_RES_RST -1
#define TFT_SDA_DIN_MOSI 23
#define TFT_SCL_CLK_SCK 18
// #define TFT_MISO 19

Adafruit_GC9A01A tft(TFT_CS_SS, TFT_DC, TFT_SDA_DIN_MOSI, TFT_SCL_CLK_SCK, TFT_RES_RST);

void setup()
{
    /* Set Screen */
    tft.begin();
    tft.fillScreen(GC9A01A_BLACK);
    tft.setRotation(0);
    
    tft.setTextColor(GC9A01A_WHITE, GC9A01A_BLACK);
    tft.setCursor(30, 40);
    tft.setTextSize(3);
    tft.printf("%-11s", "TrackSense");
    tft.setCursor(10, 150);
    tft.printf("%-13s", "Initializing");
    tft.setCursor(90, 180);
    tft.printf("%-4s", "GPS");

    SerialMon.begin(115200);
    SerialMon.println("Place your board outside to catch satelite signal");
    tft.setTextColor(GC9A01A_DARKGREEN, GC9A01A_YELLOW);
    tft.setCursor(0, 90);
    tft.setTextSize(2);
    tft.printf("%-50s", "Place your board outside to catch satelite signal");

    // Set LED OFF
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);

    // Turn on the modem
    pinMode(PWR_PIN, OUTPUT);
    digitalWrite(PWR_PIN, HIGH);
    delay(300);
    digitalWrite(PWR_PIN, LOW);

    delay(1000);

    // Set module baud rate and UART pins
    SerialAT.begin(UART_BAUD, SERIAL_8N1, PIN_RX, PIN_TX);

    // Restart takes quite some time
    // To skip it, call init() instead of restart()
    SerialMon.println("Initializing modem...");
    if (!modem.restart())
    {
        Serial.println("Failed to restart modem, attempting to continue without restarting");
    }

    // Print modem info
    String modemName = modem.getModemName();
    delay(500);
    SerialMon.println("Modem Name: " + modemName);

    String modemInfo = modem.getModemInfo();
    delay(500);
    SerialMon.println("Modem Info: " + modemInfo);

    // Init String on Screen
    tft.fillScreen(GC9A01A_BLACK);
    printGPSOnScreen(0, 0, 0, 0, -1, -1);

    // Open port 4 for GPS
    void enableGPSAndModem();
}

void loop()
{
    delay(15000);
    float lat = 0;
    float lon = 0;
    float speed = 0;
    float alt = 0;
    int vsat = 0;
    int usat = 0;
    float accuracy = 0;
    int year = 0;
    int month = 0;
    int day = 0;
    int hour = 0;
    int min = 0;
    int sec = 0;

    modem.getGsmLocation();
    SerialMon.println();
    SerialMon.print("GSM Based Location: ");
    SerialMon.println(modem.getGsmLocation());
    SerialMon.println();
    SerialMon.println();

    int counterGoodValue = 0;

    for (int counterTotal = 0; counterTotal < 1000; counterTotal++)
    {
        SerialMon.println("=======================================");
        SerialMon.println("Requesting current GPS/GNSS/GLONASS location");
        if (modem.getGPS(&lat, &lon, &speed, &alt, &vsat, &usat, &accuracy,
                         &year, &month, &day, &hour, &min, &sec))
        {
            SerialMon.println("Latitude: " + String(lat, 8) + "\tLongitude: " + String(lon, 8));
            SerialMon.println("Speed: " + String(speed) + "\tAltitude: " + String(alt));
            SerialMon.println("Visible Satellites: " + String(vsat) + "\tUsed Satellites: " + String(usat));
            SerialMon.println("Accuracy: " + String(accuracy));
            SerialMon.println("Year: " + String(year) + "\tMonth: " + String(month) + "\tDay: " + String(day));
            SerialMon.println("Hour: " + String(hour) + "\tMinute: " + String(min) + "\tSecond: " + String(sec));
        }
        else
        {
            SerialMon.println("Couldn't get GPS/GNSS/GLONASS location");
        }

        /* Print on LCD Screen */
        printGPSOnScreen(lat, lon, speed, alt, counterTotal, counterGoodValue);
        counterTotal++;

        SerialMon.println("Retrieving GPS/GNSS/GLONASS location again as a string");
        String gps_raw = modem.getGPSraw();
        SerialMon.println("GPS/GNSS Based Location String: " + gps_raw);
        SerialMon.println("=======================================");
    }

#if DISABLE_GPS_AND_MODEM
    // Turn off the modem and GPS
    disableGPSAndModem();
#endif
}

void enableGPSAndModem()
{
    // Set SIM7000G GPIO4 HIGH ,turn on GPS power
    // CMD:AT+SGPIO=0,4,1,1
    // Only in version 20200415 is there a function to control GPS power
    modem.sendAT("+SGPIO=0,4,1,1");
    if (modem.waitResponse(10000L) != 1)
    {
        SerialMon.println(" SGPIO=0,4,1,1 false ");
    }

    modem.enableGPS();
}

void disableGPSAndModem()
{
    SerialMon.println("Disabling GPS");
    modem.disableGPS();

    // Set SIM7000G GPIO4 LOW ,turn off GPS power
    // CMD:AT+SGPIO=0,4,1,0
    // Only in version 20200415 is there a function to control GPS power
    modem.sendAT("+SGPIO=0,4,1,0");
    if (modem.waitResponse(10000L) != 1)
    {
        SerialMon.println(" SGPIO=0,4,1,0 false ");
    }

    delay(200);
    // Do nothing forevermore
    while (true)
    {
        modem.maintain();
    }
}

void printGPSOnScreen(float lat, float lon, float speed, float alt, int counterTotal, int counterGoodValue)
{
    char *formatChar = (char *)"%-29s";
    bool locationIsValid = false;

    if (lat != 0 && lon != 0)
    {
        locationIsValid = true;
    }

    if (locationIsValid)
    {
        tft.setTextColor(GC9A01A_GREEN, GC9A01A_BLACK);
    }
    else
    {
        tft.setTextColor(GC9A01A_RED, GC9A01A_BLACK);
    }

    tft.setTextSize(2);

    tft.setCursor(40, 40);
    String strCounterGoodValue = "Good : " + String(counterGoodValue);
    tft.printf("%-15s", strCounterGoodValue.c_str());
    
    tft.setCursor(30, 60);
    String strCounterTotal = "Total : " + String(counterTotal);
    tft.printf("%-11s", strCounterTotal.c_str());

    tft.setCursor(30, 90);
    String strIsValid = "IsValid : " + String(locationIsValid ? "true" : "false");
    tft.printf(formatChar, strIsValid.c_str());

    tft.setCursor(20, 110);
    String strLatitude = "Lat : " + String(lat, 8);
    tft.printf(formatChar, strLatitude.c_str());

    tft.setCursor(20, 130);
    String strLongitude = "Long : " + String(lon, 8);
    tft.printf(formatChar, strLongitude.c_str());

    tft.setCursor(20, 150);
    String strAltitude = "Alt : " + String(alt, 8);
    tft.printf(formatChar, strAltitude.c_str());

    tft.setCursor(20, 170);
    String strSpeed = "Speed : " + String(speed, 4);
    tft.printf(formatChar, strSpeed.c_str());

}

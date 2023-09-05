#pragma once
#include <Arduino.h>


/*----- DEBUG -----*/
#define DEBUG_BUTTONS false


/*----- Screen -----*/
#define SPI_TFCard 0 // 1 = SPI, 0 = VSPI

#if SPI_TFCard

    #define TFT_BL_BLK -1       // LED back-light
    #define TFT_CS_SS 12        // 25       // Chip select control pin
    #define TFT_DC 25           // 02          // Data Command control pin
    #define TFT_RES_RST -1      // Reset pin (could connect to Arduino RESET pin)
    #define TFT_SDA_DIN_MOSI 15 // In some display driver board, it might be written as "SDA" and so on.
    #define TFT_SCL_CLK_SCK 14  // In some display driver board, it might be written as "SCL" and so on.
    // #define TFT_MISO 02          // Ne semble pas être utile, car non tactile

#else // VSPI

    #define TFT_BL_BLK -1       // LED back-light
    #define TFT_CS_SS 05        // 25     // Chip select control pin
    #define TFT_DC 00           // 19        // Data Command control pin
    #define TFT_RES_RST -1      // Reset pin (could connect to Arduino RESET pin)
    #define TFT_SDA_DIN_MOSI 23 // In some display driver board, it might be written as "SDA" and so on.
    #define TFT_SCL_CLK_SCK 18  // In some display driver board, it might be written as "SCL" and so on.
    // #define TFT_MISO 19          // Ne semble pas être utile, car non tactile

#endif

/*----- SD Card -----*/
#define PIN_SDCARD_MOSI 15
#define PIN_SDCARD_SCLK 14
#define PIN_SDCARD_CS 13
#define PIN_SDCARD_MISO 2


/*----- LilyGO T-SIM7000G (GPS, LTE) -----*/
#define GPS_UART_BAUD   115200
#define PIN_GPS_LTE_TX 27 // 26
#define PIN_GPS_LTE_RX 26 // 27
#define PIN_GPS_LTE_PWR 4
#define TINY_GSM_MODEM_SIM7000  // Utile ???
#define TINY_GSM_RX_BUFFER 1024 // Set RX buffer to 1Kb
// #define GPSNEO6M_SERIAL_BAUD 9600
#define DISTANCE_MINIMUM_AJOUT_POSITION 10

/*----- Accelerometer, Gyroscope, Compass, Temperature -----*/
#define PIN_GY87_SDA 21
#define PIN_GY87_SCL 22


/*----- Buzzer -----*/
#define PIN_BUZZER 32


/*----- Buttons -----*/
#define PIN_BUTTON1 33
#define PIN_BUTTON2 34
#define BUTTON_LONG_PRESS_DURATION_MS 2000
#define BUTTON_INACTIVITY_TIME_MS 10000


/*----- BLE -----*/
#define BLE_DEVICE_NAME "TrackSense"
#define BLE_PIN_CODE "123456"
#define BLE_TRUE "true"
#define BLE_FALSE "false"

// Service et caracterisiques pour CompletedRide
#define BLE_COMPLETED_RIDE_SERVICE_UUID "62ffab64-3646-4fb9-88d8-541deb961192"
#define BLE_COMPLETED_RIDE_CHARACTERISTIC_ID "51656aa8-b795-427f-a96c-c4b6c57430dd"
#define BLE_COMPLETED_RIDE_CHARACTERISTIC_ROUTE_ID "17072e79-57c3-4aa2-a71e-02dea60b5804"
#define BLE_COMPLETED_RIDE_CHARACTERISTIC_MAX_SPEED "f3c6a5a1-c56a-4300-9e33-1e6f5505d3de"
#define BLE_COMPLETED_RIDE_CHARACTERISTIC_AVG_SPEED "e4c18d44-dde8-4344-982a-404260c08056"
#define BLE_COMPLETED_RIDE_CHARACTERISTIC_DATE_BEGIN "e3c59927-31f2-4821-b598-6ac659cc4515"
#define BLE_COMPLETED_RIDE_CHARACTERISTIC_DATE_END "c3102e0c-3e02-4d3b-a35f-147d02c08c42"
#define BLE_COMPLETED_RIDE_CHARACTERISTIC_DURATION "e3de9b11-f709-4d56-8717-b1faf0f0b3ef"
#define BLE_COMPLETED_RIDE_CHARACTERISTIC_DISTANCE "0f2c291c-76b5-4511-a103-530a83b626c4"
#define BLE_COMPLETED_RIDE_CHARACTERISTIC_POINTS "42154deb-5828-4876-8d4f-eaec38fa1ea7"
#define BLE_COMPLETED_RIDE_CHARACTERISTIC_NUMBER_OF_POINTS "86abb0bc-770e-4887-a6ff-47615669fcd6"
#define BLE_COMPLETED_RIDE_CHARACTERISTIC_NUMBER_OF_FALLS "3d29747b-7a8a-4df0-a8e9-21dc2cc90d89"
#define BLE_COMPLETED_RIDE_CHARACTERISTIC_IS_READY "9456444a-4b5f-11ee-be56-0242ac120002"
#define BLE_COMPLETED_RIDE_CHARACTERISTIC_IS_RECEIVED "08382f5e-4b60-11ee-be56-0242ac120002"





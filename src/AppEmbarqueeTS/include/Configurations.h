#pragma once
#include <Arduino.h>


/*----- DEBUG -----*/
#define DEBUG_BUTTONS false
#define DEBUG_GSM true


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

#define TFT_WIDTH 240
#define TFT_HEIGHT 240
// #define TFT_INIT_ROTATION 0
#define TFT_LIGHT_MODE_BACKGROUND_COLOR GC9A01A_WHITE
#define TFT_LIGHT_MODE_TEXT_COLOR GC9A01A_BLACK
#define TFT_DARK_MODE_BACKGROUND_COLOR GC9A01A_BLACK
#define TFT_DARK_MODE_TEXT_COLOR GC9A01A_WHITE


/*----- Page ID -----*/
#define NB_ACTIVE_PAGES 3   // 3 == Home Page, Ride Page, Ride Statistics Page
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
#define HOME_PAGE_ID 0
#define RIDE_PAGE_ID 1
#define RIDE_STATISTICS_PAGE_ID 2
#define COMPASS_PAGE_ID 3
#define RIDE_DIRECTION_PAGE_ID 4
#define GLOBAL_STATISTICS_PAGE_ID 5
#define GO_HOME_PAGE_ID 6
#define INIT_TS_PAGE_ID -1
#define ERROR_PAGE_ID -2

/*----- SD Card -----*/
#define PIN_SDCARD_MOSI 15
#define PIN_SDCARD_SCLK 14
#define PIN_SDCARD_CS 13
#define PIN_SDCARD_MISO 2
#define PIN_SDCARD_LED 12

#define SDCARD_ROOT_PATH "/cr"
#define SDCARD_FILE_EXTENSION ".csv"
#define SDCARD_FILE_STATS_NAME "_stats"
#define SDCARD_FILE_POINTS_NAME "_points"

/*----- GSM LilyGO T-SIM7000G (GPS, LTE) -----*/
// Exemple point
// 1;0.0000000000;0.0000000000;0.0000000000;00.00;00.00;0000/00/00-00:00:00;00:00:00

// Exemple Stats
// 00000000-0000-0000-0000-000000000000;00000000-0000-0000-0000-000000000000;00.00;00.00;0000/00/00-00:00:00;0000/00/00-00:00:00;00:00:00;000.0;5;0

#define SerialAT Serial1
#define GPS_UART_BAUD   115200
#define PIN_GSM_DTR 25
#define PIN_GSM_TX 27
#define PIN_GSM_RX 26
#define PIN_GSM_PWR 4
#define TINY_GSM_MODEM_SIM7000  // Active le bon processeur
#define TINY_GSM_RX_BUFFER 1024 // Set RX buffer to 1Kb
#define MINIMUM_DISTANCE_TO_ADD_POSITION 10

/*----- I2C : Accelerometer, Gyroscope, Compass, Temperature -----*/
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
#define BLE_OK "ok"

#define BLE_DELAY_SEND_STATS_MS 2000
#define BLE_DELAY_SEND_POINT_MS 500

// Service et caracterisiques pour CompletedRide
#define BLE_COMPLETED_RIDE_SERVICE_UUID "62ffab64-3646-4fb9-88d8-541deb961192"

#define BLE_COMPLETED_RIDE_CARACTRISTIC_STATS "51656aa8-b795-427f-a96c-c4b6c57430dd"
#define BLE_COMPLETED_RIDE_DESCRIPTOR_STATS_NAME "Completed Ride Stats"
#define BLE_COMPLETED_RIDE_DESCRIPTOR_STATS_UUID "5a2b4a0f-8ddd-4c69-a825-dbab5822ba0e"

#define BLE_COMPLETED_RIDE_CHARACTERISTIC_IS_STATS_READY "9456444a-4b5f-11ee-be56-0242ac120002"
#define BLE_COMPLETED_RIDE_DESCRIPTOR_IS_READY_NAME "Completed Ride Stats Is Ready"
#define BLE_COMPLETED_RIDE_DESCRIPTOR_IS_READY_UUID "ff1b5451-f570-430e-85a0-09b866593aad"

#define BLE_COMPLETED_RIDE_CHARACTERISTIC_POINT "42154deb-5828-4876-8d4f-eaec38fa1ea7"
#define BLE_COMPLETED_RIDE_DESCRIPTOR_POINT_NAME "Completed Ride Point"
#define BLE_COMPLETED_RIDE_DESCRIPTOR_POINT_UUID "35267417-01b5-4fe1-adc6-365edf6cb6ec"

#define BLE_COMPLETED_RIDE_CHARACTERISTIC_POINT_NUMBER "c5799499-9053-4a9e-a2d5-b8814c5ff12b"
#define BLE_COMPLETED_RIDE_DESCRIPTOR_POINT_NUMBER_NAME "Completed Ride Point"
#define BLE_COMPLETED_RIDE_DESCRIPTOR_POINT_NUMBER_UUID "e4c18d44-dde8-4344-982a-404260c08056"

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

#define TFT_WIDTH 240
#define TFT_HEIGHT 240
// #define TFT_INIT_ROTATION 0
#define TFT_LIGHT_MODE_BACKGROUND_COLOR GC9A01A_WHITE
#define TFT_LIGHT_MODE_TEXT_COLOR GC9A01A_BLACK
#define TFT_DARK_MODE_BACKGROUND_COLOR GC9A01A_BLACK
#define TFT_DARK_MODE_TEXT_COLOR GC9A01A_WHITE

/*----- SD Card -----*/
#define PIN_SDCARD_MOSI 15
#define PIN_SDCARD_SCLK 14
#define PIN_SDCARD_CS 13
#define PIN_SDCARD_MISO 2
#define PIN_SDCARD_LED 12

#define SDCARD_ROOT_PATH "/rd"
#define SDCARD_FILE_EXTENSION ".csv"
#define SDCARD_FILE_STATS_NAME "_stats"
#define SDCARD_FILE_POINTS_NAME "_points"

/*----- GSM LilyGO T-SIM7000G (GPS, LTE) -----*/
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

// Service et caracterisiques pour CompletedRide
#define BLE_COMPLETED_RIDE_SERVICE_UUID "62ffab64-3646-4fb9-88d8-541deb961192"
#define BLE_COMPLETED_RIDE_CARACTRISTIC_STATS "51656aa8-b795-427f-a96c-c4b6c57430dd"
#define BLE_COMPLETED_RIDE_DESCRIPTOR_STATS_NAME "Completed Ride Stats"
#define BLE_COMPLETED_RIDE_DESCRIPTOR_STATS_UUID "5a2b4a0f-8ddd-4c69-a825-dbab5822ba0e"

// #define BLE_COMPLETED_RIDE_CHARACTERISTIC_ID "51656aa8-b795-427f-a96c-c4b6c57430dd"
// #define BLE_COMPLETED_RIDE_DESCRIPTOR_ID_NAME "Complete Ride ID"
// #define BLE_COMPLETED_RIDE_DESCRIPTOR_ID_UUID "5a2b4a0f-8ddd-4c69-a825-dbab5822ba0e"
// #define BLE_COMPLETED_RIDE_CHARACTERISTIC_ROUTE_ID "17072e79-57c3-4aa2-a71e-02dea60b5804"
// #define BLE_COMPLETED_RIDE_DESCRIPTOR_ROUTE_ID_NAME "Planned Ride ID"
// #define BLE_COMPLETED_RIDE_DESCRIPTOR_ROUTE_ID_UUID "0e5d0edf-b5ce-4c42-ac61-dcc6f43fc835"
// #define BLE_COMPLETED_RIDE_CHARACTERISTIC_MAX_SPEED "f3c6a5a1-c56a-4300-9e33-1e6f5505d3de"
// #define BLE_COMPLETED_RIDE_DESCRIPTOR_MAX_SPEED_NAME "Completed Ride Max Speed"
// #define BLE_COMPLETED_RIDE_DESCRIPTOR_MAX_SPEED_UUID "c5799499-9053-4a9e-a2d5-b8814c5ff12b"
// #define BLE_COMPLETED_RIDE_CHARACTERISTIC_AVG_SPEED "e4c18d44-dde8-4344-982a-404260c08056"
// #define BLE_COMPLETED_RIDE_DESCRIPTOR_AVG_SPEED_NAME "Completed Ride Average Speed"
// #define BLE_COMPLETED_RIDE_DESCRIPTOR_AVG_SPEED_UUID "4e34ced4-c23c-437c-be25-5cea6092b8b6"
// #define BLE_COMPLETED_RIDE_CHARACTERISTIC_DATE_BEGIN "e3c59927-31f2-4821-b598-6ac659cc4515"
// #define BLE_COMPLETED_RIDE_DESCRIPTOR_DATE_BEGIN_NAME "Completed Ride Date Begin"
// #define BLE_COMPLETED_RIDE_DESCRIPTOR_DATE_BEGIN_UUID "8c51364b-7188-487b-b962-cda44451d0bf"
// #define BLE_COMPLETED_RIDE_CHARACTERISTIC_DATE_END "c3102e0c-3e02-4d3b-a35f-147d02c08c42"
// #define BLE_COMPLETED_RIDE_DESCRIPTOR_DATE_END_NAME "Completed Ride Date End"
// #define BLE_COMPLETED_RIDE_DESCRIPTOR_DATE_END_UUID "4221b172-a852-46b3-83c7-44ec00712cd8"
// #define BLE_COMPLETED_RIDE_CHARACTERISTIC_DURATION "e3de9b11-f709-4d56-8717-b1faf0f0b3ef"
// #define BLE_COMPLETED_RIDE_DESCRIPTOR_DURATION_NAME "Completed Ride Duration"
// #define BLE_COMPLETED_RIDE_DESCRIPTOR_DURATION_UUID "80959f98-44fe-4823-bc1b-19612b9a79d3"
// #define BLE_COMPLETED_RIDE_CHARACTERISTIC_DISTANCE "0f2c291c-76b5-4511-a103-530a83b626c4"
// #define BLE_COMPLETED_RIDE_DESCRIPTOR_DISTANCE_NAME "Completed Ride Distance"
// #define BLE_COMPLETED_RIDE_DESCRIPTOR_DISTANCE_UUID "6d9e56f3-7302-4605-b703-ccea576adf3c"

#define BLE_COMPLETED_RIDE_CHARACTERISTIC_POINTS "42154deb-5828-4876-8d4f-eaec38fa1ea7"
#define BLE_COMPLETED_RIDE_DESCRIPTOR_POINTS_NAME "Completed Ride Points"
#define BLE_COMPLETED_RIDE_DESCRIPTOR_POINTS_UUID "35267417-01b5-4fe1-adc6-365edf6cb6ec"

// #define BLE_COMPLETED_RIDE_CHARACTERISTIC_NUMBER_OF_POINTS "86abb0bc-770e-4887-a6ff-47615669fcd6"
// #define BLE_COMPLETED_RIDE_DESCRIPTOR_NUMBER_OF_POINTS_NAME "Completed Ride Number of Points"
// #define BLE_COMPLETED_RIDE_DESCRIPTOR_NUMBER_OF_POINTS_UUID "6bca2695-a837-4d5d-986f-6fffea16578e"
// #define BLE_COMPLETED_RIDE_CHARACTERISTIC_NUMBER_OF_FALLS "3d29747b-7a8a-4df0-a8e9-21dc2cc90d89"
// #define BLE_COMPLETED_RIDE_DESCRIPTOR_NUMBER_OF_FALLS_NAME "Completed Ride Number of Falls"
// #define BLE_COMPLETED_RIDE_DESCRIPTOR_NUMBER_OF_FALLS_UUID "d4b1e746-3e94-4073-abb9-0901d99f1ff6"

#define BLE_COMPLETED_RIDE_CHARACTERISTIC_IS_READY "9456444a-4b5f-11ee-be56-0242ac120002"
#define BLE_COMPLETED_RIDE_DESCRIPTOR_IS_READY_NAME "Completed Ride Is Ready"
#define BLE_COMPLETED_RIDE_DESCRIPTOR_IS_READY_UUID "ff1b5451-f570-430e-85a0-09b866593aad"
#define BLE_COMPLETED_RIDE_CHARACTERISTIC_IS_RECEIVED "08382f5e-4b60-11ee-be56-0242ac120002"
#define BLE_COMPLETED_RIDE_DESCRIPTOR_IS_RECEIVED_NAME "Completed Ride Is Received"
#define BLE_COMPLETED_RIDE_DESCRIPTOR_IS_RECEIVED_UUID "136c1256-2afb-46e3-b956-3aeaa55951e0"





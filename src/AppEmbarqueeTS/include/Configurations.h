#pragma once
#include <Arduino.h>



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
#define UART_BAUD   115200
#define PIN_GPS_LTE_TX 27 // 26
#define PIN_GPS_LTE_RX 26 // 27
#define PIN_GPS_LTE_PWR 4
#define TINY_GSM_MODEM_SIM7000  // Utile ???
#define TINY_GSM_RX_BUFFER 1024 // Set RX buffer to 1Kb


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
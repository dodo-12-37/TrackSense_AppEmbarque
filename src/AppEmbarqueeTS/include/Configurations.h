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
    // #define TFT_MISO 02          // Ne semble pas être utile

#else // VSPI

    #define TFT_BL_BLK -1       // LED back-light
    #define TFT_CS_SS 05        // 25     // Chip select control pin
    #define TFT_DC 00           // 19        // Data Command control pin
    #define TFT_RES_RST -1      // Reset pin (could connect to Arduino RESET pin)
    #define TFT_SDA_DIN_MOSI 23 // In some display driver board, it might be written as "SDA" and so on.
    #define TFT_SCL_CLK_SCK 18  // In some display driver board, it might be written as "SCL" and so on.
    // #define TFT_MISO 19          // Ne semble pas être utile

    /*
        @brief  Instantiate Adafruit GC9A01A driver with software SPI
        @param  cs    Chip select pin #   05
        @param  dc    Data/Command pin #    19
        @param  mosi  SPI MOSI pin #    23
        @param  sclk  SPI Clock pin #   18
        @param  rst   Reset pin # (optional, pass -1 if unused)
        @param  miso  SPI MISO pin # (optional, pass -1 if unused)
    */
#endif


/*----- Buzzer -----*/
#define PIN_BUZZER 26

/*----- Buttons -----*/
#define LONG_TOUCH_TIME_BUTTON_MS 2000
#define PIN_BUTTON1 25
#define PIN_BUTTON2 25
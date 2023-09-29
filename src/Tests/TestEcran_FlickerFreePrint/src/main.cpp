#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_GC9A01A.h>
#include <FlickerFreePrint.h>
#include <Fonts\FreeSansOblique12pt7b.h>

/*----- Screen -----*/
#define SPI_TFCard 0 // 1 = SPI, 0 = VSPI

#if SPI_TFCard

    #define TFT_BLK -1       // LED back-light
    #define TFT_CS 12        // 25       // Chip select control pin
    #define TFT_DC 25           // 02          // Data Command control pin
    #define TFT_RST -1      // Reset pin (could connect to Arduino RESET pin)
    #define TFT_MOSI 15 // In some display driver board, it might be written as "SDA" and so on.
    #define TFT_CLK 14  // In some display driver board, it might be written as "SCL" and so on.
    // #define TFT_MISO 02          // Ne semble pas être utile, car non tactile

#else // VSPI

    #define TFT_BLK -1       // LED back-light
    #define TFT_CS 05        // 25     // Chip select control pin
    #define TFT_DC 00           // 19        // Data Command control pin
    #define TFT_RST -1      // Reset pin (could connect to Arduino RESET pin)
    #define TFT_MOSI 23 // In some display driver board, it might be written as "SDA" and so on.
    #define TFT_CLK 18  // In some display driver board, it might be written as "SCL" and so on.
    // #define TFT_MISO 19          // Ne semble pas être utile, car non tactile

#endif

#define TFT_WIDTH 240
#define TFT_HEIGHT 240

// setup some colors
#define C_BLACK 0x0000
#define C_BLUE 0x001F
#define C_RED 0xF800
#define C_GREEN 0x07E0
#define C_CYAN 0x07FF
#define C_MAGENTA 0xF81F
#define C_YELLOW 0xFFE0
#define C_WHITE 0xFFFF

// create the display object
// Adafruit_GC9A01A Display(TFT_CS, TFT_DC);
Adafruit_GC9A01A Display(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST);

// create a flicker free print object for each data to be printed with the flicker free option
// the library used template scheme so you need to pass the data type in <>
FlickerFreePrint<Adafruit_GC9A01A> Data1(&Display, C_WHITE, C_BLACK);
FlickerFreePrint<Adafruit_GC9A01A> Data2(&Display, C_WHITE, C_BLACK);
FlickerFreePrint<Adafruit_GC9A01A> Data3(&Display, C_WHITE, C_BLACK);

// setup some variables
int i;
float j;
unsigned long curtime, thetime;
byte h, m, s;
char str[30];

void setup()
{
    Serial.begin(115200);

    pinMode(TFT_CS, OUTPUT);
    pinMode(TFT_DC, OUTPUT);

    // while (!Serial);     // used for leonardo debugging

    Display.begin();
    Display.setRotation(0);
    Display.fillScreen(C_BLACK);

    Display.fillRect(0, 55, 240, 35, C_RED);
}

void loop()
{
    // get some data
    i++;
    j += 0.0013;
    thetime = millis();
    h = (thetime / 3600000) / 1000;
    m = (thetime / 1000 - (3600 * h)) / 60;
    s = (thetime / 1000 - (3600 * h) - (m * 60));
    sprintf(str, "Time: %02d:%02d:%02d", h, m, s);

    // first example
    Display.setFont(&FreeSansOblique12pt7b);
    Display.setCursor(20, 80);
    Display.setTextColor(C_WHITE, C_BLACK);
    Display.print("Crude repaint: ");
    Display.fillRect(Display.getCursorX(), 55, 100, 35, C_RED);
    Display.print(i);

    // now draw some data using flicker free print
    Display.setCursor(20, 110);
    Display.setTextColor(C_WHITE, C_RED);
    Display.print("FlickerFree library: ");

    Display.setCursor(40, 140);
    Data1.setTextColor(C_YELLOW, C_BLACK);
    Data1.print(i);

    Display.setCursor(40, 170);
    Data2.setTextColor(C_BLUE, C_BLACK);
    Data2.print(j, 4);

    Display.setCursor(40, 200);
    Data3.setTextColor(C_GREEN, C_BLACK);
    Data3.print(str);

    // delay(100);
}

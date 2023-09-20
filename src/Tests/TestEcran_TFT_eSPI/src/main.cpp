
//   Diagnostic test for the displayed colour order
//
// Written by Bodmer 17/2/19 for the TFT_eSPI library:
// https://github.com/Bodmer/TFT_eSPI

/* 
 Different hardware manufacturers use different colour order
 configurations at the hardware level.  This may result in
 incorrect colours being displayed.

 Incorrectly displayed colours could also be the result of
 using the wrong display driver in the library setup file.

 Typically displays have a control register (MADCTL) that can
 be used to set the Red Green Blue (RGB) colour order to RGB
 or BRG so that red and blue are swapped on the display.

 This control register is also used to manage the display
 rotation and coordinate mirroring. The control register
 typically has 8 bits, for the ILI9341 these are:

 Bit Function
 7   Mirror Y coordinate (row address order)
 6   Mirror X coordinate (column address order)
 5   Row/column exchange (for rotation)
 4   Refresh direction (top to bottom or bottom to top in portrait orientation)
 3   RGB order (swaps red and blue)
 2   Refresh direction (top to bottom or bottom to top in landscape orientation)
 1   Not used
 0   Not used

 The control register bits can be written with this example command sequence:
 
    tft.writecommand(TFT_MADCTL);
    tft.writedata(0x48);          // Bits 6 and 3 set
    
 0x48 is the default value for ILI9341 (0xA8 for ESP32 M5STACK)
 in rotation 0 orientation.
 
 Another control register can be used to "invert" colours,
 this swaps black and white as well as other colours (e.g.
 green to magenta, red to cyan, blue to yellow).
 
 To invert colours insert this line after tft.init() or tft.begin():

    tft.invertDisplay( invert ); // Where invert is true or false

*/

#include <SPI.h>
#include <TFT_eSPI.h>       // Hardware-specific library
// #include <Fonts/Custom/BebasNeue_Regular18pt7b.h>

void drawLogoTS();

TFT_eSPI tft = TFT_eSPI(); // Invoke custom library


void setup(void)
{
    Serial.begin(115200);

    tft.init();

    tft.fillScreen(TFT_BLACK);
    // tft.drawRect(0, 0, tft.width(), tft.height(), TFT_GREEN);

    // // Set "cursor" at top left corner of display (0,0) and select font 4
    // tft.setCursor(20, 40, 4);

    // // Set the font colour to be white with a black background
    // tft.setTextColor(TFT_WHITE);

    // // We can now plot text on screen using the "print" class
    // tft.println(" Initialised default\n");
    // tft.println(" White text");

    // tft.setTextColor(TFT_RED);
    // tft.println(" Red text");

    // tft.setTextColor(TFT_GREEN);
    // tft.println(" Green text");

    // tft.setTextColor(TFT_BLUE);
    // tft.println(" Blue text");

    // delay(5000);
    
}

void loop()
{
    drawLogoTS();


    // tft.invertDisplay(false); // Where i is true or false

    // tft.fillScreen(TFT_BLACK);
    // tft.drawRect(0, 0, tft.width(), tft.height(), TFT_GREEN);

    // tft.setCursor(20, 40, 4);

    // tft.setTextColor(TFT_WHITE);
    // tft.println(" Invert OFF\n");

    // tft.println(" White text");

    // tft.setTextColor(TFT_RED);
    // tft.println(" Red text");

    // tft.setTextColor(TFT_GREEN);
    // tft.println(" Green text");

    // tft.setTextColor(TFT_BLUE);
    // tft.println(" Blue text");

    // // delay(5000);

    // // Binary inversion of colours
    // tft.invertDisplay(true); // Where i is true or false

    // tft.fillScreen(TFT_BLACK);
    // tft.drawRect(0, 0, tft.width(), tft.height(), TFT_GREEN);

    // tft.setCursor(20, 40, 4);

    // tft.setTextColor(TFT_WHITE);
    // tft.println(" Invert ON\n");

    // tft.println(" White text");

    // tft.setTextColor(TFT_RED);
    // tft.println(" Red text");

    // tft.setTextColor(TFT_GREEN);
    // tft.println(" Green text");

    // tft.setTextColor(TFT_BLUE);
    // tft.println(" Blue text");

    // delay(5000);
}


void drawLogoTS() // TODO : Ajouter des fonctions pour dessiner le logo TS en Light Mode : tft.drawfillCircle()
{
    int16_t coordX = 17; // "T" coordX = 16
    int16_t coordY = 65; // "T" coordX = 65
    tft.setTextSize(7);

    int16_t coordX_ = 0;
    int16_t coordY_ = 0;

    // int16_t coordX = 31;  // "T" coordX = 16
    // int16_t coordY = 115; // "T" coordX = 65
    // tft.setTextSize(2);
    // // tft.setFont(&FreeSansBold9pt7b);    // Le meilleur à date
    // tft.setTextFont(&BebasNeue_Regular18pt7b.bitmap);

    uint16_t width = 42;  // "T" width = 42
    uint16_t height = 56; // "T" height = 56

    // tft.getTextBounds("R", coordX, coordY, &coordX_, &coordY_, &width, &height);
    // Serial.println("T");
    // Serial.print("coordX : ");
    // Serial.println(coordX);
    // Serial.print("coordY : ");
    // Serial.println(coordY);
    // Serial.print("coordX_ : ");
    // Serial.println(coordX_);
    // Serial.print("coordY_ : ");
    // Serial.println(coordY_);
    // Serial.print("width : ");
    // Serial.println(width);
    // Serial.print("height : ");
    // Serial.println(height);

    // width = 42;  // "T" width = 42
    // height = 56; // "T" height = 56

    int widthWithoutSpace = width * 0.80952381; // widthWithoutSpace = 42 * 0.80952381 = 34
    int heightWithoutSpace = height * 0.875;    // heightWithoutSpace = 56 * 0.875 = 49

    int coordY2 = coordY + height + 1; // "premier E" coordX = 122     // 65 + 56 = 121

    // Draw "TRA"
    tft.setTextColor(TFT_WHITE);
    tft.setCursor(coordX, coordY);
    tft.printf("%-3s", "TRA");
    // Draw "C" of "TRACK"
    tft.setTextColor(TFT_RED);
    tft.setCursor(coordX + width * 3, coordY);
    tft.printf("%-1s", "C");
    // Draw "K" of "TRACK"
    tft.setTextColor(TFT_WHITE);
    tft.setCursor(coordX + width * 4, coordY);
    tft.printf("%-1s", "K");

    // Draw special "S"
    tft.fillCircle(coordX + width * 0.761904762, coordY2 + (height * 0.160714286), 4, TFT_RED);
    tft.fillCircle(coordX + width * 0.547619048, coordY2 + (height * 0.053571429), 4, TFT_WHITE);
    tft.fillCircle(coordX + width * 0.285714286, coordY2 + (height * 0.089285714), 4, TFT_WHITE);
    tft.fillCircle(coordX + width * 0.142857143, coordY2 + (height * 0.250000000), 4, TFT_WHITE);
    tft.fillCircle(coordX + width * 0.309523810, coordY2 + (height * 0.392857143), 4, TFT_WHITE);
    tft.fillCircle(coordX + width * 0.523809524, coordY2 + (height * 0.500000000), 4, TFT_WHITE);
    tft.fillCircle(coordX + width * 0.714285714, coordY2 + (height * 0.642857143), 4, TFT_WHITE);
    tft.fillCircle(coordX + width * 0.547619048, coordY2 + (height * 0.803571429), 4, TFT_WHITE);
    tft.fillCircle(coordX + width * 0.285714286, coordY2 + (height * 0.839285714), 4, TFT_WHITE);
    tft.fillCircle(coordX + width * 0.095238095, coordY2 + (height * 0.714285714), 4, TFT_RED);

    // Draw "ENSE"
    tft.setTextColor(TFT_WHITE);
    tft.setCursor(coordX + width, coordY2);
    tft.printf("%-4s", "ENSE");

    // Draw circle
    // Comme le nombre de pixel est pair (240), le centre est entre 2 pixels. On ne peut pas mettre de fraction de pixel... Donc pour avoir un cercle centré, il faut dessiner 4 cercles...
    tft.drawCircle(119, 119, 120, TFT_WHITE); // Center X = 119.5 (0 to 239)    // Center Y = 119.5 (0 to 239)    // rayon = 120
    tft.drawCircle(120, 120, 120, TFT_WHITE); // Center X = 119.5 (0 to 239)    // Center Y = 119.5 (0 to 239)    // rayon = 120
    tft.drawCircle(119, 120, 120, TFT_WHITE); // Center X = 119.5 (0 to 239)    // Center Y = 119.5 (0 to 239)    // rayon = 120
    tft.drawCircle(120, 119, 120, TFT_WHITE); // Center X = 119.5 (0 to 239)    // Center Y = 119.5 (0 to 239)    // rayon = 120
}
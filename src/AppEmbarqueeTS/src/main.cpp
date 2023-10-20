#include <Arduino.h>
#include "Program.h"



void loopCore0(void *pvParameters); // forward declaration of the loopCore0 function

Program *program = nullptr;


void setup()
{
    Serial.end();
    Serial.begin(115200);

    program = new Program();

    xTaskCreatePinnedToCore(
        loopCore0,
        "loopCore0", // Name of the task
        5000,        // Stack size in words // À vérifier !!!
        NULL,        // Task input parameter
        100,         // Priority of the task
        NULL,        // Task handle.
        0            // Core where the task should run
    );
}

void loop()
{
    program->executeCore1();

    // delay(1000);
}

void loopCore0(void *pvParameters)
{
    while (true)
    {
        program->executeCore0();
        
        // delay(1000);
    }
}

/*

ESP32-WROVER-E-N16R8 16 MB (Quad SPI) 8 MB (Quad SPI) –40 ~ 85


abort() was called at PC 0x400f9518 on core 0


Backtrace: 0x400838d5:0x3ffbea6c |<-CORRUPTED

  #0  0x400838d5:0x3ffbea6c in panic_abort at /Users/ficeto/Desktop/ESP32/ESP32S2/esp-idf-public/components/esp_system/panic.c:408




ELF file SHA256: b49e8b8012d18ef0

Rebooting...
ets Jul 29 2019 12:21:46

rst:0xc (SW_CPU_RESET),boot:0x13 (SPI_FAST_FLASH_BOOT)
configsip: 0, SPIWP:0xee
clk_drv:0x00,q_drv:0x00,d_drv:0x00,cs0_drv:0x00,hd_drv:0x00,wp_drv:0x00
mode:DIO, clock div:2
load:0x3fff0030,len:1184
load:0x40078000,len:13232
load:0x40080400,len:3028
entry 0x400805e4
[   475][I][esp32-hal-psram.c:96] psramInit(): PSRAM enabled
Start Advertising
========SDCard Detect.======
SDCard Size: 30436MB
SDCard Ride Id find: bac33e05-187e-cc6a-9fea-37695630ec50
SDCard nb of rides: 1
SDCard nb of rides: 1
===========================
Initializing modem...
Modem is finally functional
Modem initialized.
Disabling GPS



*/
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
#include <Arduino.h>
#include "SDCard.h"
#ifdef TEST
    #include <gtest/gtest.h>
#endif

#define PIN_BAT 35 /* read battery voltage, Disabled when using USB - ONLY INPUT PIN */


float map_battery_voltage_to_percentage(float voltage, float min_voltage, float max_voltage, float min_percentage, float max_percentage);
void sortData(float data[], int size);
void read_bat();


SDCard *sdCard = new SDCard();
int _batteryPercentage = 0;
float _batteryVoltage = 0;
const int _voltageReads = 15; // number of voltage readings before choosing a median, keep this number odd
int vref = 1100;       // ADC reference voltage, change this to 1100 if using ESP32 ADC


void setup()
{
    Serial.begin(115200); // Start serial monitor at a baud rate of 9600
    delay(500);
    pinMode(PIN_BAT, INPUT);

    sdCard->init();

#ifdef TEST
    ::testing::InitGoogleTest();
#endif
}

void read_bat()
{ // reads and returns the battery voltage
    float voltageBuffer[_voltageReads];
    uint32_t Read_buffer = 0;

    for (int x = 0; x < _voltageReads; x++)
    {
        for (int i = 0; i < _voltageReads; i++)
        {
            voltageBuffer[i] = (uint32_t)analogRead(PIN_BAT);
        }
        sortData(voltageBuffer, _voltageReads);
        Read_buffer += (voltageBuffer[(_voltageReads - 1) / 2]);
    }

    // _batteryVoltage = (((float)(Read_buffer / _voltageReads) / 4096) * 3600 * 2) / 1000;
    _batteryVoltage= ((float)(Read_buffer / _voltageReads) / 4096.0) * 2.0 * 3.3 * (vref / 1000.0);
    _batteryPercentage = map_battery_voltage_to_percentage(_batteryVoltage, 3.0, 4.2, 0, 100); // get battery voltage as a percentage 0-100%
    
    if (_batteryPercentage < 0)
    {
        _batteryPercentage = 0;
    }

    if (_batteryPercentage > 100)
    {
        _batteryPercentage = 100;
    }
}

float map_battery_voltage_to_percentage(float voltage, float min_voltage, float max_voltage, float min_percentage, float max_percentage)
{
    return (voltage - min_voltage) * (max_percentage - min_percentage) / (max_voltage - min_voltage) + min_percentage;
}

void sortData(float data[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (data[j] > data[j + 1])
            {
                float temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }
}

void loop()
{
#ifdef TEST
    // Run tests
    if (RUN_ALL_TESTS())
        ;

    // sleep 1 sec
    delay(1000);
#endif

    static unsigned long last_time = 0;
    if (millis() - last_time >= 2000)
    {
        last_time = millis();
        read_bat();
        Serial.print("Battery Voltage : ");
        Serial.println(_batteryVoltage); // 2.5v - 4.2v
        Serial.print("Battery Percentage : ");
        Serial.print(_batteryPercentage);
        Serial.println("%"); // 0-100%

        sdCard->tick(_batteryVoltage, _batteryPercentage);
    }
}
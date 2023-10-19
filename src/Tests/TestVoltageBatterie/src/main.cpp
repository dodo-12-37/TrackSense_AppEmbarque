#include <Arduino.h>

#define PIN_BAT 35 /* read battery voltage, Disabled when using USB - ONLY INPUT PIN */



float map_battery_voltage_to_percentage(float voltage, float min_voltage, float max_voltage, float min_percentage, float max_percentage);
void sortData(float data[], int size);


int BP = 0;
float v_bat = 0;
const int VReads = 15; // number of voltage readings before choosing a median, keep this number odd

void setup()
{
    Serial.begin(115200); // Start serial monitor at a baud rate of 9600
    delay(500);
    pinMode(PIN_BAT, INPUT);
}

void read_bat()
{ // reads and returns the battery voltage
    float voltageBuffer[VReads];
    uint32_t Read_buffer = 0;
    for (int x = 0; x < VReads; x++)
    {
        for (int i = 0; i < VReads; i++)
        {
            voltageBuffer[i] = (uint32_t)analogRead(PIN_BAT);
        }
        sortData(voltageBuffer, VReads);
        Read_buffer += (voltageBuffer[(VReads - 1) / 2]);
    }
    v_bat = (((float)(Read_buffer / VReads) / 4096) * 3600 * 2) / 1000;
    BP = map_battery_voltage_to_percentage(v_bat, 2.5, 4.2, 0, 100); // get battery voltage as a percentage 0-100%
    if (BP < 0)
    {
        BP = 0;
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
    static unsigned long last_time = 0;
    if (millis() - last_time >= 5000)
    {
        last_time = millis();
        read_bat();
        Serial.print("Battery Voltage : ");
        Serial.println(v_bat); // 2.5v - 4.2v
        Serial.print("Battery Percentage : ");
        Serial.print(BP);
        Serial.println("%"); // 0-100%
    }
}
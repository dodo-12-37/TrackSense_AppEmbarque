#include <Arduino.h>
#include <LittleFS.h>

#include "ControlerConfigurationFile.h"
#include "Configurations.h"

#define FS LittleFS

String ControlerConfigurationFile::readFile()
{
    String content = String("");

    FS.begin(true);
    File file = FS.open(PATH_CONFIGURATION_FILE, "r");

    if (file)
    {
        Serial.println(String("ControlerConfigurationFile readFile Opened : ") + PATH_CONFIGURATION_FILE);

        while (file.available()) 
        {
            content += file.readString();
        }
    }

    Serial.println(String("ControlerConfigurationFile readFile read : ") + content);

    file.close();
    // FS.end();

    return content;
}

void ControlerConfigurationFile::writeFile(String const& content)
{
    FS.begin(true);
    File file = FS.open(PATH_CONFIGURATION_FILE, "w");

    if (file)
    {
        Serial.println(String("ControlerConfigurationFile writeFile Opened : ") + PATH_CONFIGURATION_FILE);
        file.println(content);
        Serial.println(String("ControlerConfigurationFile writeFile : ") + content);
    }

    file.close();
    // FS.end();
}

String ControlerConfigurationFile::getValue(String const& field)
{
    String content = ControlerConfigurationFile::readFile(); 

    DynamicJsonDocument configFileJson(DYNAMIQUE_JSON_DOCUMENT_SIZE);
    deserializeJson(configFileJson, content);

    return configFileJson[field];
}

void ControlerConfigurationFile::setValue(String const& field, String const& value)
{
    String content = ControlerConfigurationFile::readFile(); 

    Serial.println(String("ControlerConfigurationFile setValue read : ") + content);

    DynamicJsonDocument configFileJson(DYNAMIQUE_JSON_DOCUMENT_SIZE);
    deserializeJson(configFileJson, content);

    configFileJson[field] = value;

    String newContent = String("");
    serializeJson(configFileJson, newContent);

    Serial.println(String("ControlerConfigurationFile setValue content to write : ") + newContent);

    ControlerConfigurationFile::writeFile(newContent);
}
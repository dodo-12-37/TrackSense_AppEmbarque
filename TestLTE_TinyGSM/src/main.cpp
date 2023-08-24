/**
 * @file      Arduino_NetworkTest.ino
 * @author    Lewis He (lewishe@outlook.com)
 * @license   MIT
 * @copyright Copyright (c) 2023  Shenzhen Xin Yuan Electronic Technology Co., Ltd
 * @date      2023-02-01
 * @note      This example function is the SIM7000/SIM7070 network test to
 *            determine whether the module can access the network and obtain some access parameters
 */

// Set serial for debug console (to the Serial Monitor, default speed 115200)
#define SerialMon Serial

// Set serial for AT commands (to the module)
// Use Hardware Serial on Mega, Leonardo, Micro
#define SerialAT Serial1

#define TINY_GSM_MODEM_SIM7000
#define TINY_GSM_RX_BUFFER 1024 // Set RX buffer to 1Kb
#define SerialAT Serial1

// See all AT commands, if wanted
// #define DUMP_AT_COMMANDS

#include <TinyGsmClient.h>
#include <SPI.h>
#include <SD.h>
#include <Ticker.h>

#ifdef DUMP_AT_COMMANDS
#include <StreamDebugger.h>
StreamDebugger debugger(SerialAT, SerialMon);
TinyGsm modem(debugger);
#else
TinyGsm modem(SerialAT);
#endif

#define UART_BAUD 115200 //9600 //115200
#define PIN_DTR 25
#define PIN_TX 27
#define PIN_RX 26
#define PWR_PIN 4

#define SD_MISO 2
#define SD_MOSI 15
#define SD_SCLK 14
#define SD_CS 13
#define LED_PIN 12

void enableGPS(void)
{
    // Set Modem GPS Power Control Pin to HIGH, turn on GPS power
    // Only in version 20200415 is there a function to control GPS power
    modem.sendAT("+CGPIO=0,48,1,1");
    if (modem.waitResponse(10000L) != 1)
    {
        DBG("Set GPS Power HIGH Failed");
    }
    modem.enableGPS();
}

void disableGPS(void)
{
    // Set Modem GPS Power Control Pin to LOW ,turn off GPS power
    // Only in version 20200415 is there a function to control GPS power
    modem.sendAT("+CGPIO=0,48,1,0");
    if (modem.waitResponse(10000L) != 1)
    {
        DBG("Set GPS Power LOW Failed");
    }
    modem.disableGPS();
}

void modemPowerOn()
{
    pinMode(PWR_PIN, OUTPUT);
    digitalWrite(PWR_PIN, LOW);
    delay(1000); // Datasheet Ton mintues = 1S
    digitalWrite(PWR_PIN, HIGH);
}

void modemPowerOff()
{
    pinMode(PWR_PIN, OUTPUT);
    digitalWrite(PWR_PIN, LOW);
    delay(1500); // Datasheet Ton mintues = 1.2S
    digitalWrite(PWR_PIN, HIGH);
}

void setup()
{
    // Set console baud rate
    SerialMon.begin(115200);

    // Set LED OFF
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);

    modemPowerOn();

    SPI.begin(SD_SCLK, SD_MISO, SD_MOSI);
    if (!SD.begin(SD_CS))
    {
        Serial.println("> It looks like you haven't inserted the SD card..");
    }
    else
    {
        uint32_t cardSize = SD.cardSize() / (1024 * 1024);
        String str = "> SDCard Size: " + String(cardSize) + "MB";
        Serial.println(str);
    }

    // SD.mkdir("/test");

    SerialAT.begin(UART_BAUD, SERIAL_8N1, PIN_RX, PIN_TX);

    Serial.println("> Check whether Modem is online");
    // test modem is online ?
    uint32_t timeout = millis();
    while (!modem.testAT())
    {
        Serial.print(".");
        if (millis() - timeout > 60000)
        {
            Serial.println("> It looks like the modem is not responding, trying to restart");
            modemPowerOff();
            delay(5000);
            modemPowerOn();
            timeout = millis();
        }
    }
    Serial.println("\nModem is online");

    // test sim card is online ?
    timeout = millis();
    Serial.print("> Get SIM card status");
    while (modem.getSimStatus() != SIM_READY)
    {
        Serial.print(".");
        if (millis() - timeout > 60000)
        {
            Serial.println("It seems that your SIM card has not been detected. Has it been inserted?");
            Serial.println("If you have inserted the SIM card, please remove the power supply again and try again!");
            return;
        }
    }
    Serial.println();
    Serial.println("> SIM card exists");

    Serial.println("> /**********************************************************/");
    Serial.println("> Please make sure that the location has 2G/NB-IOT signal");
    Serial.println("> SIM7000/SIM707G does not support 4G network. Please ensure that the USIM card you use supports 2G/NB access");
    Serial.println("> /**********************************************************/");

    String res = modem.getIMEI();
    Serial.print("IMEI:");
    Serial.println(res);
    Serial.println();

    /*
     * Tips:
     * When you are not sure which method of network access is supported by the network you use,
     * please use the automatic mode. If you are sure, please change the parameters to speed up the network access
     * * * * */

    // Set mobile operation band
    modem.sendAT("+CBAND=ALL_MODE");
    modem.waitResponse();

    // Args:
    // 1 CAT-M
    // 2 NB-IoT
    // 3 CAT-M and NB-IoT
    // Set network preferre to auto
    uint8_t perferred = 3;
    modem.setPreferredMode(perferred);

    if (perferred == 2)
    {
        Serial.println("When you select 2, please ensure that your SIM card operator supports NB-IOT");
    }

    // Args:
    // 2 Automatic
    // 13 GSM only
    // 38 LTE only
    // 51 GSM and LTE only
    // Set network mode to auto
    modem.setNetworkMode(2);

    // Check network signal and registration information
    Serial.println("> SIM7000/SIM7070 uses automatic mode to access the network. The access speed may be slow. Please wait patiently");
    RegStatus status;
    timeout = millis();
    do
    {
        int16_t sq = modem.getSignalQuality();

        status = modem.getRegistrationStatus();

        if (status == REG_DENIED)
        {
            Serial.println("> The SIM card you use has been rejected by the network operator. Please check that the card you use is not bound to a device!");
            return;
        }
        else
        {
            Serial.print("Signal:");
            Serial.println(sq);
        }

        if (millis() - timeout > 360000)
        {
            if (sq == 99)
            {
                Serial.println("> It seems that there is no signal. Please check whether the"
                               "LTE antenna is connected. Please make sure that the location has 2G/NB-IOT signal\n"
                               "SIM7000G does not support 4G network. Please ensure that the USIM card you use supports 2G/NB access");
                return;
            }
            timeout = millis();
        }

        delay(800);
    } while (status != REG_OK_HOME && status != REG_OK_ROAMING);

    Serial.println("Obtain the APN issued by the network");
    modem.sendAT("+CGNAPN");
    if (modem.waitResponse(3000, res) == 1)
    {
        res = res.substring(res.indexOf(",") + 1);
        res.replace("\"", "");
        res.replace("\r", "");
        res.replace("\n", "");
        res.replace("OK", "");
        Serial.print("The APN issued by the network is:");
        Serial.println(res);
    }

    modem.sendAT("+CNACT=1");
    modem.waitResponse();

    // res = modem.getLocalIP();
    modem.sendAT("+CNACT?");
    if (modem.waitResponse("+CNACT: ") == 1)
    {
        modem.stream.read();
        modem.stream.read();
        res = modem.stream.readStringUntil('\n');
        res.replace("\"", "");
        res.replace("\r", "");
        res.replace("\n", "");
        modem.waitResponse();
        Serial.print("The current network IP address is:");
        Serial.println(res);
    }

    modem.sendAT("+CPSI?");
    if (modem.waitResponse("+CPSI: ") == 1)
    {
        res = modem.stream.readStringUntil('\n');
        res.replace("\r", "");
        res.replace("\n", "");
        modem.waitResponse();
        Serial.print("The current network parameter is:");
        Serial.println(res);
    }

    Serial.println("/**********************************************************/");
    Serial.println("After the network test is complete, please enter the  ");
    Serial.println("AT command in the serial terminal.");
    Serial.println("/**********************************************************/\n\n");
}

    float lat, lon, alt, speed;

void loop()
{
    while (SerialAT.available())
    {
        SerialMon.write(SerialAT.read());
        


        Serial.println();
        Serial.println("****************BATTERY*****************");
        Serial.print("Battery percent: ");
        Serial.print(modem.getBattPercent());
        Serial.println("%");

        modem.getGPS(&lat, &lon, &alt, &speed);

        Serial.println("****************GPS*****************");
        Serial.print("lat:");
        Serial.println(lat);
        Serial.print("lon:");
        Serial.println(lon);
        Serial.print("alt:");
        Serial.println(alt);
        Serial.print("speed:");
        Serial.println(speed);
        Serial.println("************************************");
        Serial.println();

    }
    while (SerialMon.available())
    {
        SerialAT.write(SerialMon.read());

    }
}














// /*
//   FILE: AllFunctions.ino
//   AUTHOR: Koby Hale
//   PURPOSE: Test functionality
// */

// #define TINY_GSM_MODEM_SIM7000
// #define TINY_GSM_RX_BUFFER 1024 // Set RX buffer to 1Kb
// #define SerialAT Serial1

// // See all AT commands, if wanted
// #define DUMP_AT_COMMANDS

// /*
//    Tests enabled
// */
// #define TINY_GSM_TEST_GPRS true
// #define TINY_GSM_TEST_GPS true
// #define TINY_GSM_POWERDOWN true

// // set GSM PIN, if any
// #define GSM_PIN ""

// // Your GPRS credentials, if any
// const char apn[] = "hologram"; // SET TO YOUR APN
// const char gprsUser[] = "";
// const char gprsPass[] = "";

// #include <TinyGsmClient.h>
// #include <SPI.h>
// #include <SD.h>
// #include <Ticker.h>

// #ifdef DUMP_AT_COMMANDS // if enabled it requires the streamDebugger lib
// #include <StreamDebugger.h>
// StreamDebugger debugger(SerialAT, Serial);
// TinyGsm modem(debugger);
// #else
// TinyGsm modem(SerialAT);
// #endif

// #define uS_TO_S_FACTOR 1000000ULL // Conversion factor for micro seconds to seconds
// #define TIME_TO_SLEEP 60          // Time ESP32 will go to sleep (in seconds)

// #define UART_BAUD 115200
// #define PIN_DTR 25
// #define PIN_TX 27
// #define PIN_RX 26
// #define PWR_PIN 4

// #define SD_MISO 2
// #define SD_MOSI 15
// #define SD_SCLK 14
// #define SD_CS 13
// #define LED_PIN 12

// int counter, lastIndex, numberOfPieces = 24;
// String pieces[24], input;

// void setup()
// {
//     // Set console baud rate
//     Serial.begin(115200);
//     delay(10);

//     // Set LED OFF
//     pinMode(LED_PIN, OUTPUT);
//     digitalWrite(LED_PIN, HIGH);

//     pinMode(PWR_PIN, OUTPUT);
//     digitalWrite(PWR_PIN, HIGH);
//     // Starting the machine requires at least 1 second of low level, and with a level conversion, the levels are opposite
//     delay(1000);
//     digitalWrite(PWR_PIN, LOW);

//     SPI.begin(SD_SCLK, SD_MISO, SD_MOSI, SD_CS);
//     if (!SD.begin(SD_CS))
//     {
//         Serial.println("SDCard MOUNT FAIL");
//     }
//     else
//     {
//         uint32_t cardSize = SD.cardSize() / (1024 * 1024);
//         String str = "SDCard Size: " + String(cardSize) + "MB";
//         Serial.println(str);
//     }

//     Serial.println("\nWait...");

//     delay(1000);

//     SerialAT.begin(UART_BAUD, SERIAL_8N1, PIN_RX, PIN_TX);

//     // Restart takes quite some time
//     // To skip it, call init() instead of restart()
//     Serial.println("Initializing modem...");
//     if (!modem.restart())
//     {
//         Serial.println("Failed to restart modem, attempting to continue without restarting");
//     }
// }

// void loop()
// {

//     // Restart takes quite some time
//     // To skip it, call init() instead of restart()
//     Serial.println("Initializing modem...");
//     if (!modem.init())
//     {
//         Serial.println("Failed to restart modem, attempting to continue without restarting");
//     }

//     String name = modem.getModemName();
//     delay(500);
//     Serial.println("Modem Name: " + name);

//     String modemInfo = modem.getModemInfo();
//     delay(500);
//     Serial.println("Modem Info: " + modemInfo);

//     // Set Modem GPS Power Control Pin to LOW ,turn off GPS power
//     // Only in version 20200415 is there a function to control GPS power
//     modem.sendAT("+CGPIO=0,48,1,0");
//     if (modem.waitResponse(10000L) != 1)
//     {
//         DBG("Set GPS Power LOW Failed");
//     }

// #if TINY_GSM_TEST_GPRS
//     // Unlock your SIM card with a PIN if needed
//     if (GSM_PIN && modem.getSimStatus() != 3)
//     {
//         modem.simUnlock(GSM_PIN);
//     }
// #endif

//     modem.sendAT("+CFUN=0");
//     if (modem.waitResponse(10000L) != 1)
//     {
//         DBG(" +CFUN=0  false ");
//     }
//     delay(200);

//     /*
//       2 Automatic
//       13 GSM only
//       38 LTE only
//       51 GSM and LTE only
//     * * * */

//     bool res = modem.setNetworkMode(2);
//     if (!res)
//     {
//         DBG("setNetworkMode  false ");
//         return;
//     }
//     delay(200);

//     /*
//       1 CAT-M
//       2 NB-Iot
//       3 CAT-M and NB-IoT
//     * * */
//     res = modem.setPreferredMode(3);
//     if (!res)
//     {
//         DBG("setPreferredMode  false ");
//         return;
//     }
//     delay(200);

//     /*AT+CBANDCFG=<mode>,<band>[,<band>…]
//      * <mode> "CAT-M"   "NB-IOT"
//      * <band>  The value of <band> must is in the band list of getting from  AT+CBANDCFG=?
//      * For example, my SIM card carrier "NB-iot" supports B8.  I will configure +CBANDCFG= "Nb-iot ",8
//      */
//     /* modem.sendAT("+CBANDCFG=\"NB-IOT\",8 ");
//      if (modem.waitResponse(10000L) != 1) {
//          DBG(" +CBANDCFG=\"NB-IOT\" ");
//      }
//      delay(200);*/

//     modem.sendAT("+CFUN=1");
//     if (modem.waitResponse(10000L) != 1)
//     {
//         DBG(" +CFUN=1  false ");
//     }
//     delay(200);

// #if TINY_GSM_TEST_GPRS

//     SerialAT.println("AT+CGDCONT?");
//     delay(500);
//     if (SerialAT.available())
//     {
//         input = SerialAT.readString();
//         for (int i = 0; i < input.length(); i++)
//         {
//             if (input.substring(i, i + 1) == "\n")
//             {
//                 pieces[counter] = input.substring(lastIndex, i);
//                 lastIndex = i + 1;
//                 counter++;
//             }
//             if (i == input.length() - 1)
//             {
//                 pieces[counter] = input.substring(lastIndex, i);
//             }
//         }
//         // Reset for reuse
//         input = "";
//         counter = 0;
//         lastIndex = 0;

//         for (int y = 0; y < numberOfPieces; y++)
//         {
//             for (int x = 0; x < pieces[y].length(); x++)
//             {
//                 char c = pieces[y][x]; // gets one byte from buffer
//                 if (c == ',')
//                 {
//                     if (input.indexOf(": ") >= 0)
//                     {
//                         String data = input.substring((input.indexOf(": ") + 1));
//                         if (data.toInt() > 0 && data.toInt() < 25)
//                         {
//                             modem.sendAT("+CGDCONT=" + String(data.toInt()) + ",\"IP\",\"" + String(apn) + "\",\"0.0.0.0\",0,0,0,0");
//                         }
//                         input = "";
//                         break;
//                     }
//                     // Reset for reuse
//                     input = "";
//                 }
//                 else
//                 {
//                     input += c;
//                 }
//             }
//         }
//     }
//     else
//     {
//         Serial.println("Failed to get PDP!");
//     }

//     Serial.println("\n\n\nWaiting for network...");
//     if (!modem.waitForNetwork())
//     {
//         delay(10000);
//         return;
//     }

//     if (modem.isNetworkConnected())
//     {
//         Serial.println("Network connected");
//     }

//     Serial.println("\n---Starting GPRS TEST---\n");
//     Serial.println("Connecting to: " + String(apn));
//     if (!modem.gprsConnect(apn, gprsUser, gprsPass))
//     {
//         delay(10000);
//         return;
//     }

//     Serial.print("GPRS status: ");
//     if (modem.isGprsConnected())
//     {
//         Serial.println("connected");
//     }
//     else
//     {
//         Serial.println("not connected");
//     }

//     String ccid = modem.getSimCCID();
//     Serial.println("CCID: " + ccid);

//     String imei = modem.getIMEI();
//     Serial.println("IMEI: " + imei);

//     String cop = modem.getOperator();
//     Serial.println("Operator: " + cop);

//     IPAddress local = modem.localIP();
//     Serial.println("Local IP: " + String(local));

//     int csq = modem.getSignalQuality();
//     Serial.println("Signal quality: " + String(csq));

//     SerialAT.println("AT+CPSI?"); // Get connection type and band
//     delay(500);
//     if (SerialAT.available())
//     {
//         String r = SerialAT.readString();
//         Serial.println(r);
//     }

//     Serial.println("\n---End of GPRS TEST---\n");
// #endif

// #if TINY_GSM_TEST_GPRS
//     modem.gprsDisconnect();
//     if (!modem.isGprsConnected())
//     {
//         Serial.println("GPRS disconnected");
//     }
//     else
//     {
//         Serial.println("GPRS disconnect: Failed.");
//     }
// #endif

// #if TINY_GSM_TEST_GPS
//     Serial.println("\n---Starting GPS TEST---\n");
//     // Set Modem GPS Power Control Pin to HIGH ,turn on GPS power
//     // Only in version 20200415 is there a function to control GPS power
//     modem.sendAT("+CGPIO=0,48,1,1");
//     if (modem.waitResponse(10000L) != 1)
//     {
//         DBG("Set GPS Power HIGH Failed");
//     }

//     modem.enableGPS();

//     float lat, lon;
//     while (1)
//     {
//         if (modem.getGPS(&lat, &lon))
//         {
//             Serial.printf("lat:%f lon:%f\n", lat, lon);
//             break;
//         }
//         else
//         {
//             Serial.print("getGPS ");
//             Serial.println(millis());
//         }
//         delay(2000);
//     }
//     modem.disableGPS();

//     // Set Modem GPS Power Control Pin to LOW ,turn off GPS power
//     // Only in version 20200415 is there a function to control GPS power
//     modem.sendAT("+CGPIO=0,48,1,0");
//     if (modem.waitResponse(10000L) != 1)
//     {
//         DBG("Set GPS Power LOW Failed");
//     }

//     Serial.println("\n---End of GPRS TEST---\n");
// #endif

// #if TINY_GSM_POWERDOWN
//     // Try to power-off (modem may decide to restart automatically)
//     // To turn off modem completely, please use Reset/Enable pins
//     modem.sendAT("+CPOWD=1");
//     if (modem.waitResponse(10000L) != 1)
//     {
//         DBG("+CPOWD=1");
//     }
//     modem.poweroff();
//     Serial.println("Poweroff.");
// #endif

//     esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
//     delay(200);
//     esp_deep_sleep_start();

//     Serial.println("This will never be printed");
// }

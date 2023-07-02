#include <Arduino.h>
#include <BluetoothSerial.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <cstdlib>
#include <string>

// Definition des UUID /////////////////////////////////////////////////////////////////////
#define SERVICE_TEST_UUID                   "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_TEST_UUID            "beb5483e-36e1-4688-b7f5-ea07361b26a8"
#define DESCRIPTOR_TEST_UUID                "beb5483e-36e1-4688-b7f5-ea07361b26a9"
#define SERVICE_BATTERY_UUID                BLEUUID((u_int16_t)0x180F)  // Norme définie
#define CHARACTERISTIC_BATTERY_LEVEL_UUID   BLEUUID((u_int16_t)0x2A19)  // Norme définie
#define DESCRIPTOR_BATTERY_LEVEL_UUID       BLEUUID((u_int16_t)0x2901)  // Norme définie (valeur en %)
////////////////////////////////////////////////////////////////////////////////////////////

BLEService* serviceTest;
BLEService* serviceBattery;
BLEServer* serverBLE;
BLEScan* scanBLE;

BLECharacteristic* characteristicTest;
BLECharacteristic* characteristicBattery;

bool deviceConnected = false;

// Callbacks du serveurBLE lors de la connexion et de la déconnexion
class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* p_server) {
      deviceConnected = true;
      Serial.println("Connecte");
    }

    void onDisconnect(BLEServer* p_server) {
        deviceConnected = false;
        Serial.println("Deconnecte");
    }
};
///////////////////////////////////////////////////////////////////////////////////////////

// Callbacks du serviceTest lors de l'écriture, de la lecture et de l'envoie d'une notification
class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string value = pCharacteristic->getValue();

      if (value.length() > 0) {
        Serial.println("*********");
        Serial.print("Ecriture : ");
        for (int i = 0; i < value.length(); i++) {
          Serial.print(value[i]);
        }  

        Serial.println();
        Serial.println("*********");
      }
    }

    void onRead(BLECharacteristic *pCharacteristic) {
      std::string value = pCharacteristic->getValue();

      if (value.length() > 0) {
        Serial.println("*********");
        Serial.print("Lecture : ");
        for (int i = 0; i < value.length(); i++) {
          Serial.print(value[i]);
        }

        Serial.println();
        Serial.println("*********");
      }
    }

    void onNotify(BLECharacteristic* pCharacteristic) {
      std::string value = pCharacteristic->getValue();

      if (value.length() > 0) {
        Serial.println("*********");
        Serial.print("Notification : ");
        for (int i = 0; i < value.length(); i++) {
          Serial.print(value[i]);
        }

        Serial.println();
        Serial.println("*********");
      }
    }
};
/////////////////////////////////////////////////////////////////////////////////////////

// Callbacks du scan des clients ////////////////////////////////////////////////////////
class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    if (advertisedDevice.haveServiceUUID()) {
      Serial.println("Resultat du callback sur le scan : ");
      BLEAddress add = advertisedDevice.getAddress();
      Serial.print("Adresse : ");
      Serial.println(add.toString().c_str());
    }
  }
};
/////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  Serial.begin(115200);
  Serial.println("Bienvenue dans le test Bluetooth !");

  String name = "CoucouESP";

  Serial.println("Initialisation du Bluetooth...");
  BLEDevice::init(name.c_str());
  Serial.println("Initialisation terminee !");
  Serial.println(String("Nom du peripherique : ") + String(name));

  Serial.println("Creation et configuration du serveur...");
  serverBLE = BLEDevice::createServer();
  Serial.println("Configuration des callback...");
  serverBLE->setCallbacks(new MyServerCallbacks());
  Serial.println("Serveur cree !");
  
  Serial.println("Creation des services...");
  serviceTest = serverBLE->createService(SERVICE_TEST_UUID);
  serviceBattery = serverBLE->createService(SERVICE_BATTERY_UUID);
  Serial.println("Services crees !");

  Serial.println("Creation des caraceristiques...");
  characteristicTest = new BLECharacteristic(CHARACTERISTIC_TEST_UUID, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_NOTIFY);
  characteristicBattery = new BLECharacteristic(CHARACTERISTIC_BATTERY_LEVEL_UUID, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
  Serial.println("Definition des valeurs...");
  characteristicTest->setValue("Hello World");
  uint32_t level = 0;
  characteristicBattery->setValue(level);
  Serial.println("Configuration des callback...");
  characteristicTest->setCallbacks(new MyCallbacks());
  Serial.println("Creation des caraceristiques terminee !");

  Serial.println("Creation des descripteurs...");
  BLEDescriptor* descriptorTest = new BLEDescriptor(DESCRIPTOR_TEST_UUID);
  BLEDescriptor* descriptorBattery = new BLEDescriptor(DESCRIPTOR_BATTERY_LEVEL_UUID);
  Serial.println("Definition des valeurs...");
  descriptorTest->setValue("Test ESP32");
  descriptorBattery->setValue("Pourcentage 0 - 100");
  Serial.println("Creation des descripteurs terminee !");
  
  Serial.println("Ajout des descripteurs aux caracteristiques...");
  characteristicTest->addDescriptor(descriptorTest);
  characteristicBattery->addDescriptor(descriptorBattery);
  Serial.println("Ajout des descripteur aux caracteristiques termine !");

  Serial.println("Ajout des characeristiques aux services...");
  serviceTest->addCharacteristic(characteristicTest);
  serviceBattery->addCharacteristic(characteristicBattery);
  Serial.println("Ajout des characeristiques aux services termine !");

  Serial.println("Lancement des services...");
  serviceTest->start();
  serviceBattery->start();
  Serial.println("Services lances !");

  Serial.println("Configuration de la publicite...");
  BLEAdvertising* advertising = BLEDevice::getAdvertising();
  advertising->addServiceUUID(SERVICE_TEST_UUID);
  advertising->addServiceUUID(SERVICE_BATTERY_UUID);
  advertising->setScanResponse(true);
  advertising->setMinPreferred(0x06);
  advertising->setMaxPreferred(0x12);
  Serial.println("Configuration de la publicite teminee !");


  Serial.println("Configuration du scan...");
  scanBLE = BLEDevice::getScan();  
  scanBLE->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  scanBLE->setActiveScan(true);
  scanBLE->setInterval(100);
  scanBLE->setWindow(99);
  Serial.println("Configuration du scan terminee !");

  Serial.println("Lancement du serveur...");
  advertising->start();
  Serial.println("Serveur lance !");

} 

void loop() {

  if (deviceConnected) {
    BLEScanResults foundDevices = scanBLE->start(1, false);
    int nbApp = foundDevices.getCount();
    Serial.print("Nombre d'appareils connectes : ");
    Serial.println(nbApp);

    Serial.println("Details des appareils : ");
    for (int i = 0; i < nbApp; ++i)
    {
      BLEAdvertisedDevice client = foundDevices.getDevice(i);
      Serial.print(i + 1);
      Serial.print(" - ");
      Serial.println(client.toString().c_str());
    }
    
    scanBLE->clearResults();

    characteristicTest->setValue("Hello World");
    characteristicTest->notify();

    std::string message = characteristicBattery->getValue();
    int level = atoi(message.c_str());
    level += 1;

    characteristicBattery->setValue(level);
    characteristicBattery->notify();
  } else {
    serverBLE->startAdvertising();
  }

  delay(2000);
}


// BluetoothSerial BT;

// void setup() {
//   Serial.begin(115200);
//   Serial.println("Bienvenue dans le test Bluetooth !");

//   String name = "CoucouESP";
//   const char* pin = "1234";

//   Serial.println("Initialisation du BluetoothSerial : ");
//   BT.begin(name);
//   BT.setPin(pin);
//   Serial.println("Initialisation terminee !");
//   Serial.println(String("Nom du periferique : ") + String(name));

//   Serial.println("************************");
//   Serial.println("En attente d'une connexion...");

//   while (!BT.connected())
//   {
//     Serial.print(".");
//     delay(1000);
//   }
  
//   Serial.println();

//   if (BT.connected())
//   {
//     Serial.println("Connexion reussie !");

//     String addressBT = BT.getBtAddressString();
//     Serial.println(String("Adresse de ") + name + String(" : ") + addressBT);

//     if (BT.hasClient())
//     {  
//       Serial.println("L'appareil connecte a l'ESP est client");
//     }
//     else
//     {
//       Serial.println("L'appareil connecte a l'ESP n'est pas client");
//     }
//   }
// }

// void loop() {
// }

// #if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
// #error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
// #endif

// #if !defined(CONFIG_BT_SPP_ENABLED)
// #error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
// #endif

// BluetoothSerial SerialBT;

// #define BT_DISCOVER_TIME	10000

// static bool btScanAsync = true;
// static bool btScanSync = false;


// void btAdvertisedDeviceFound(BTAdvertisedDevice* pDevice) {
// 	Serial.printf("Appareil trouve de maniere asychrone : %s\n", pDevice->toString().c_str());
// }

// void setup() {
//   Serial.begin(115200);
//   SerialBT.begin("AsyncESP"); //Bluetooth device name
//   Serial.println("The device started, now you can pair it with bluetooth!");

//   if (btScanAsync) {
//     Serial.println("Starting discoverAsync...");
//     if (SerialBT.discoverAsync(btAdvertisedDeviceFound)) {
//       Serial.println("Findings will be reported in \"btAdvertisedDeviceFound\"");
//       delay(10000);
//       Serial.print("Stopping discoverAsync... ");
//       SerialBT.discoverAsyncStop();
//       Serial.println("stopped");
//     } else {
//       Serial.println("Error on discoverAsync f.e. not workin after a \"connect\"");
//     }
//   }
  
//   if (btScanSync) {
//     Serial.println("Starting discover...");
//     BTScanResults *pResults = SerialBT.discover(BT_DISCOVER_TIME);
//     if (pResults)
//       pResults->dump(&Serial);
//     else
//       Serial.println("Error on BT Scan, no result!");
//   }
// }

// void loop() {
//   delay(100);
// }
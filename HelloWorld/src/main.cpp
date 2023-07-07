#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLESecurity.h>
#include <BLE2902.h>
#include <cstdlib>
#include <string>

#define SERVICE_USER_UUID                   "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_USERNAME_UUID        "beb5483e-36e1-4688-b7f5-ea07361b26a8"
#define DESCRIPTOR_USERNAME_UUID            "beb5483e-36e1-4688-b7f5-ea07361b26a9"

BLEServer* serverBLE;
BLEService* serviceUser;
BLECharacteristic* characteristicUserName;
String serverName = "TrackSense";
uint32_t pin = 123456;

bool deviceConnected = false;

class ServerBLECallbacks
  : public BLEServerCallbacks 
{
  void onConnect(BLEServer* p_server) 
  {
    deviceConnected = true;
    Serial.println("Connecte");
  }

  void onDisconnect(BLEServer* p_server) 
  {
    deviceConnected = false;
    Serial.println("Deconnecte");
  }
};

class ServiceUserCallbacks
  : public BLECharacteristicCallbacks 
{
  void onWrite(BLECharacteristic *pCharacteristic) 
  {
    std::string value = pCharacteristic->getValue();

    if (value.length() > 0) {
      Serial.println("*********");
      Serial.print("Ecriture : ");
      for (int i = 0; i < value.length(); i++) 
      {
        Serial.print(value[i]);
      }  

      Serial.println();
      Serial.println("*********");
    }
  }

  void onRead(BLECharacteristic *pCharacteristic) 
  {
    std::string value = pCharacteristic->getValue();

    if (value.length() > 0) {
      Serial.println("*********");
      Serial.print("Lecture : ");
      for (int i = 0; i < value.length(); i++) 
      {
        Serial.print(value[i]);
      }

      Serial.println();
      Serial.println("*********");
    }
  }

  void onNotify(BLECharacteristic* pCharacteristic) 
  {
    std::string value = pCharacteristic->getValue();

    if (value.length() > 0) {
      Serial.println("*********");
      Serial.print("Notification : ");
      for (int i = 0; i < value.length(); i++) 
      {
        Serial.print(value[i]);
      }

      Serial.println();
      Serial.println("*********");
    }
  }
};

class SecurityBLECallbacks 
  : public BLESecurityCallbacks 
{
  uint32_t onPassKeyRequest(){
    Serial.println("PassKeyRequest!");
    return pin;
  }

  void onPassKeyNotify(uint32_t pass_key){
    Serial.println("On passkey Notify!");
  }

  bool onSecurityRequest(){
    Serial.println("On Security Request!");
    return true;
  }

  void onAuthenticationComplete(esp_ble_auth_cmpl_t cmpl){
    
    Serial.println(String("Mode d'authentification : ") + String(cmpl.auth_mode));
    BLEAddress add = cmpl.bd_addr;
    serverBLE->addPeerDevice(&add, true, 0);
    Serial.println(String("Adresse du client : ") + String(add.toString().c_str()));
    Serial.println(String("Cle presente : ") + String(cmpl.key_present));
    Serial.println(String("Type de cle : ") + String(cmpl.key_type));
    Serial.println(String("Authentification reussie : ") + String(cmpl.success));

    if(cmpl.success){
      Serial.println("onAuthenticationComplete!");
    } else {
      Serial.println("onAuthentication not Complete!");
      Serial.println(String("Numero de l'erreur : ") + String(cmpl.fail_reason));
    }
  }

  bool onConfirmPIN(uint32_t p_pin){
    Serial.println("onConfirmPIN!");
    return true;
  }
};

void setup() {
  Serial.begin(115200);
  Serial.println("Bienvenue dans votre TrackSense !");

  Serial.println("Lancement du Bluetooth...");
  BLEDevice::init(serverName.c_str());
  Serial.println("Bluetooth lancé !");
  Serial.println(String("Votre TrackSense est visible sous le nom de \"") + String(serverName) + String("\""));

  Serial.println("Creation et configuration du serveur...");
  serverBLE = BLEDevice::createServer();
  serverBLE->setCallbacks(new ServerBLECallbacks());
  Serial.println("Serveur cree !");

  Serial.println("Initialisation de la securite du serveur...");
  BLESecurity* securityBLE = new BLESecurity();
  securityBLE->setStaticPIN(pin);
  securityBLE->setAuthenticationMode(ESP_LE_AUTH_REQ_SC_BOND);
  BLEDevice::setSecurityCallbacks(new SecurityBLECallbacks());
  Serial.println("Initialisation de la securite du serveur terminee !");
  
  Serial.println("Creation du service User...");
  serviceUser = serverBLE->createService(SERVICE_USER_UUID);
  Serial.println("Service User cree !");

  Serial.println("Creation de la caracteristique UserName en Read, Write et Notify...");
  characteristicUserName = new BLECharacteristic(CHARACTERISTIC_USERNAME_UUID, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_NOTIFY);
  characteristicUserName->setValue("Pierre-Francois");
  Serial.println("Configuration des callback...");
  characteristicUserName->setCallbacks(new ServiceUserCallbacks());
  Serial.println("Creation de la  caraceristique UserName terminee !");

  Serial.println("Creation du descripteur UserName...");
  BLEDescriptor* descriptorUserName = new BLEDescriptor(DESCRIPTOR_USERNAME_UUID);
  descriptorUserName->setValue("Nom");
  Serial.println("Creation du descripteur UserName terminee !");
  
  Serial.println("Ajout du descripteur a la caracteristique...");
  characteristicUserName->addDescriptor(descriptorUserName);
  Serial.println("Ajout du descripteur a la caracteristique termine !");

  Serial.println("Ajout de la caracteristique UserName au service User...");
  serviceUser->addCharacteristic(characteristicUserName);
  Serial.println("Ajout de la caracteristique UserName au service User termine !");

  Serial.println("Lancement du service User...");
  serviceUser->start();
  Serial.println("Service User lance !");

  Serial.println("Configuration de la publicite...");
  BLEAdvertising* advertising = BLEDevice::getAdvertising();
  advertising->addServiceUUID(SERVICE_USER_UUID);
  Serial.println("Configuration de la publicite teminee !");

  Serial.println("Lancement du serveur...");
  advertising->start();
  Serial.println("Serveur lance !");
} 

void loop() {

  if (!deviceConnected) 
  {
    serverBLE->startAdvertising();
  }

  delay(2000);
}
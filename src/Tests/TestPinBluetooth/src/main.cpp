#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLESecurity.h>

String name = "CoucouESP";
uint32_t pin = 123456; // Doit être de 6 chiffres
BLEServer* serverBLE;

bool deviceConnected = false;

// Callbacks du serveurBLE lors de la connexion et de la déconnexion //////////////////////
class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* p_server) {
      deviceConnected = true;
      Serial.println("Connecte");
    }

    void onDisconnect(BLEServer* p_server) {
        deviceConnected = false;
        serverBLE->removePeerDevice(0, true);
        Serial.println("Deconnecte");
    }
};
///////////////////////////////////////////////////////////////////////////////////////////

// Callbacks du securityBLE ///////////////////////////////////////////////////////////////
class MySecurity : public BLESecurityCallbacks {

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
      uint16_t length;
      esp_ble_gap_get_whitelist_size(&length); // Ajout à la liste blanche
      // serverBLE->connect(add);
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
///////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  Serial.begin(115200);
  Serial.println("Bienvenue dans le test Bluetooth !");

  Serial.println("Initialisation du Bluetooth...");
  BLEDevice::init(name.c_str());
  Serial.println("Initialisation de la securite...");
  BLESecurity* sec = new BLESecurity();
  sec->setStaticPIN(pin);
  sec->setAuthenticationMode(ESP_LE_AUTH_REQ_SC_BOND);
  BLEDevice::setSecurityCallbacks(new MySecurity());
  
  Serial.println("Initialisation de la securite terminee !");
  Serial.println("Initialisation du Bluetotth terminee !");
  Serial.println(String("Nom du peripherique : ") + String(name));
  Serial.println(String("Code pin : ") + String(pin));

  Serial.println("Creation et configuration du serveur...");
  serverBLE = BLEDevice::createServer();
  Serial.println("Configuration des callback...");
  serverBLE->setCallbacks(new MyServerCallbacks());
  Serial.println("Serveur cree !");

  serverBLE->startAdvertising();
}

void loop() {
  uint32_t numberDevices = serverBLE->getConnectedCount();
  uint16_t connectionID = serverBLE->getConnId();

  Serial.println(String("ID de la connexion : ") + String(connectionID));

  if (numberDevices == 0) {
    Serial.println("Pas d'appareil connecte, on relance la publicite !");
    serverBLE->startAdvertising();
  } else {
    Serial.println(String("Nombre d'appareils connectes : ") + String(numberDevices));

    std::map<uint16_t, conn_status_t> peerDevices = serverBLE->getPeerDevices(true);

    for (const auto& entry : peerDevices) {
      uint16_t connId = entry.first;
      conn_status_t connStatus = entry.second;
      
      if (connStatus.connected) {
        BLEClient* client = static_cast<BLEClient*>(connStatus.peer_device);
        Serial.println(String("Details du client : ") + String(client->toString().c_str()));
        Serial.println(String("ID de la connexion client : ") + String(client->getConnId()));  
        client->getConnId();
        Serial.println(String("Adresse du serveur : ") + String(client->getPeerAddress().toString().c_str()));
      }
    }
  }

  delay(5000);
}

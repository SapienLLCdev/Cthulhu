/*
An ESP32 BLE program that can be uploaded to an esp32 wroom32 module (dev kit c in our case)
that when paired with your smartphone and enabled/selected in the komoot app, 
will print directions to the serial monitor. This is designed to be modified to be used with 
esp32 or arduino based navigation hardware, such as bicycle or dashboard mounted displays
or wearable clothing or devices with naviagation capabilities. 

Currently, to get the system to work, you must first upload the BLE_uart example found here https://github.com/nkolban/ESP32_BLE_Arduino/blob/b232e7f5f0e87f36afbc2f4e03a2c49c48dd47bc/examples/BLE_uart/BLE_uart.ino
then pair the device to your phone in bluetooth settings (it will show up as UART Service), then upload this program to your esp32.

Following these two steps, open the komoot app, go to profile>settings>bluetooth connect, click any of the options (different smart bicycles)
click 'connect' when 'UART Service' appears. Once you see the checkmark next to UART Service, you can exit into the navigation settings
and begin a route. Once your route begins, you should see directions printed onto your serial terminal.

JJ Moritz, 
Sapien LLC 
Jan 2019


Adapted from example code written by nkolban and chegewara taken from the ESP32_BLE_Arduino library by nkolban on github

komoot app referrence can be found here
https://github.com/komoot/BLEConnect#data_distance

ESP32 Arduino cores can be found here
https://github.com/espressif/arduino-esp32
*/




#include "BLEDevice.h"
//#include "BLEScan.h"
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

// The remote service we wish to connect to.
static BLEUUID serviceUUID("71c1e128-d92f-4fa8-a2b2-0f171db3436c");  //this is the service from Komoot
// The characteristic of the remote service we are interested in.
static BLEUUID    charUUID("503DD605-9BCB-4F6E-B235-270A57483026");  //this is our characteristic of the komoot service 

static BLEAddress *pServerAddress;
static boolean doConnect = false;
static boolean connected = false;
static BLERemoteCharacteristic* pRemoteCharacteristic;



bool connectToServer(BLEAddress pAddress) {
    Serial.print("Forming a connection to ");
    Serial.println(pAddress.toString().c_str());
    
    BLEClient*  pClient  = BLEDevice::createClient();
    Serial.println(" - Created client");

    // Connect to the remove BLE Server.
    pClient->connect(pAddress);
    Serial.println(" - Connected to server");

    // Obtain a reference to the service we are after in the remote BLE server.
    BLERemoteService* pRemoteService = pClient->getService(serviceUUID);
    if (pRemoteService == nullptr) {
      Serial.print("Failed to find our service UUID: ");
      Serial.println(serviceUUID.toString().c_str());
      return false;
    }
    Serial.println(" - Found our service");


    // Obtain a reference to the characteristic in the service of the remote BLE server.
    pRemoteCharacteristic = pRemoteService->getCharacteristic(charUUID);
    if (pRemoteCharacteristic == nullptr) {
      Serial.print("Failed to find our characteristic UUID: ");
      Serial.println(charUUID.toString().c_str());
      return false;
    }
    Serial.println(" - Found our characteristic");

}
/**
 * Scan for BLE servers and find the first one that advertises the service we are looking for.
 */
class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
 /**
   * Called for each advertising BLE server.
   */
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    Serial.print("BLE Advertised Device found: ");
    Serial.println(advertisedDevice.toString().c_str());

    // We have found a device, let us now see if it contains the service we are looking for.
    if (advertisedDevice.haveServiceUUID() && advertisedDevice.getServiceUUID().equals(serviceUUID)) {

      // 
      Serial.print("Found our device!  address: "); 
      advertisedDevice.getScan()->stop();

      pServerAddress = new BLEAddress(advertisedDevice.getAddress());
      doConnect = true;

    } // Found our server
  } // onResult
}; // MyAdvertisedDeviceCallbacks



BLEServer *pServer = NULL;
BLECharacteristic * pTxCharacteristic;
bool deviceConnected = false;
bool oldDeviceConnected = false;
uint8_t txValue = 0;

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID           "6E400001-B5A3-F393-E0A9-E50E24DCCA9E" // UART service UUID
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"


class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};

class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string rxValue = pCharacteristic->getValue();

      if (rxValue.length() > 0) {
        Serial.println("*********");
        Serial.print("Received Value: ");
        for (int i = 0; i < rxValue.length(); i++)
          Serial.print(rxValue[i]);

        Serial.println();
        Serial.println("*********");
      }
    }
};

void setup() {
  Serial.begin(115200);
  Serial.println("Starting Arduino BLE Client application...");
  BLEDevice::init("Cthulhu_Nav_Module");

  // Retrieve a Scanner and set the callback we want to use to be informed when we
  // have detected a new device.  Specify that we want active scanning and start the
  // scan to run for 30 seconds.
  BLEScan* pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true);
  pBLEScan->start(30);

  // Create the BLE Server
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Create the BLE Service
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Create a BLE Characteristic
  pTxCharacteristic = pService->createCharacteristic(
                    CHARACTERISTIC_UUID_TX,
                    BLECharacteristic::PROPERTY_NOTIFY
                  );
                      
  pTxCharacteristic->addDescriptor(new BLE2902());

  BLECharacteristic * pRxCharacteristic = pService->createCharacteristic(
                       CHARACTERISTIC_UUID_RX,
                      BLECharacteristic::PROPERTY_WRITE
                    );

  pRxCharacteristic->setCallbacks(new MyCallbacks());

  // Start the service
  pService->start();

  // Start advertising
  pServer->getAdvertising()->start();
  Serial.println("Waiting a client connection to notify...");

  
} // End of setup.


// This is the Arduino main loop function.
void loop() {

  // If the flag "doConnect" is true then we have scanned for and found the desired
  // BLE Server with which we wish to connect.  Now we connect to it.  Once we are 
  // connected we set the connected flag to be true.
  if (doConnect == true) {
    if (connectToServer(*pServerAddress)) {
      Serial.println("We are now connected to the BLE Server.");
      delay(10000);
      connected = true;
    } else {
      Serial.println("We have failed to connect to the server; there is nothin more we will do.");
    }
    doConnect = false;
  }

    // disconnecting
//    if (!deviceConnected && oldDeviceConnected) {
//        delay(500); // give the bluetooth stack the chance to get things ready
//        pServer->startAdvertising(); // restart advertising
//        Serial.println("start advertising");
//        oldDeviceConnected = deviceConnected;
//    }
//    // connecting
//    if (deviceConnected && !oldDeviceConnected) {
//    // do stuff here on connecting
//        oldDeviceConnected = deviceConnected;
//    }


    
  if (connected) {



        std::string rxValue = pRemoteCharacteristic->readValue();

      if (rxValue.length() > 0) {
       // Serial.println("*********");
       // Serial.print("Received Value: ");
//
//                for (int i = 0; i < 4; i++)
//          Serial.write(byte(rxValue[i]));//Serial.print(",");//instruction identifier (unique number given to each instruction)
//          for (int i = 4; i < 5; i++)
//          Serial.write(byte(rxValue[i]));//Serial.print(",");//direction, see table https://github.com/komoot/BLEConnect#data_distance
//          for (int i = 5; i < 9; i++)
//          Serial.write(byte(rxValue[i]));//Serial.print(","); // Distance in meters, appears to be LSB first (38m prints as 38000)
        for (int i = 0; i < rxValue.length(); i++)
          Serial.write(rxValue[i]);                         //Street Name, we are not using this right now

        //Serial.write(0);
        //Serial.println("*********");
      }

  }
  
  delay(1000); // Delay a second between loops.
} // End of loop

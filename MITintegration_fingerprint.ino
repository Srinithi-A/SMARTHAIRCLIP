#include <Adafruit_Fingerprint.h>
#include <HardwareSerial.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

// Fingerprint sensor setup
HardwareSerial mySerial(2); 
Adafruit_Fingerprint finger(&mySerial);
const int FINGER_ID = 1;  int matchCount = 0;

// BLE setup
#define SERVICE_UUID        
#define CHARACTERISTIC_UUID

BLEServer *pServer = NULL;
BLECharacteristic *pCharacteristic = NULL;

void setup() {
  Serial.begin(115200);
  mySerial.begin(57600, SERIAL_8N1, 16, 17); 

  Serial.println("⏳ Initializing fingerprint sensor...");
  finger.begin(57600);
  if (finger.verifyPassword()) {
    Serial.println("✅ Fingerprint sensor detected");
  } else {
    Serial.println("❌ Sensor not found. Check wiring and ID!");
    while (1);
  }

  finger.LEDcontrol(FINGERPRINT_LED_ON); 

  // BLE setup
  BLEDevice::init("SOS_HairClip");
  Serial.print("BLE MAC: ");
  Serial.println(BLEDevice::getAddress().toString().c_str());

  pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);

  pCharacteristic = pService->createCharacteristic(
    CHARACTERISTIC_UUID,
    BLECharacteristic::PROPERTY_NOTIFY
  );

  pCharacteristic->addDescriptor(new BLE2902());
  pService->start();

  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->start();

  Serial.println("✅ BLE Advertising as SOS_HairClip");
  Serial.println("👉 Place pinky 3 times to trigger SOS...");
}

void loop() {
  static bool waitingForFingerLift = false;

  if (waitingForFingerLift) {
    if (finger.getImage() == FINGERPRINT_NOFINGER) {
      waitingForFingerLift = false;
    }
    return;    }

  if (finger.getImage() != FINGERPRINT_OK) return;
  if (finger.image2Tz() != FINGERPRINT_OK) return;
  if (finger.fingerSearch() != FINGERPRINT_OK) return;

  if (finger.fingerID == FINGER_ID) {
    matchCount++;
    Serial.print("✅ Match detected: ");
    Serial.println(matchCount);

    waitingForFingerLift = true; 

    if (matchCount >= 3) {
      Serial.println("🚨 SOS ALERT! Sending BLE...");
      pCharacteristic->setValue("SOS_TRIGGERED");
      pCharacteristic->notify();
      matchCount = 0;  // Reset count after SOS
    }
  }
}


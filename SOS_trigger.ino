#include <Adafruit_Fingerprint.h>
#include <HardwareSerial.h>

HardwareSerial mySerial(2);
Adafruit_Fingerprint finger(&mySerial);

const int FINGER_ID = 1;  // ID to match
int matchCount = 0;

void setup() {
  Serial.begin(115200);
  mySerial.begin(57600, SERIAL_8N1, 16, 17);  // TX=17, RX=16

  Serial.println("⏳ Initializing fingerprint sensor...");
  finger.begin(57600);
  if (finger.verifyPassword()) {
    Serial.println("✅ Fingerprint sensor detected");
  } else {
    Serial.println("❌ Sensor not found. Check wiring");
    while (true);
  }

  finger.LEDcontrol(FINGERPRINT_LED_ON);  // Always scanning
  Serial.println(" Place registered finger 3 times to trigger SOS...");
}

void loop() {
  if (finger.getImage() != FINGERPRINT_OK) return;
  if (finger.image2Tz() != FINGERPRINT_OK) return;
  if (finger.fingerSearch() != FINGERPRINT_OK) return;

  if (finger.fingerID == FINGER_ID) {
    matchCount++;
    Serial.print("Match detected ");
    Serial.println(matchCount);

    while (finger.getImage() != FINGERPRINT_NOFINGER);  

    if (matchCount >= 3) {
      Serial.println("🚨 SOS ALERT 🚨");
      matchCount = 0;  
    }
  }
}

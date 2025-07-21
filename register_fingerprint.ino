
#include <Adafruit_Fingerprint.h>
#include <HardwareSerial.h>

// UART2: GPIO16 (RX2), GPIO17 (TX2)
HardwareSerial mySerial(2);
Adafruit_Fingerprint finger(&mySerial);

const int FINGER_ID = 1;

void setup() {
  Serial.begin(115200);
  mySerial.begin(57600, SERIAL_8N1, 16, 17);  // R307 default baud rate

  delay(1000);
  Serial.println("⏳ Initializing fingerprint sensor...");

  finger.begin(57600);
  if (finger.verifyPassword()) {
    Serial.println("✅ Fingerprint sensor detected");
  } else {
    Serial.println("❌ Fingerprint sensor not found. Check wiring.");
    while (true) delay(1);
  }

  finger.LEDcontrol(FINGERPRINT_LED_ON);  // Turn blue LED on (continuous scan mode)

  Serial.println("👉 Place your finger to register...");
  enrollFinger(FINGER_ID);
}

void loop() {
  
}

// ===== Function to enroll a fingerprint =====
void enrollFinger(uint8_t id) {
  int p = -1;

  Serial.println("[1] Waiting for valid finger to enroll...");
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    if (p == FINGERPRINT_OK) {
      Serial.println("✔️ Finger captured");
    } else if (p == FINGERPRINT_NOFINGER) {
      // wait
    } else {
      Serial.println("❌ Error capturing image");
    }
  }

  p = finger.image2Tz(1);
  if (p != FINGERPRINT_OK) {
    Serial.println("❌ Error converting image");
    return;
  }

  Serial.println("✋ Remove finger...");
  delay(2000);
  while (finger.getImage() != FINGERPRINT_NOFINGER);

  Serial.println("[2] Place the same finger again...");
  while ((p = finger.getImage()) != FINGERPRINT_OK);

  p = finger.image2Tz(2);
  if (p != FINGERPRINT_OK) {
    Serial.println("❌ Error converting second image");
    return;
  }

  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    Serial.println("✅ Fingerprint matched!");
  } else {
    Serial.println("❌ Fingerprints do not match");
    return;
  }

  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
    Serial.println("🎉 Fingerprint enrolled successfully!");
    finger.LEDcontrol(FINGERPRINT_LED_OFF);  // Turn off LED after enroll
  } else {
    Serial.println("❌ Failed to store fingerprint");
  }
}

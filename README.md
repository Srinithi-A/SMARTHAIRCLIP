# SMARTHAIRCLIP
A IoT project made a smart hair clip poc using ESP32 and R307 Fingerprint sensor.
This project was built as part of our internship at **IIITDM Kancheepuram**, aimed at designing a **compact, wearable, and smart safety device** for women's safety Developed by **me and my teammate**, this Smart Hair Clip uses fingerprint recognition and IoT integration to trigger **SOS alerts in emergency situations and send the emergency alert to the emergency contact.**

# 💡 Project Ideation

While researching women's safety tech, we found that **no existing solution used a hair accessory** as a stealthy wearable. So we envisioned a **“Smart Hair Clip”** that can:
- Trigger alerts with just **3 taps** of a **registered fingerprint**
- Use **GPS + BLE/Wi-Fi** to send emergency messages
- Stay **discreet, accessible, and wearable** at all times
  
# Key Features
-🔒 Fingerprint detection (3 taps to trigger alert)
-📍 Location tracking via GPS/Phone
-📡 BLE + Wi-Fi hybrid alert system
-📱 Android app integration using MIT App Inventor
  
  # 📌 Tech Stack

### 🔧 Hardware:
- ESP32 Wroom Dev Kit  
- R307 Fingerprint Sensor  
- Vibration Motor   

### 💻 Software:
- Arduino IDE / PlatformIO – ESP32 Programming  
- MIT App Inventor – Android App (BLE & Location-based actions)

 ### 📱 App Features:

-GPS tracking
-SMS/WhatsApp alerts
-BLE control
-Map navigation
-Hybrid BLE + Wi-Fi for indoor/outdoor flexibility

# How it Works
1.User taps their registered pinky fingerprint 3 times
2.ESP32 triggers BLE signal → MIT App receives
3.App fetches phone’s GPS location
4.App sends SOS alert via WhatsApp/SMS to saved contacts and nearby police station

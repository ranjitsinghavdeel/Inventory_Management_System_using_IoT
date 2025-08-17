#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN D4  // RFID SS pin
#define RST_PIN D3 // RFID RST pin

MFRC522 rfid(SS_PIN, RST_PIN);

// Replace with your WiFi credentials
#define WIFI_SSID "Ashay"
#define WIFI_PASSWORD "ashay2006"

// Replace with your Firebase credentials
#define FIREBASE_HOST "https://inventory-management-using-iot-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "CQF7N6bzmq4bzrB6GMV2F23fPhJ3CmBY4dcVjR"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

void setup() {
    Serial.begin(115200);
    SPI.begin();
    rfid.PCD_Init();
    Serial.print("RFID Version: ");
    Serial.println(rfid.PCD_ReadRegister(MFRC522::VersionReg), HEX);

    // Connect to WiFi
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(1000);
    }
    Serial.println("\nConnected to WiFi!");

    // Firebase setup
    config.host = FIREBASE_HOST;
    config.signer.tokens.legacy_token = FIREBASE_AUTH;
    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);

    Serial.println("RFID scanner ready!");
}

void loop() {
    if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
        return;
    }

    // Get RFID UID
    String uid = "";
    for (byte i = 0; i < rfid.uid.size; i++) {
        uid += String(rfid.uid.uidByte[i], HEX);
    }
    uid.toUpperCase();
    Serial.println("Card UID: " + uid);

    // Check Firebase for last entry
    String path = "/RFID_Logs/" + uid + "/status";
    String lastStatus;
    if (Firebase.getString(fbdo, path)) {
        lastStatus = fbdo.stringData();
    } else {
        lastStatus = "OUT"; // Default to OUT if not found
    }

    // Determine new status
    String newStatus = (lastStatus == "OUT") ? "IN" : "OUT";

    // Update Firebase
    Firebase.setString(fbdo, path, newStatus);
    Firebase.setString(fbdo, "/RFID_Logs/" + uid + "/timestamp", String(millis()));

    Serial.println("Updated Status: " + newStatus);

    // Stop RFID scanning until next card
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
}

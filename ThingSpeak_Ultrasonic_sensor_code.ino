#include <WiFi.h>
#include <HTTPClient.h>
#include <ThingSpeak.h>

// Replace with your WiFi credentials
const char* ssid = "Ashay";
const char* password = "ashay2006";

// Replace with your ThingSpeak Write API Key
const char* server = "http://api.thingspeak.com/update";
const char* apiKey = "WY1FYBWU9AH1VH11";  // Replace this

// Ultrasonic sensor pins
#define TRIG_PIN 5
#define ECHO_PIN 18

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected!");
  
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  // Trigger the ultrasonic sensor
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read the echo pin
  long duration = pulseIn(ECHO_PIN, HIGH);
  float distance = duration * 0.034 / 2;  // cm

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Send data to ThingSpeak
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = String(server) + "?api_key=" + apiKey + "&field1=" + String(distance);
    
    http.begin(url);
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      Serial.print("Data sent to ThingSpeak. Response code: ");
      Serial.println(httpResponseCode);
    } else {
      Serial.print("Error sending data. Code: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  } else {
    Serial.println("WiFi not connected!");
  }

  delay(15000);  // ThingSpeak allows updates every 15 seconds
}

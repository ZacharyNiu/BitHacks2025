#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);  // ESP-NOW requires station mode
  wifi.begin();
  delay(100);
  
  Serial.println("ESP32 Receiver MAC Address:");
  Serial.println(WiFi.macAddress());
}

void loop() {
  // Nothing here
}


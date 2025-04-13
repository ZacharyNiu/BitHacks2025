// ✅ ESP-NOW VERSION: Send analog value from one ESP32-S3 to another
#include <esp_now.h>
#include <WiFi.h>

#define ANALOG_PIN 4

// Replace with the MAC address of the RECEIVER ESP32
uint8_t receiverMAC[] = {0x8C, 0xBF, 0xEA, 0x03, 0xB2, 0x00};  // Example MAC

esp_now_peer_info_t peerInfo;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  if (esp_now_init() != ESP_OK) {
    Serial.println("❌ ESP-NOW init failed");
    return;
  }

  memcpy(peerInfo.peer_addr, receiverMAC, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("❌ Failed to add peer");
    return;
  }

  Serial.println("✅ ESP-NOW Sender Ready");
}

void loop() {
  int val = analogRead(ANALOG_PIN);
  esp_now_send(receiverMAC, (uint8_t *)&val, sizeof(val));
  Serial.printf("📤 Sent analog value: %d\n", val);
  delay(200);
} 

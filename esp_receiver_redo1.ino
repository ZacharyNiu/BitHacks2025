#include <esp_now.h>
#include <WiFi.h>

void onReceive(const esp_now_recv_info_t *info, const uint8_t *incomingData, int len) {
  int receivedVal;
  memcpy(&receivedVal, incomingData, sizeof(receivedVal));
  Serial.printf("📥 Received analog value: %d\n", receivedVal);
}

void setup() {
  Serial.begin(115200);
  Serial.println("🔌 Booting Receiver...");

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  Serial.println("📶 WiFi set to STA + disconnected");

  if (esp_now_init() != ESP_OK) {
    Serial.println("❌ ESP-NOW init failed");
    return;
  }

  Serial.println("✅ ESP-NOW initialized");

  esp_now_register_recv_cb(onReceive);
  Serial.println("✅ ESP-NOW Receiver Ready 🚦");
}

void loop() {
  // Receiver runs on callback — nothing needed here!
}

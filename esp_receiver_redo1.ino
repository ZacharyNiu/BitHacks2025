#include <esp_now.h>
#include <WiFi.h>

void onReceive(const esp_now_recv_info_t *info, const uint8_t *incomingData, int len) {
  int receivedVal;
  memcpy(&receivedVal, incomingData, sizeof(receivedVal));
  Serial.printf("📥 Received analog value: %d\n", receivedVal);
}

void setup() {
  pinMode(12, OUTPUT);
  pinMode(11,OUTPUT);

  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  
  Serial.begin(115200);
  delay(500);
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
  int sensorValue = receivedVal;
  delay(50);  // Fast enough to catch spikes

  int motorSpeed = receivedVal/50; //converting sensorValue to motor speed

  //Motors Control
  analogWrite(12, 0);
  analogWrite(11, motorSpeed);
  
  analogWrite(10, 0);
  analogWrite(9, motorSpeed);
}

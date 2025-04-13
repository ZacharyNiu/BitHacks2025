#include <esp_now.h>

/*typedef struct struct_message {
  int vibrationValue;
} struct_message;

struct_message incomingData;

void onDataRecv(const uint8_t * mac, const uint8_t *incomingDataRaw, int len) {
  memcpy(&incomingData, incomingDataRaw, sizeof(incomingData));
  Serial.print("Vibration Received: ");
  Serial.println(incomingData.vibrationValue);
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_recv_cb(onDataRecv);
}

void loop() {
  // Nothing here! ESP-NOW handles the rest in the background
}*/
#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);  // ESP-NOW requires station mode
  Serial.println("ESP32 Receiver MAC Address:");
  Serial.println(WiFi.macAddress());
}

void loop() {
  // Nothing here
}


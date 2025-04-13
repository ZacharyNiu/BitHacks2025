#define VIBRATION_PIN 4  // ADC-capable pin

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Live Vibration Sensor Values:");
}

void loop() {
  int sensorValue = analogRead(VIBRATION_PIN);
  Serial.println(sensorValue);  // Just print the value only
  delay(50);  // Fast enough to catch spikes
}

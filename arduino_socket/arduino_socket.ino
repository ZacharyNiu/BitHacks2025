#include <WiFi.h>
#include <WebSocketsServer.h>
#include <driver/ledc.h>  // Required for LEDC functions

// Motor pins
#define ENA_GPIO 13    // PWM for Motor A
#define IN1_GPIO 12    // Direction 1
#define IN2_GPIO 11    // Direction 2

#define ENB_GPIO 10    // PWM for Motor B
#define IN3_GPIO 9     // Direction 3
#define IN4_GPIO 46    // Direction 4 (changed from 8 to 46)

// LEDC configuration for ESP32-S3
#define PWM_CHANNEL_A LEDC_CHANNEL_0
#define PWM_CHANNEL_B LEDC_CHANNEL_1
#define PWM_TIMER LEDC_TIMER_0
#define PWM_MODE LEDC_LOW_SPEED_MODE  // Required for ESP32-S3
#define PWM_FREQ 5000                 // 5kHz
#define PWM_RESOLUTION LEDC_TIMER_8_BIT  // 8-bit resolution

WebSocketsServer webSocket = WebSocketsServer(81);

void setupPWM() {
  // Configure Timer
  ledc_timer_config_t timer_conf = {
    .speed_mode = PWM_MODE,
    .duty_resolution = PWM_RESOLUTION,
    .timer_num = PWM_TIMER,
    .freq_hz = PWM_FREQ,
    .clk_cfg = LEDC_AUTO_CLK
  };
  ledc_timer_config(&timer_conf);

  // Configure Channels
  ledc_channel_config_t channel_conf_A = {
    .gpio_num = ENA_GPIO,
    .speed_mode = PWM_MODE,
    .channel = PWM_CHANNEL_A,
    .timer_sel = PWM_TIMER,
    .duty = 0,
    .hpoint = 0
  };
  ledc_channel_config(&channel_conf_A);

  ledc_channel_config_t channel_conf_B = {
    .gpio_num = ENB_GPIO,
    .speed_mode = PWM_MODE,
    .channel = PWM_CHANNEL_B,
    .timer_sel = PWM_TIMER,
    .duty = 0,
    .hpoint = 0
  };
  ledc_channel_config(&channel_conf_B);
}

void setup() {
  Serial.begin(115200);

  // Configure motor pins
  pinMode(IN1_GPIO, OUTPUT);
  pinMode(IN2_GPIO, OUTPUT);
  pinMode(IN3_GPIO, OUTPUT);
  pinMode(IN4_GPIO, OUTPUT);

  // Set fixed direction (forward)
  digitalWrite(IN1_GPIO, HIGH);
  digitalWrite(IN2_GPIO, LOW);
  digitalWrite(IN3_GPIO, HIGH);
  digitalWrite(IN4_GPIO, LOW);

  // Initialize PWM
  setupPWM();

  // Connect to WiFi
  WiFi.begin("ZAWG 5136", "1138j@V4");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());


  if(WiFi.status() == WL_CONNECTED) {
    Serial.println("Initializing WebSocket...");
    webSocket.begin();
    webSocket.onEvent(webSocketEvent);
    Serial.println("Websocket server started!!!!");
  } else{
    Serial.println("failed");
  }
  

}

void loop() {
  webSocket.loop();
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length) {
  if (type == WStype_TEXT) {
    int speed = String((char*)payload).toInt();
    speed = constrain(speed, 0, 100);
    int duty = (speed * 255) / 100;  // Convert % to 8-bit duty cycle
    
    ledc_set_duty(PWM_MODE, PWM_CHANNEL_A, duty);
    ledc_update_duty(PWM_MODE, PWM_CHANNEL_A);
    
    ledc_set_duty(PWM_MODE, PWM_CHANNEL_B, duty);
    ledc_update_duty(PWM_MODE, PWM_CHANNEL_B);
    
    Serial.printf("Speed: %d%% (Duty: %d)\n", speed, duty);
  }
}
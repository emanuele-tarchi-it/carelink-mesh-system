#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <espnow.h>
#include <Wire.h>

#include "carelink_protocol.h"
#include "config.h"
#include "storage.h"

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ============================================================
//  OLED
// ============================================================
Adafruit_SSD1306 display(128, 64, &Wire);

// Config
CareLinkConfig config;

// MAC del Gateway
uint8_t gatewayMac[6];

// ============================================================
//  Invia SOS al Gateway
// ============================================================
void sendSOS() {
    carelink_msg_t msg;

    strcpy(msg.bed_id, config.bed_id);
    msg.timestamp = millis();
    msg.bpm = 0;
    msg.spo2 = 0;
    msg.temperature = 0;
    msg.shock_index = 0;
    msg.alert_type = ALERT_SOS;

    esp_now_send(gatewayMac, (uint8_t*)&msg, sizeof(msg));
}

// ============================================================
//  OLED
// ============================================================
void showMessage(const char *text) {
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 20);
    display.print(text);
    display.display();
}

// ============================================================
//  SETUP
// ============================================================
void setup() {
    Serial.begin(115200);
    Wire.begin();

    // OLED
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();
    display.display();

    // Config
    loadConfig(config);

    // Parse MAC
    sscanf(config.nurse_mac, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
           &gatewayMac[0], &gatewayMac[1], &gatewayMac[2],
           &gatewayMac[3], &gatewayMac[4], &gatewayMac[5]);

    // WiFi + ESP-NOW
    WiFi.mode(WIFI_STA);
    if (esp_now_init() != 0) {
        showMessage("ESP-NOW ERR");
        return;
    }

    showMessage("Ready");
}

// ============================================================
//  LOOP
// ============================================================
void loop() {
    // Premere il pulsante fisico (GPIO0)
    if (digitalRead(0) == LOW) {
        showMessage("SOS SENT");
        sendSOS();
        delay(1000);
        showMessage("Ready");
    }

    delay(50);
}
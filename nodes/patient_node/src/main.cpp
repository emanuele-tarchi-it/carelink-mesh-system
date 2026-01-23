#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <espnow.h>
#include <Wire.h>

#include <SparkFun_MAX30205.h>      // Temperatura
#include "algorithm.h"              // Algoritmo Maxim
#include "carelink_protocol.h"      // Protocollo v0.4

#include "config.h"
#include "storage.h"

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ============================================================
//  OLED
// ============================================================
Adafruit_SSD1306 display(128, 64, &Wire);

// ============================================================
//  Sensori
// ============================================================
MAX30205 tempSensor;

#define BUFFER_SIZE 100
uint32_t irBuffer[BUFFER_SIZE];
uint32_t redBuffer[BUFFER_SIZE];

int32_t spo2;
int8_t validSPO2;
int32_t heartRate;
int8_t validHeartRate;

// ============================================================
//  Variabili cliniche v0.4
// ============================================================
uint16_t current_hr = 0;
uint8_t current_spo2 = 0;
float current_temp = 0.0;
float current_shock = 0.0;

uint8_t current_alert = ALERT_NORM;

// ACK
volatile bool ack_received = false;

// Config
CareLinkConfig config;

// ============================================================
//  CALLBACK ESP-NOW (ACK)
// ============================================================
void onDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
    if (len == sizeof(carelink_ack_t)) {
        carelink_ack_t ack;
        memcpy(&ack, incomingData, sizeof(ack));
        if (ack.ok == 1) {
            ack_received = true;
        }
    }
}

// ============================================================
//  Lettura PPG
// ============================================================
void readPPG() {
    for (int i = 0; i < BUFFER_SIZE; i++) {
        while (!maxim_max30102_read_fifo(&redBuffer[i], &irBuffer[i])) {
            // attesa campione valido
        }
    }
}

void processPPG() {
    maxim_heart_rate_and_oxygen_saturation(
        irBuffer, BUFFER_SIZE,
        redBuffer,
        &spo2, &validSPO2,
        &heartRate, &validHeartRate
    );

    if (validHeartRate && validSPO2) {
        current_hr = (uint16_t)heartRate;
        current_spo2 = (uint8_t)spo2;
    } else {
        current_hr = 0;
        current_spo2 = 0;
    }
}

// ============================================================
//  Lettura sensori (v0.4)
// ============================================================
void readSensors() {
    // Temperatura
    float t = tempSensor.readTemperature();
    if (t > 30.0 && t < 45.0) {
        current_temp = t;
    } else {
        current_temp = 0.0;
    }

    // PPG
    readPPG();
    processPPG();

    // Shock index
    if (current_hr > 0 && current_spo2 > 0) {
        current_shock = (float)current_hr / (float)current_spo2;
    } else {
        current_shock = 0.0;
    }
}

// ============================================================
//  Alert clinici v0.4
// ============================================================
void computeAlerts() {
    current_alert = ALERT_NORM;

    // Shock
    if (current_shock > 1.0) {
        current_alert = ALERT_SHOCK;
        return;
    }

    // Infezione
    if (current_temp > 37.8 && current_hr > 100) {
        current_alert = ALERT_INFECTION;
        return;
    }
}

// ============================================================
//  Telemetria + ACK (v0.4)
// ============================================================
void sendTelemetry() {
    carelink_msg_t msg;

    strcpy(msg.bed_id, config.bed_id);
    msg.timestamp = millis();
    msg.bpm = current_hr;
    msg.spo2 = current_spo2;
    msg.temperature = current_temp;
    msg.shock_index = current_shock;
    msg.alert_type = current_alert;

    uint8_t nurseMac[6];
    sscanf(config.nurse_mac, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
           &nurseMac[0], &nurseMac[1], &nurseMac[2],
           &nurseMac[3], &nurseMac[4], &nurseMac[5]);

    const int MAX_RETRIES = 3;
    ack_received = false;

    for (int attempt = 0; attempt < MAX_RETRIES; attempt++) {

        esp_now_send(nurseMac, (uint8_t*)&msg, sizeof(msg));

        unsigned long start = millis();
        while (millis() - start < 150) {
            if (ack_received) {
                Serial.println("ACK received");
                return;
            }
        }

        Serial.println("No ACK, retrying...");
    }

    Serial.println("Telemetry failed after retries");
}

// ============================================================
//  OLED
// ============================================================
void updateOLED() {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

    display.setCursor(0, 0);
    display.printf("Bed %s", config.bed_id);

    display.setCursor(0, 12);
    display.printf("HR: %d", current_hr);

    display.setCursor(0, 24);
    display.printf("SpO2: %d", current_spo2);

    display.setCursor(0, 36);
    display.printf("Temp: %.1f", current_temp);

    display.setCursor(0, 48);
    display.printf("sSI: %.2f", current_shock);

    display.display();
}

// ============================================================
//  SETUP
// ============================================================
void setup() {
    Serial.begin(115200);
    Wire.begin();

    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();
    display.display();

    loadConfig(config);

    WiFi.mode(WIFI_STA);
    if (esp_now_init() != 0) {
        Serial.println("ESP-NOW init failed");
    }
    esp_now_register_recv_cb(onDataRecv);

    if (!tempSensor.begin()) {
        Serial.println("MAX30205 not detected!");
    }

    if (!maxim_max30102_init()) {
        Serial.println("MAXREFDES117 not detected!");
    }
}

// ============================================================
//  LOOP
// ============================================================
void loop() {
    readSensors();
    computeAlerts();
    sendTelemetry();
    updateOLED();
    delay(1000);
}
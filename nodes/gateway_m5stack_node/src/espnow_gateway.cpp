#include "espnow_gateway.h"
#include "telemetry_buffer.h"
#include "storage_sd.h"
#include <esp_now.h>
#include <WiFi.h>
#include <M5Stack.h>

void onDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {

    if (len != sizeof(carelink_msg_t)) {
        return;
    }

    carelink_msg_t msg;
    memcpy(&msg, incomingData, sizeof(msg));

    // 1. Aggiorna buffer storico
    updateTelemetry(msg);

    // 2. Log su SD
    logTelemetry(msg);

    // (Dashboard e grafico si aggiornano da soli tramite main.cpp)
}

void initESPNow() {
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();

    if (esp_now_init() != ESP_OK) {
        M5.Lcd.setCursor(10, 200);
        M5.Lcd.setTextSize(2);
        M5.Lcd.setTextColor(RED);
        M5.Lcd.print("ESP-NOW init failed");
        M5.Lcd.setTextColor(WHITE);
        return;
    }

    esp_now_register_recv_cb(onDataRecv);

    M5.Lcd.setCursor(10, 180);
    M5.Lcd.setTextSize(1);
    M5.Lcd.setTextColor(GREEN);
    M5.Lcd.print("ESP-NOW OK");
    M5.Lcd.setTextColor(WHITE);
}

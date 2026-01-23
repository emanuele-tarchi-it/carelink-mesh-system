#include "ui_dashboard.h"
#include "telemetry_buffer.h"
#include <M5Stack.h>

// Icona ALERT grande (32x32)
static const unsigned char PROGMEM icon_alert_big[] = {
  0x00,0x00,0x18,0x3C,0x7E,0xDB,0xDB,0xDB,
  0xDB,0xDB,0x7E,0x3C,0x18,0x00,0x00,0x00,
  0x00,0x00,0x18,0x3C,0x7E,0xDB,0xDB,0xDB,
  0xDB,0xDB,0x7E,0x3C,0x18,0x00,0x00,0x00
};

void uiDashboardInit() {
    M5.Lcd.fillScreen(BLACK);
}

static const char* alertToString(uint8_t a) {
    switch (a) {
        case ALERT_SOS:       return "SOS";
        case ALERT_INFECTION: return "INFECTION";
        case ALERT_SHOCK:     return "SHOCK";
        default:              return "NORMAL";
    }
}

static uint16_t alertColor(uint8_t a) {
    switch (a) {
        case ALERT_SOS:       return RED;
        case ALERT_INFECTION: return YELLOW;
        case ALERT_SHOCK:     return ORANGE;
        default:              return GREEN;
    }
}

void uiDashboardLoop() {
    const carelink_msg_t *msg = getLatestAlertingMessage();

    M5.Lcd.fillScreen(BLACK);

    if (!msg) {
        M5.Lcd.setCursor(20, 20);
        M5.Lcd.setTextSize(3);
        M5.Lcd.print("No Alerts");
        return;
    }

    // Bed ID
    M5.Lcd.setTextSize(3);
    M5.Lcd.setCursor(10, 10);
    M5.Lcd.printf("Bed %s", msg->bed_id);

    // Icona alert
    M5.Lcd.drawBitmap(10, 60, icon_alert_big, 32, 32, alertColor(msg->alert_type));

    // Alert type
    M5.Lcd.setCursor(60, 60);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setTextColor(alertColor(msg->alert_type));
    M5.Lcd.printf("%s", alertToString(msg->alert_type));
    M5.Lcd.setTextColor(WHITE);

    // BPM
    M5.Lcd.setCursor(60, 90);
    M5.Lcd.printf("HR: %d", msg->bpm);

    // SpO2
    M5.Lcd.setCursor(60, 120);
    M5.Lcd.printf("SpO2: %d", msg->spo2);

    // Temp
    M5.Lcd.setCursor(60, 150);
    M5.Lcd.printf("Temp: %.1f", msg->temperature);

    // Shock Index
    M5.Lcd.setCursor(60, 180);
    M5.Lcd.printf("sSI: %.2f", msg->shock_index);
}
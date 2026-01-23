#include "ui_graph.h"
#include "telemetry_buffer.h"
#include <M5Stack.h>

// Dimensioni grafico
static const int GRAPH_X = 20;
static const int GRAPH_Y = 40;
static const int GRAPH_W = 280;
static const int GRAPH_H = 160;

// Range valori
static const int HR_MIN = 40;
static const int HR_MAX = 160;

static const int SPO2_MIN = 80;
static const int SPO2_MAX = 100;

static const float TEMP_MIN = 34.0;
static const float TEMP_MAX = 41.0;

static const float SSI_MIN = 0.0;
static const float SSI_MAX = 2.0;

// ============================================================
//  Inizializzazione grafico
// ============================================================
void uiGraphInit(const String &bed_id) {
    M5.Lcd.fillScreen(BLACK);

    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(10, 10);
    M5.Lcd.printf("Bed %s - Trend", bed_id.c_str());

    // Assi
    M5.Lcd.drawRect(GRAPH_X, GRAPH_Y, GRAPH_W, GRAPH_H, WHITE);

    // Legenda
    M5.Lcd.setTextSize(1);

    M5.Lcd.setCursor(10, 210);
    M5.Lcd.setTextColor(RED);
    M5.Lcd.print("HR");

    M5.Lcd.setCursor(60, 210);
    M5.Lcd.setTextColor(BLUE);
    M5.Lcd.print("SpO2");

    M5.Lcd.setCursor(120, 210);
    M5.Lcd.setTextColor(YELLOW);
    M5.Lcd.print("Temp");

    M5.Lcd.setCursor(180, 210);
    M5.Lcd.setTextColor(GREEN);
    M5.Lcd.print("sSI");

    M5.Lcd.setTextColor(WHITE);
}

// ============================================================
//  Funzioni di mapping
// ============================================================
static int mapHR(int hr) {
    hr = constrain(hr, HR_MIN, HR_MAX);
    return GRAPH_Y + GRAPH_H - map(hr, HR_MIN, HR_MAX, 0, GRAPH_H);
}

static int mapSpO2(int spo2) {
    spo2 = constrain(spo2, SPO2_MIN, SPO2_MAX);
    return GRAPH_Y + GRAPH_H - map(spo2, SPO2_MIN, SPO2_MAX, 0, GRAPH_H);
}

static int mapTemp(float t) {
    t = constrain(t, TEMP_MIN, TEMP_MAX);
    return GRAPH_Y + GRAPH_H - map(t * 10, TEMP_MIN * 10, TEMP_MAX * 10, 0, GRAPH_H);
}

static int mapSSI(float s) {
    s = constrain(s, SSI_MIN, SSI_MAX);
    return GRAPH_Y + GRAPH_H - map(s * 100, SSI_MIN * 100, SSI_MAX * 100, 0, GRAPH_H);
}

// ============================================================
//  Loop grafico
// ============================================================
void uiGraphLoop(const String &bed_id) {
    const TelemetryHistory *hist = getHistoryForBed(bed_id);
    if (!hist || hist->count == 0) {
        M5.Lcd.setCursor(20, 120);
        M5.Lcd.setTextSize(2);
        M5.Lcd.print("No data");
        return;
    }

    // Cancella area grafico
    M5.Lcd.fillRect(GRAPH_X + 1, GRAPH_Y + 1, GRAPH_W - 2, GRAPH_H - 2, BLACK);

    // Disegna tutte le curve
    for (int i = 1; i < hist->count; i++) {
        int x1 = GRAPH_X + (GRAPH_W * (i - 1)) / hist->maxSize;
        int x2 = GRAPH_X + (GRAPH_W * i) / hist->maxSize;

        // HR (rosso)
        M5.Lcd.drawLine(
            x1, mapHR(hist->bpm[i - 1]),
            x2, mapHR(hist->bpm[i]),
            RED
        );

        // SpO2 (blu)
        M5.Lcd.drawLine(
            x1, mapSpO2(hist->spo2[i - 1]),
            x2, mapSpO2(hist->spo2[i]),
            BLUE
        );

        // Temp (giallo)
        M5.Lcd.drawLine(
            x1, mapTemp(hist->temperature[i - 1]),
            x2, mapTemp(hist->temperature[i]),
            YELLOW
        );

        // Shock Index (verde)
        M5.Lcd.drawLine(
            x1, mapSSI(hist->shock_index[i - 1]),
            x2, mapSSI(hist->shock_index[i]),
            GREEN
        );
    }

    delay(200);
}
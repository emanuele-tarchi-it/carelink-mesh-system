#include <M5Stack.h>
#include "carelink_protocol.h"
#include "telemetry_buffer.h"
#include "ui_dashboard.h"
#include "ui_menu.h"
#include "ui_graph.h"
#include "storage_sd.h"
#include "net_sync.h"
#include "espnow_gateway.h"   // ← aggiunto

enum GatewayMode { MODE_DASHBOARD, MODE_MENU, MODE_GRAPH };
GatewayMode mode = MODE_DASHBOARD;

String selectedBed = "";

void setup() {
    M5.begin();
    M5.Lcd.setTextSize(2);

    initSD();
    initESPNow();        // ← definire in espnow_gateway.cpp
    initBuffers();
    uiDashboardInit();   // ← aggiunto

    M5.Lcd.println("CareLink Gateway Ready");
}

void loop() {
    M5.update();

    // Cambio modalità
    if (mode == MODE_DASHBOARD && M5.BtnB.wasPressed()) {
        mode = MODE_MENU;
    }

    if (mode == MODE_MENU) {
        String bed = uiMenuLoop();
        if (bed != "") {
            selectedBed = bed;
            mode = MODE_GRAPH;
        }
    }

    if (mode == MODE_GRAPH) {
        uiGraphLoop(selectedBed);
        if (M5.BtnA.wasPressed() || M5.BtnB.wasPressed() || M5.BtnC.wasPressed()) {
            mode = MODE_DASHBOARD;
        }
    }

    if (mode == MODE_DASHBOARD) {
        uiDashboardLoop();
    }

    syncIfNetworkAvailable();
}

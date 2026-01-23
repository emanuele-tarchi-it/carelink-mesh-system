#include "ui_menu.h"
#include "telemetry_buffer.h"

static int selectedIndex = 0;
static std::vector<String> bedList;

// ============================================================
//  Inizializzazione menu
// ============================================================
void uiMenuInit() {
    bedList = getAllBedIDs();
    selectedIndex = 0;

    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(10, 10);
    M5.Lcd.print("Select Bed");
}

// ============================================================
//  Rendering del menu
// ============================================================
static void renderMenu() {
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setTextSize(2);

    if (bedList.empty()) {
        M5.Lcd.setCursor(10, 40);
        M5.Lcd.print("No beds found");
        return;
    }

    // Protezione da out-of-range
    if (selectedIndex >= bedList.size()) {
        selectedIndex = bedList.size() - 1;
    }

    for (int i = 0; i < bedList.size(); i++) {
        int y = 40 + i * 30;

        if (i == selectedIndex) {
            M5.Lcd.fillRect(0, y - 5, 320, 30, BLUE);
            M5.Lcd.setTextColor(WHITE, BLUE);
        } else {
            M5.Lcd.setTextColor(WHITE, BLACK);
        }

        M5.Lcd.setCursor(20, y);
        M5.Lcd.printf("Bed %s", bedList[i].c_str());
    }
}

// ============================================================
//  Loop del menu
// ============================================================
//
//  Ritorna:
//  - ""   → nessuna selezione
//  - "XX" → bed_id selezionato
//
// ============================================================
String uiMenuLoop() {
    bedList = getAllBedIDs();

    renderMenu();

    if (bedList.empty()) {
        delay(100);
        return "";
    }

    // Navigazione
    if (M5.BtnA.wasPressed()) {
        if (selectedIndex > 0) selectedIndex--;
        renderMenu();
        delay(150);
    }

    if (M5.BtnC.wasPressed()) {
        if (selectedIndex < bedList.size() - 1) selectedIndex++;
        renderMenu();
        delay(150);
    }

    if (M5.BtnB.wasPressed()) {
        return bedList[selectedIndex];
    }

    return "";
}
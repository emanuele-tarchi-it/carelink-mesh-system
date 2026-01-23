#include "net_sync.h"
#include "storage_sd.h"
#include <WiFi.h>

// ============================================================
//  Inizializzazione rete (placeholder per v0.5)
// ============================================================
void initNetwork() {
    // Per ora non connettiamo nulla.
    // In v0.5 qui metteremo:
    // - lettura config.json
    // - WiFi.begin(ssid, pass)
    // - attesa connessione
}

// ============================================================
//  Controlla se c’è connessione Internet
// ============================================================
bool isNetworkAvailable() {
    return (WiFi.status() == WL_CONNECTED);
}

// ============================================================
//  Stub: invia una riga al cloud (v0.5 → MQTT)
// ============================================================
bool sendLineToCloud(const String &line) {
    // Per ora simuliamo sempre successo.
    // In v0.5:
    // - publish MQTT
    // - attendi ACK
    // - ritorna true/false
    return true;
}

// ============================================================
//  Sincronizza pending.csv se c’è rete
// ============================================================
void syncIfNetworkAvailable() {
    if (!isNetworkAvailable()) return;

    // Leggi tutte le righe
    std::vector<String> lines = readPendingLines();

    if (lines.size() <= 1) {
        // Solo header → niente da sincronizzare
        return;
    }

    // Salta l’header
    for (int i = 1; i < lines.size(); i++) {
        const String &line = lines[i];

        if (!sendLineToCloud(line)) {
            // Se fallisce, interrompi la sync
            return;
        }
    }

    // Se tutte le righe sono state inviate → svuota file
    clearPendingFile();

    // Feedback visivo
    M5.Lcd.setCursor(10, 220);
    M5.Lcd.setTextSize(1);
    M5.Lcd.setTextColor(GREEN);
    M5.Lcd.print("Sync OK");
    M5.Lcd.setTextColor(WHITE);
}

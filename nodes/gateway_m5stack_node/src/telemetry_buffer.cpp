#include "telemetry_buffer.h"
#include <map>

// ============================================================
//  Strutture interne
// ============================================================

// Storico per ogni letto
static std::map<String, TelemetryHistory> historyMap;

// Ultimo messaggio ricevuto per ogni letto
static std::map<String, carelink_msg_t> lastMessageMap;

// Ultimo letto in alert (per dashboard)
static String lastAlertBed = "";

// ============================================================
//  Inizializzazione
// ============================================================
void initBuffers() {
    historyMap.clear();
    lastMessageMap.clear();
    lastAlertBed = "";
}

// ============================================================
//  Aggiorna buffer con nuovo pacchetto (v0.4)
// ============================================================
void updateTelemetry(const carelink_msg_t &msg) {

    String bed = String(msg.bed_id);

    // Se non esiste, crea buffer
    if (!historyMap.count(bed)) {
        TelemetryHistory h;
        h.index = 0;
        h.count = 0;
        historyMap[bed] = h;
    }

    TelemetryHistory &h = historyMap[bed];

    // Scrivi nel buffer circolare
    int i = h.index;

    h.bpm[i]         = msg.bpm;
    h.spo2[i]        = msg.spo2;
    h.temperature[i] = msg.temperature;
    h.shock_index[i] = msg.shock_index;
    h.alert_type[i]  = msg.alert_type;
    h.timestamp[i]   = msg.timestamp;

    // Aggiorna indici
    h.index = (h.index + 1) % h.maxSize;
    if (h.count < h.maxSize) h.count++;

    // Aggiorna ultimo messaggio
    lastMessageMap[bed] = msg;

    // Aggiorna stato alert (solo se non NORM)
    if (msg.alert_type != ALERT_NORM) {
        lastAlertBed = bed;
    }
}

// ============================================================
//  Lista di tutti i bed_id
// ============================================================
std::vector<String> getAllBedIDs() {
    std::vector<String> list;
    for (auto &kv : lastMessageMap) {
        list.push_back(kv.first);
    }
    return list;
}

// ============================================================
//  Ultimo messaggio in alert (per dashboard)
// ============================================================
const carelink_msg_t* getLatestAlertingMessage() {
    if (lastAlertBed == "") return nullptr;

    if (!lastMessageMap.count(lastAlertBed)) return nullptr;

    return &lastMessageMap[lastAlertBed];
}

// ============================================================
//  Storico per un letto
// ============================================================
const TelemetryHistory* getHistoryForBed(const String &bed_id) {
    if (!historyMap.count(bed_id)) return nullptr;
    return &historyMap[bed_id];
}

// ============================================================
//  Ultimo messaggio per un letto
// ============================================================
const carelink_msg_t* getLastMessageForBed(const String &bed_id) {
    if (!lastMessageMap.count(bed_id)) return nullptr;
    return &lastMessageMap[bed_id];
}

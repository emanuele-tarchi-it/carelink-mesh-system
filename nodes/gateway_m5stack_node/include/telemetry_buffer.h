#pragma once
#include <Arduino.h>
#include <vector>
#include "carelink_protocol.h"

// ============================================================
//  Struttura storico per ogni letto (v0.4)
// ============================================================
struct TelemetryHistory {
    static const int maxSize = 300;

    uint16_t bpm[maxSize];
    uint8_t spo2[maxSize];
    float temperature[maxSize];
    float shock_index[maxSize];
    uint8_t alert_type[maxSize];
    uint32_t timestamp[maxSize];

    int index;
    int count;
};

// ============================================================
//  API pubbliche
// ============================================================

// Inizializza tutte le strutture
void initBuffers();

// Aggiorna buffer e ultimo messaggio
void updateTelemetry(const carelink_msg_t &msg);

// Lista di tutti i bed_id attivi
std::vector<String> getAllBedIDs();
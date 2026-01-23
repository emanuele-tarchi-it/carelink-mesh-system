#pragma once
#include <Arduino.h>

// ============================================================
//  CareLink Nurse Node - Config v0.4
// ============================================================
//
// Ogni Nurse Node ha:
// - MAC del Gateway (per inoltro ESP-NOW)
// - Flag per inoltro via Serial (USB) invece che ESP-NOW
// - ID opzionale dell'infermiere (per future estensioni)
//
// Salvato in EEPROM tramite storage.cpp
//

typedef struct {
    char gateway_mac[18];        // "AA:BB:CC:DD:EE:FF"
    bool use_serial_gateway;     // true = Serial, false = ESP-NOW
    char nurse_id[8];            // opzionale, es: "N01"
} CareLinkConfig;

extern CareLinkConfig config;

void loadConfig(CareLinkConfig &cfg);
void saveConfig(const CareLinkConfig &cfg);
void resetConfig();

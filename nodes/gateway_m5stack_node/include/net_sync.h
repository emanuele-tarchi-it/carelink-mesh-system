#pragma once
#include <Arduino.h>

// ============================================================
//  Network Sync (v0.4 → stub per v0.5)
// ============================================================
//
//  initNetwork()            → inizializza WiFi (placeholder)
//  isNetworkAvailable()     → ritorna true se connesso
//  sendLineToCloud(line)    → stub per MQTT v0.5
//  syncIfNetworkAvailable() → sincronizza pending.csv
//
// ============================================================

// Inizializzazione rete (stub v0.4)
void initNetwork();

// Ritorna true se il dispositivo è connesso a Internet
bool isNetworkAvailable();

// Invia una singola riga al cloud (stub v0.4)
bool sendLineToCloud(const String &line);

// Sincronizza pending.csv se c’è rete
void syncIfNetworkAvailable();
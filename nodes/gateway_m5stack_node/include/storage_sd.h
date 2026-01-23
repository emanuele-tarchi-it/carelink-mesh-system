#pragma once
#include <Arduino.h>
#include <vector>
#include "carelink_protocol.h"

// ============================================================
//  Inizializzazione SD
// ============================================================
bool initSD();

// ============================================================
//  Timestamp formattato (stringa)
// ============================================================
String getTimestamp();

// ============================================================
//  Aggiunge una riga raw al file pending.csv
// ============================================================
void appendLine(const String &line);

// ============================================================
//  Logga un pacchetto CareLink (v0.4)
// ============================================================
void logTelemetry(const carelink_msg_t &msg);

// ============================================================
//  Legge tutte le righe in pending.csv
// ============================================================
std::vector<String> readPendingLines();

// ============================================================
//  Svuota pending.csv dopo sincronizzazione
// ============================================================
void clearPendingFile();
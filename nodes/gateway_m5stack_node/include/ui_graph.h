#pragma once
#include <M5Stack.h>
#include <Arduino.h>

// ============================================================
//  UI Graph - Trend clinico per un letto selezionato (v0.4)
// ============================================================
//
//  uiGraphInit(bed_id)   → prepara la schermata grafico
//  uiGraphLoop(bed_id)   → disegna HR / SpO2 / Temp / sSI
//
//  Il grafico mostra gli ultimi N campioni (buffer circolare)
//  forniti da telemetry_buffer.
//
//  uiGraphIsActiveFor(bed_id) → usato dal gateway per sapere
//  se aggiornare il grafico in tempo reale.
//
// ============================================================

// Inizializza la schermata del grafico per un letto specifico
void uiGraphInit(const String &bed_id);

// Loop del grafico: disegna HR, SpO2, Temp, Shock Index
void uiGraphLoop(const String &bed_id);

// Ritorna true se il grafico è attivo per quel bed_id
bool uiGraphIsActiveFor(const String &bed_id);
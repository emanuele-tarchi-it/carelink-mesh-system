#pragma once
#include <Arduino.h>
#include <M5Stack.h>

// ============================================================
//  UI Menu - Selezione letto (v0.4)
// ============================================================

// Inizializza la schermata del menu
void uiMenuInit();

// Loop del menu: ritorna il bed selezionato oppure ""
String uiMenuLoop();
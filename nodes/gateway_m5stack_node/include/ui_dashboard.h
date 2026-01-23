#pragma once
#include <Arduino.h>
#include "carelink_protocol.h"

// ============================================================
//  Inizializzazione dashboard
// ============================================================
void uiDashboardInit();

// ============================================================
//  Loop dashboard (mostra ultimo alert clinico)
// ============================================================
void uiDashboardLoop();

// ============================================================
//  Recupera l'ultimo messaggio in alert (v0.4)
//  Ritorna nullptr se non ci sono alert attivi
// ============================================================
const carelink_msg_t* getLatestAlertingMessage();
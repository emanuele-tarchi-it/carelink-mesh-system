#pragma once
#include <Arduino.h>
#include "carelink_protocol.h"

// Inizializzazione ESP-NOW
void initESPNow();

// Callback ricezione pacchetti
void onDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len);
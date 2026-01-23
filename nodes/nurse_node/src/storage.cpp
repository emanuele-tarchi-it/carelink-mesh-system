#include <Arduino.h>
#include <EEPROM.h>
#include "config.h"

// Indirizzo EEPROM (ESP8266)
#define EEPROM_SIZE 256
#define CONFIG_ADDR 0

CareLinkConfig config;

// ============================================================
//  Carica configurazione
// ============================================================
void loadConfig(CareLinkConfig &cfg) {
    EEPROM.begin(EEPROM_SIZE);
    EEPROM.get(CONFIG_ADDR, cfg);

    // Se EEPROM vuota o non inizializzata → valori di default
    if (cfg.gateway_mac[0] == '\0') {
        strcpy(cfg.gateway_mac, "AA:BB:CC:DD:EE:FF");
        cfg.use_serial_gateway = false;
        strcpy(cfg.nurse_id, "N01");
        saveConfig(cfg);
    }
}

// ============================================================
//  Salva configurazione
// ============================================================
void saveConfig(const CareLinkConfig &cfg) {
    EEPROM.put(CONFIG_ADDR, cfg);
    EEPROM.commit();
}

// ============================================================
//  Reset configurazione
// ============================================================
void resetConfig() {
    CareLinkConfig empty = {};
    strcpy(empty.gateway_mac, "AA:BB:CC:DD:EE:FF");
    empty.use_serial_gateway = false;
    strcpy(empty.nurse_id, "N01");

    saveConfig(empty);
}

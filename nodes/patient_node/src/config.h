#pragma once

struct CareLinkConfig {
    char bed_id[8];      // max 3 chars + '\0' (extra space OK)
    char nurse_mac[18];  // "AA:BB:CC:DD:EE:FF"
    bool paired;         // pairing status (v0.5)
};

extern CareLinkConfig config;

void loadConfig();
void saveConfig();
void resetConfig();
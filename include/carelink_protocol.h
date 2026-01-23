#pragma once
#include <Arduino.h>

//
// ============================================================
//  CARELINK PROTOCOL v0.4 (Aligned with documentation)
//  Clinical Telemetry + Alerts + ACK + Shock Index
// ============================================================
//

// -------------------------------
// ALERT TYPES (clinical v0.4)
// -------------------------------
typedef enum : uint8_t {
    ALERT_NORM      = 0x00,   // Routine telemetry
    ALERT_SOS       = 0x01,   // Manual emergency
    ALERT_INFECTION = 0x02,   // Temp > 38 + HR > 100
    ALERT_SHOCK     = 0x03    // sSI > 1.0
} alert_type_t;


// -------------------------------
// TELEMETRY PACKET (Patient → Nurse → Gateway)
// -------------------------------
// Size: 4 + 4 + 1 + 2 + 1 + 4 + 4 = 20 bytes (packed)
typedef struct __attribute__((packed)) {
    char bed_id[4];        // e.g. "B12"
    uint32_t timestamp;    // uptime ms or epoch ms
    uint8_t alert_type;    // alert_type_t
    uint16_t bpm;          // Heart Rate
    uint8_t spo2;          // Oxygen Saturation
    float temperature;     // °C
    float shock_index;     // BPM / SpO2
} carelink_msg_t;


// -------------------------------
// ACK PACKET (Nurse → Patient)
// -------------------------------
typedef struct __attribute__((packed)) {
    uint8_t ok;            // 1 = received, 0 = retry
} carelink_ack_t;
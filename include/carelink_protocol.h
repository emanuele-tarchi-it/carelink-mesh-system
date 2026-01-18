C++
/**
 * @file carelink_protocol.h
 * @author CareLink Team
 * @brief Definizione del protocollo binario v0.2 per ESP-NOW.
 * * Questo file definisce la struttura dei pacchetti per garantire la coerenza
 * tra nodi Patient, Nurse e Gateway.
 */

#ifndef CARELINK_PROTOCOL_H
#define CARELINK_PROTOCOL_H

#include <Arduino.h>

// Definizione dei tipi di allarme (alert_type)
#define ALERT_NORM      0x00  // Stato normale, telemetria di routine
#define ALERT_SOS       0x01  // Chiamata manuale di emergenza
#define ALERT_INFECTION 0x02  // Allarme clinico: Febbre + Tachicardia
#define ALERT_SHOCK     0x03  // Allarme clinico: Shock Index > 1.0

/**
 * @struct carelink_msg_t
 * @brief Struttura binaria del messaggio (21 byte totali)
 * * L'attributo 'packed' impedisce al compilatore di aggiungere padding,
 * fondamentale per la trasmissione P2P tra diverse architetture.
 */
typedef struct __attribute__((packed)) {
    char bed_id[4];         // ID Letto (es. "B12\0")
    uint32_t timestamp;     // Uptime del nodo o Epoch time (secondi)
    uint8_t alert_type;     // Codice allarme (0-3)
    uint16_t bpm;           // Battito cardiaco (Beats Per Minute)
    uint8_t spo2;           // Saturazione ossigeno (0-100%)
    float temperature;      // Temperatura corporea (°C)
    float shock_index;      // Calcolato come BPM / SpO2
} carelink_msg_t;

// Byte di ACK (Acknowledgment) per ESP-NOW
#define CARELINK_ACK_BYTE 0x06 

#endif // CARELINK_PROTOCOL_H

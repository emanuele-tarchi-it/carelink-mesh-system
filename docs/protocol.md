# 📡 CareLink — Communication Protocol v0.2
> **Binary-Optimized Protocol for Resilient Clinical Telemetry**

This document defines the communication protocol for CareLink. 
Version 0.2 transitions from generic JSON strings to Packed C-Structures to minimize latency, reduce power consumption, and ensure reliability on constrained ESP8266/ESP32 hardware.

---

## 1. 📦 Message Structure (Binary Payload)
To maximize performance, messages are transmitted as raw byte arrays mapped directly to a C-structure. This avoids the overhead of JSON parsing.

[STRUCT DEFINITION]
typedef struct __attribute__((packed)) {
    char bed_id[4];         // Unit identifier (e.g., "B12")
    uint32_t timestamp;     // Relative uptime or Epoch ms
    uint8_t alert_type;     // 0: NORM, 1: SOS, 2: INFECTION, 3: SHOCK
    uint16_t bpm;           // Heart Rate (BPM)
    uint8_t spo2;           // Oxygen Saturation (%)
    float temperature;      // Body Temperature (°C)
    float shock_index;      // Calculated sSI (BPM/SpO2)
} carelink_msg_t;

---

## 2. 🚦 Alert Classification & Priority
The protocol implements edge-calculated priority levels. Each alert_type triggers specific behaviors on both Patient and Nurse nodes:

| Alert Code | Severity | Description | Trigger Condition |
|:--- | :--- | :--- | :--- |
| 0x00 (NORM) | Low | Routine Telemetry | Vitals within safe thresholds. |
| 0x01 (SOS) | Critical | Manual Alert | Emergency button pressed by patient. |
| 0x02 (INFECT) | High | Infection Risk | Temp > 38.0°C + Tachycardia (BPM > 100). |
| 0x03 (SHOCK) | Critical | Hemodynamic Alert | sSI > 1.0 (BPM/SpO2 ratio). |

---

## 3. 📶 Communication Fallback Strategy
CareLink enforces a tiered transmission logic to guarantee delivery during infrastructure failures:

1. Wi-Fi (Primary): Uses MQTT/TCP for long-term data logging at the Gateway.
2. ESP-NOW (Secondary): Fast, peer-to-peer failover. Reaches Nurse Nodes directly if the local Wi-Fi router is down.
3. LoRa Mesh (Future): Emergency long-range layer for total building power failure (Planned v0.5).

---

## 4. 🔄 Acknowledgment (ACK) & Retries
The protocol uses a targeted feedback loop to ensure the Patient Node knows the alert was received:

1. Broadcast: Patient Node sends carelink_msg_t.
2. Validation: Nurse Node checks the bed_id and clinical priority.
3. ACK: Nurse Node replies with a 1-byte confirmation (0x06) to the sender's MAC address.
4. Timeout: If no ACK arrives within 500ms, the Patient Node retries up to 3 times.
5. Local Escalation: If all retries fail, the Patient Node enters "Isolated Alert Mode" (OLED Flashing).

---

## 5. 🚨 Visual Urgency Protocol
Hardware behavior is dictated by the protocol state:

* Standby: OLED displays real-time vitals and bed_id.
* Critical/Unacknowledged: The system calls display.invertDisplay(true) at 300ms intervals, creating a high-contrast strobe effect to signal urgency.

---

## 6. 🛠️ Implementation Notes (HW-364A)
* Bus Timing: Sensor polling (MAX30102/MAX30205) is interleaved with radio bursts to prevent I2C bus jitter.
* Memory Footprint: The binary structure uses only 21 bytes per packet, making it ideal for the limited RAM of the ESP8266.

---

## ⚠️ Disclaimer
CareLink is a technical and educational prototype. It is not a certified medical device and should not be used for life-critical monitoring.

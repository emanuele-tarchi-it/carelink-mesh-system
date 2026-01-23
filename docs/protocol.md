# 📡 CareLink — Communication Protocol (v0.4)
> **Binary‑Optimized Protocol for Resilient Clinical Telemetry & Secure Pairing**

This document defines the binary communication standards for the CareLink Mesh System.  
It covers both the **Telemetry Layer (v0.4)** for vital signs and the **Pairing Layer (v0.4)** for secure bedside association.

---

# 🟦 PART I: Clinical Telemetry (v0.4)
*Optimized for low latency and minimal power consumption on ESP8266/ESP32 hardware.*

---

## 1. 📦 Message Structure (Binary Payload)

Telemetry messages are transmitted as raw byte arrays mapped directly to a packed C‑structure.  
This avoids JSON overhead and ensures deterministic timing on low‑power microcontrollers.

### C‑Struct Definition

```c
typedef struct __attribute__((packed)) {
    char bed_id[4];         // Unit identifier (e.g., "B12")
    uint32_t timestamp;     // Relative uptime or Epoch ms
    uint8_t alert_type;     // 0: NORM, 1: SOS, 2: INFECTION, 3: SHOCK
    uint16_t bpm;           // Heart Rate (BPM)
    uint8_t spo2;           // Oxygen Saturation (%)
    float temperature;      // Body Temperature (°C)
    float shock_index;      // Calculated sSI (BPM/SpO2)
} carelink_msg_t;
```

---

## 2. 🚦 Alert Classification & Priority

The Patient Node computes `alert_type` locally.  
This reduces network load and ensures immediate clinical feedback even without connectivity.

| Alert Code | Severity | Description | Trigger Condition |
|-----------|----------|-------------|-------------------|
| **0x00 (NORM)** | Low | Routine telemetry | Vitals within safe thresholds |
| **0x01 (SOS)** | Critical | Manual alert | Emergency button pressed |
| **0x02 (INFECT)** | High | Infection risk | Temp > 38.0°C + BPM > 100 |
| **0x03 (SHOCK)** | Critical | Hemodynamic alert | sSI > 1.0 |

---

## 3. 📶 Communication Strategy (v0.4)

CareLink v0.4 uses a **single, robust transport layer**:

### **ESP‑NOW (Primary & Only Transport in v0.4)**  
- Patient → Nurse  
- Nurse → Gateway  
- Ultra‑low latency  
- Works without Wi‑Fi infrastructure  
- Immune to router failures  

### Future Layers (v0.5+)  
- **Wi‑Fi MQTT** for cloud sync  
- **LoRa Mesh** for long‑range emergency coverage  

---

## 4. 🔄 Acknowledgment (ACK) & Retries

1. Patient Node sends `carelink_msg_t` to the assigned Nurse Node  
2. Nurse Node replies with a **1‑byte ACK** (`0x06`)  
3. If no ACK within **500 ms**, Patient retries up to **3 times**  
4. After 3 failures, Patient enters **Isolated Alert Mode**  
   - OLED strobe  
   - Local alert persists until link restored  

---

# 🟧 PART II: Pairing & Identity (v0.4)
*Nurse‑First ESP‑NOW Handshake for Secure Bedside Association.*

---

## 5. 📡 Pairing Request Packet (Patient → Nurse)

Sent immediately after boot or factory reset.

```c
typedef struct __attribute__((packed)) {
    char bed_id[8];     // Configured Bed ID (e.g., "B12")
    uint8_t mac[6];     // Patient Node MAC address
} PairingPacket;
```

---

## 6. 📩 Pairing Response Packet (Nurse → Patient)

The Nurse Node replies to authorize or reject the association.

```c
typedef struct __attribute__((packed)) {
    uint8_t status;     // 1 = Accepted, 0 = Rejected
} PairingResponse;
```

---

## 7. 🔄 Pairing Flow Summary (v0.4)

1. **Boot:**  
   The Patient Node loads `bed_id` and `nurse_mac` from EEPROM.

2. **Unicast Request:**  
   The Patient Node sends a `PairingPacket` directly to the configured `nurse_mac`.

3. **Validation (Nurse Node):**  
   The Nurse Node checks:  
   - MAC address match  
   - bed assignment match  
   - pairing status not already taken  

4. **Response:**  
   The Nurse Node replies with `PairingResponse(status = 1)` if validation succeeds.

5. **Persistence:**  
   The Patient Node stores the pairing state and enters **Monitoring Mode**.

6. **Failure Handling:**  
   - Retries pairing  
   - If still unpaired, re‑opens the Captive Portal for reconfiguration  

This ensures pairing is **explicit**, **safe**, and always **nurse‑controlled**.

---

# 🛠️ PART III: Implementation Notes (HW‑364A)

---

## 8. 🚨 Visual Urgency Protocol

CareLink uses a consistent visual language across all nodes:

- **Standby:**  
  OLED shows vitals and bed ID.

- **Critical Alert:**  
  `invertDisplay(true)` toggled every 300 ms for a high‑contrast strobe.

- **Isolated Alert Mode:**  
  Triggered when ACKs fail; strobe persists until communication is restored.

---

## 9. ⚙️ Technical Notes

- Telemetry packet size: **21 bytes**  
- Pairing packets are lightweight and isolated from telemetry  
- Sensor polling is interleaved with ESP‑NOW bursts to avoid I2C jitter  
- ESP‑NOW channel is fixed to prevent cross‑ward interference  
- Pairing and telemetry use **separate structs** for clarity and safety  

---

# ⚠️ Disclaimer

CareLink is a technical and educational prototype.  
It is **not** a certified medical device and must not be used for life‑critical monitoring.

# 🏥 CareLink — Architecture v0.3
> **Resilient Multi-layer IoT Network for Hospital Ward Monitoring**

CareLink is a resilient, multi-layer IoT network designed for hospital ward monitoring, integrating real-time clinical analytics with fail-safe communication protocols.

---

## 1. 🏗️ System Overview
The CareLink ecosystem operates through three primary functional nodes:

| Node Type | Hardware Platform | Primary Function |
| :--- | :--- | :--- |
| **Patient Nodes** | ESP8266 (HW-364A) | Continuous vitals monitoring & automated alerting |
| **Nurse Nodes** | ESP32 / ESP8266 | Alert management & alarm acknowledgment |
| **Gateway** | ESP32 / PC / Cloud | Event logging & system synchronization |

---

## 2. 🔌 Hardware Specification (Patient Node)
The implementation leverages the **HW-364A** board, featuring an integrated OLED. Technical precision regarding pin mapping is critical for sensor stability.

### 2.1 I2C Bus Mapping
Due to non-standard manufacturer pinouts, the I2C bus must be initialized manually on the following GPIOs:

- **SDA**: `GPIO 14` (Physical Pin **D5**)
- **SCL**: `GPIO 12` (Physical Pin **D6**)

### 2.2 Shared Sensor Matrix
Three devices coexist on the same I2C bus using unique hexadecimal addresses:

| Device | I2C Address | Function |
| :--- | :--- | :--- |
| **SSD1306 OLED** | `0x3C` | Local visual feedback & status |
| **MAX30102** | `0x57` | Pulse Oximetry & Heart Rate |
| **MAX30205** | `0x48` | Clinical-grade body temperature |

---

## 3. 🧠 Clinical Intelligence Layer
Firmware v0.2 introduces edge-processing algorithms to provide immediate clinical decision support:

### Simplified Shock Index (sSI)
- **Formula**: `sSI = HeartRate / SpO2`
- **Threshold**: Values **> 1.0** may indicate hemodynamic instability.

### Infection Alert
- **Logic**: Triggered if **Body Temp > 38.0°C**
- **Co-factors**: Tachycardia (**BPM > 100**) or desaturation.

---

## 4. 📡 Communication Strategy
CareLink ensures message delivery through a tiered fallback strategy to survive network outages:

1. **Wi-Fi (Primary)** — High-speed synchronization with the Gateway  
2. **ESP-NOW (Secondary)** — Low-latency, peer-to-peer Patient → Nurse communication  
3. **LoRa Mesh (Future)** — Long-range emergency layer for hospital-wide resilience  

---

## 5. 🧩 Clinical Escalation Model (Nurse‑First)
CareLink follows a human-centered escalation model aligned with real hospital workflows.

### Key Principles
- **The nurse is always the first clinical decision-maker**  
- Patient Nodes never escalate directly to physicians  
- Trend deviations and anomalies are validated by the Nurse Node  
- Only nurse-approved events may be escalated to supervisory roles (v0.5+)  

A detailed description of the clinical flow is available in:

👉 **[`docs/clinical-flow.md`](docs/clinical-flow.md)**

This separation keeps the architecture focused on the technical layers while documenting clinical logic in a dedicated file.

---

## 6. 🛡️ Resilience & Safety Features
- **Visual Urgency** — OLED strobe via `invertDisplay()` during critical alerts  
- **Local Autonomy** — Alerts processed at the edge; visual alarms remain active even without network connectivity  
- **Power Resilience** — Designed for mains power with optional backup battery support  

---

## ⚠️ Disclaimer
*CareLink is a technical and educational prototype inspired by clinical workflows.  
It is **not** a certified medical device.*

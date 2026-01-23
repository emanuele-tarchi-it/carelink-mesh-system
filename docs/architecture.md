# 🏥 CareLink — Architecture v0.4
**Resilient Multi-layer IoT Network for Hospital Ward Monitoring**

CareLink is a resilient, multi-layer IoT network designed for hospital ward monitoring, integrating real-time clinical analytics with fault-tolerant communication and local autonomy at every level.

---

## 🏗️ 1. System Overview

The CareLink ecosystem operates through three coordinated functional nodes:

| Node Type | Hardware Platform | Primary Function |
| --------- | ----------------- | ---------------- |
| **Patient Nodes** | ESP8266 (HW-364A) | Continuous vitals acquisition and edge alerting |
| **Nurse Nodes** | ESP8266 + OLED | Real-time triage, alert validation and relay |
| **Gateway M5Stack** | ESP32 (M5Stack Core Basic) | Historical analytics, SD logging, cloud sync |

High-level data flow:
```
Patient Node → Nurse Node → Gateway M5Stack → Cloud (v0.5)
```

Each layer adds redundancy, context, and clinical intelligence.

---

## 🔌 2. Hardware Specification (Patient Node)

The Patient Node is built on the HW-364A ESP8266 board, which includes an integrated SSD1306 OLED. Due to non-standard pinouts, the I2C bus requires manual configuration.

### 2.1 I2C Bus Mapping

- **SDA** → GPIO 14 (D5)  
- **SCL** → GPIO 12 (D6)

### 2.2 Shared Sensor Matrix

Three devices coexist on the same I2C bus using unique hexadecimal addresses:

| Device | I2C Address | Function |
| ------ | ----------- | -------- |
| **SSD1306 OLED** | 0x3C | Local visual feedback and status |
| **MAX30102** | 0x57 | Pulse oximetry and heart rate |
| **MAX30205** | 0x48 | Clinical-grade body temperature |

This configuration enables compact, low-power bedside monitoring.

---

## 🧠 3. Clinical Intelligence Layer

CareLink performs edge analytics directly on the Patient Node to reduce latency and avoid cloud dependency.

### Simplified Shock Index (sSI)

- **Formula:** sSI = HeartRate / SpO2  
- **Threshold:** Values > 1.0 may indicate hemodynamic instability

### Infection Alert

Triggered when:

- **Body Temp > 38.0°C**, and  
- Tachycardia (**HR > 100**) or desaturation

These rules provide immediate, local clinical insight even without network connectivity.

---

## 📡 4. Communication Strategy

CareLink uses a tiered, fault-tolerant communication model:

1. **ESP-NOW (Primary, Local Mesh)**  
   - Patient → Nurse  
   - Nurse → Gateway  
   - Ultra-low latency  
   - Works without Wi-Fi infrastructure  

2. **Wi-Fi (Gateway Only)**  
   - Cloud synchronization (v0.5)  
   - Remote dashboards  

3. **SD Logging (Gateway Fallback)**  
   - Guaranteed data retention  
   - CSV format for interoperability  

4. **LoRa Mesh (Future Layer)**  
   - Hospital-wide emergency coverage  
   - Long-range, low-power  

This architecture ensures continuity even during partial network failures.

---

## 🧩 5. Clinical Escalation Model (Nurse-First)

CareLink follows a human-centered escalation model aligned with real hospital workflows.

### Key Principles

- **The nurse is always the first clinical decision-maker**  
- Patient Nodes never escalate directly to physicians  
- Trend deviations and anomalies are validated by the Nurse Node  
- Only nurse-approved events may be escalated to supervisory roles (v0.5+)  

A detailed description of the clinical flow is available in:

`docs/clinical-flow.md`

This separation keeps the architecture focused on the technical layers while documenting clinical logic in a dedicated file.

---

## 🖥️ 6. Gateway M5Stack — Edge Analytics Hub (v0.4)

The Gateway introduces a full clinical dashboard:

- Real-time dashboard with last alerting bed  
- Bed selection menu  
- HR/SpO2 trend graph (300-sample circular buffer)  
- SD logging (`pending.csv`)  
- Cloud sync stub (MQTT in v0.5)  
- ESP-NOW receiver for multi-bed aggregation  

This transforms CareLink from a simple mesh into a clinical edge analytics platform.

---

## 🛡️ 7. Resilience & Safety Features

- **Visual urgency** on Patient and Nurse nodes via OLED inversion  
- **Local autonomy**: alerts remain active even without network  
- **SD fallback**: no data loss during outages  
- **Modular firmware**: each node operates independently  
- **Power resilience**: designed for mains with optional battery  

---

## ⚠️ Disclaimer

CareLink is a technical and educational prototype inspired by clinical workflows.  
It is **not** a certified medical device.

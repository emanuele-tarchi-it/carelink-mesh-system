# 🗺️ CareLink Roadmap — v0.5
A structured, incremental roadmap guiding CareLink from prototype to production‑ready clinical IoT system.

---

## ✅ v0.2 — Clinical Intelligence (COMPLETED)
Foundational clinical logic and sensor integration.

- MAX30102 integration  
- MAX30205 integration  
- SpO₂, HR, Temperature acquisition  
- Shock Index (sSI) calculation  
- Infection Alert logic  
- Clinical OLED display  
- Serial telemetry output  

---

## ✅ v0.3 — Configuration & Pairing (COMPLETED)
Secure bedside identity and nurse‑first association.

- Captive Portal for initial setup (legacy)  
- EEPROM persistent configuration  
- Bed ID assignment  
- Nurse MAC assignment  
- Secure ESP‑NOW pairing handshake  
- OLED pairing feedback  
- Gateway pairing event logging  
- Documentation updates  

---

## ✅ v0.4 — Clinical Telemetry (COMPLETED)
Full telemetry pipeline from Patient → Nurse → Gateway.

- Unified `carelink_protocol v0.4`  
- Shock Index + Infection logic revision  
- Patient Node → vitals + alerts  
- Nurse Node → SOS (relay removed)  
- Gateway → SD logging, graphing, dashboard  
- ESP‑NOW as primary transport  
- SD‑based pending queue  
- Network sync stub (v0.5‑ready)  
- Project structure cleanup  
- Unified `platformio.ini`  

---

## 🔜 v0.5 — Escalation, Cloud Sync & Setup
Human‑centered escalation model with supervisory layer + modern configuration workflow.

### **Escalation Layer**
- Doctor Node role  
- Escalation logic (Nurse → Doctor)  
- Multi‑node alert routing  
- Prioritization of critical events  

### **Cloud & Sync**
- MQTT publishing (stable)  
- Gateway → cloud sync with ACK  
- Offline‑first buffering (pending.csv v0.5)  
- Cloud dashboard (basic JSON feed)  

### **Setup & UX**
- Captive Portal v2 (AP mode)  
- WiFi + MQTT credentials setup  
- Auto‑pairing Patient/Nurse/Gateway  
- Configurable bed_id, nurse_id, gateway_mac  
- Reset workflow + confirmation page  

### **Gateway Enhancements**
- Dashboard v2 (web-based)  
- Real‑time vitals stream  
- Alert history viewer  

---

## 🔭 v0.6 — Mesh Networking
Resilient, ward‑wide communication backbone.

- LoRa mesh backbone  
- Multi‑hop routing  
- Redundant paths  
- Ward‑wide coverage  
- Offline‑first behavior  
- Automatic node discovery  

---

## 🎯 v1.0 — Production Candidate
Toward a clinically viable prototype.

- OTA updates (ESP32 + ESP8266)  
- Enclosure + hardware revision  
- Battery optimization  
- Clinical trial preparation  
- Documentation + safety review  
- Reliability testing (24h, 72h, 7‑day burn‑in)  

---

## 🌟 Current Status
**CareLink v0.4 is complete.**  
The system is now stable, modular, and ready for the v0.5 expansion phase.
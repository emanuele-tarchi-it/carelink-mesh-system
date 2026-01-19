# CareLink — Bedside Nodes

Bedside nodes are patient‑side devices responsible for monitoring, alerts, and emergency communication.

---

## 🟩 Capabilities

- Vital sign acquisition  
- Local clinical logic  
- Emergency button  
- Multi‑layer communication  
- Automatic fallback during network issues  

---

## 🔄 Communication

Nodes communicate using:

- **Wi‑Fi** when available  
- **ESP‑NOW** when Wi‑Fi is unstable  
- **LoRa (future)** for long‑range redundancy  

Nodes never stop sending critical events.

---

## 🧠 Local Logic

Each node performs:

- threshold checks  
- trend detection  
- emergency button handling  
- periodic heartbeat messages  
- fallback switching  

---

## 🔋 Hardware

Nodes are based on:

- ESP32 microcontrollers  
- modular sensors  
- low‑power design  
- optional battery operation  


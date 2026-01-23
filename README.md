<div align="center">

<pre>

   ██████╗  █████╗ ██████╗ ███████╗██╗     ██╗███╗   ██╗██╗  ██╗
  ██╔════╝ ██╔══██╗██╔══██╗██╔════╝██║     ██║████╗  ██║██║ ██╔╝
  ██║      ███████║██████╔╝█████╗  ██║     ██║██╔██╗ ██║█████╔╝ 
  ██║      ██╔══██║██╔══██╗██╔══╝  ██║     ██║██║╚██╗██║██╔═██╗ 
  ╚██████╗ ██║  ██║██║  ██║███████╗███████╗██║██║ ╚████║██║  ██╗
   ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝╚══════╝╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝

</pre>

</div>

---

# 🏥 **CareLink**  
### *Born in the ward. Built for the ward.*

![Version](https://img.shields.io/badge/Version-0.4-blue)
![Platform](https://img.shields.io/badge/Platform-ESP8266--ESP32-orange)
![Framework](https://img.shields.io/badge/Framework-Arduino/PlatformIO-blue)
![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)

CareLink was not imagined in a lab.  
It was born in real hospital wards — during long shifts, beside patients who needed constant attention, and among professionals who carry the weight of care every single day.

This project does **not** aim to replace anyone.  
It exists to **support everyone**.

CareLink is a tribute to the entire healthcare team:

- nurses  
- healthcare assistants and support staff  
- physicians and residents  
- physiotherapists  
- respiratory and rehabilitation therapists  
- medical technicians  
- all professionals who make patient care possible  

Every one of them faces pressure, fatigue, responsibility, and moments where time is never enough.  
CareLink wants to give back a little of that time.

It aims to reduce stress, prevent oversights, and anticipate problems before they grow.  
It is designed to be a **silent ally**, a background presence that helps clinical work remain human, focused, and safe.

This project is also part of my own journey — a bridge between the world where I worked for years and the world I am building toward.  
A way to honor what I learned in healthcare, and to grow through engineering.

---

# ✨ **What’s New in v0.4 — Clinical Telemetry Release**

Version 0.4 is where CareLink becomes a **fully functional clinical system**, not just a concept.

### 📡 Real‑Time Telemetry  
Patient Nodes now send continuous, low‑latency clinical data:

- Heart Rate  
- SpO₂  
- Body Temperature  
- Shock Index  
- Clinical alerts (SOS, Infection, Shock)

### 👩‍⚕️ Nurse‑First Model  
Every alert is validated by the Nurse Node.  
Technology supports — it never overrides clinical judgment.

### 🖥️ Gateway Dashboard  
The M5Stack Gateway becomes a compact clinical hub:

- last active alert  
- real‑time vitals  
- 300‑sample trend graph  
- bed selection menu  
- SD logging  
- offline‑first behavior

### 💾 SD Logging  
All telemetry is stored in `pending.csv`, ready for cloud sync in v0.5.

### 🔌 ESP‑NOW Mesh  
A resilient, infrastructure‑free communication layer.  
No Wi‑Fi. No router. No single point of failure.

---

# 🧱 **Where CareLink Is Going — v0.5 and Beyond**

CareLink is not a static project.  
It evolves, just as I do.

### 🔜 v0.5 — Escalation & Cloud Sync  
- Doctor Node  
- Nurse‑validated escalation  
- MQTT cloud publishing  
- Remote dashboard  
- Modern setup workflow (Captive Portal v2)

### 🔭 v0.6 — Mesh Networking  
- LoRa mesh backbone  
- Multi‑hop routing  
- Ward‑wide coverage  
- Redundant paths

### 🎯 v1.0 — Production Candidate  
- OTA updates  
- Hardware revision  
- Battery optimization  
- Reliability testing  
- Clinical‑grade documentation

---

# 📚 **Technical Documentation**

All technical documentation — architecture, protocol, flows, roadmap — is available in:

👉 **[`/docs/`](./docs/)**

This README is the story.  
The docs are the engineering.

---

# ❤️ **A Project With a Soul**

CareLink was born from real clinical experience, but it grows through engineering.  
It stands at the intersection of two worlds:  
the world of care, and the world of technology.

Every line of code is a step in a personal journey —  
a way to honor the people I worked with,  
and a way to build the future I’m moving toward.

CareLink is my way of saying thank you.  
And my way of becoming better.

---

# 🔚 **Closing Note**

CareLink will continue to evolve — with the same determination, the same curiosity, the same care.  
A technical project, yes.  
But above all, a human one.
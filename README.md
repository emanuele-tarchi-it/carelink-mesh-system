<div align="center">

<pre>

   ██████╗  █████╗ ██████╗ ███████╗██╗     ██╗███╗   ██╗██╗  ██╗
  ██╔════╝ ██╔══██╗██╔══██╗██╔════╝██║     ██║████╗  ██║██║ ██╔╝
  ██║      ███████║██████╔╝█████╗  ██║     ██║██╔██╗ ██║█████╔╝ 
  ██║      ██╔══██║██╔══██╗██╔══╝  ██║     ██║██║╚██╗██║██╔═██╗ 
  ╚██████╗ ██║  ██║██║  ██║███████╗███████╗██║██║ ╚████║██║  ██╗
   ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝╚══════╝╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝

</pre>

### **A resilient clinical IoT ecosystem for real‑world bedside monitoring, nurse workflows, and emergency alerts.**

</div>

---

# 🏥 CareLink  
### *Born in the ward. Built for the ward. A tribute to those who care.*

![Version](https://img.shields.io/badge/Version-0.3--EN-blue)
![Platform](https://img.shields.io/badge/Platform-ESP32--Clinical-orange)
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
- rehabilitation and respiratory therapists  
- medical technicians  
- all professionals who make patient care possible  

Every one of them faces pressure, fatigue, responsibility, and moments where time is never enough.  
CareLink wants to give back a little of that time.

It aims to reduce stress, prevent oversights, and anticipate problems before they grow.  
It is designed to be a **silent ally**, a background presence that helps clinical work remain human, focused, and safe.

This project is my way of honoring the people I worked with for years —  
and also the path I am building for my own future, a bridge between healthcare and engineering.

---

# 🌐 What CareLink Is (Beyond the Technology)

CareLink is a bedside ecosystem that:

- gathers vital signs directly from the patient’s bed  
- interprets them with simple but meaningful clinical logic  
- alerts the nurse gateway when something changes  
- keeps working even when the network fails  
- prepares data for cloud analysis and ward‑wide visibility  

It does not decide.  
It does not replace.  
**It supports.**

---

# 🏗️ System Architecture Overview

CareLink is built as a **modular clinical IoT ecosystem** composed of:

### **🟦 Bedside Nodes**
- Patient‑side devices  
- Vital sign acquisition  
- Local clinical logic  
- Emergency button  
- Multi‑layer communication  

### **🟩 Nurse Gateway**
- Central coordinator  
- Aggregates all bedside data  
- Manages alerts and acknowledgments  
- Ensures resilience during network instability  
- Prepares data for cloud integration  

### **🟧 Multi‑Layer Connectivity**
CareLink uses several communication layers to avoid single points of failure:

- **Wi‑Fi** — high‑bandwidth operations  
- **ESP‑NOW** — low‑latency peer‑to‑peer communication  
- **LoRa (planned)** — long‑range, low‑power redundancy  

### **🟥 Cloud‑Ready**
Future integration will include:

- dashboards  
- analytics  
- remote monitoring  
- ward‑wide visibility  

---

# 🚀 Core Principles

### **1. Real‑World Resilience**
CareLink is engineered to continue operating even when:

- Wi‑Fi is unstable  
- the network is congested  
- the gateway temporarily loses connectivity  
- the environment is noisy or unpredictable  

### **2. Clinical Workflow First**
The system supports:

- bedside monitoring  
- nurse alert workflows  
- emergency requests  
- acknowledgment loops  
- escalation logic  

### **3. Modular Architecture**
Each component can evolve independently:

- Gateway  
- Nodes  
- Communication layers  
- Cloud integration  
- Clinical logic  

### **4. Future‑Ready**
CareLink is designed to grow into:

- cloud dashboards  
- analytics  
- remote supervision  
- integration with hospital systems  

---

# 📚 Documentation

Technical documentation is available in the `docs/` directory:

- `architecture.md` — System architecture  
- `gateway.md` — Gateway logic  
- `nodes.md` — Bedside node behavior  
- `clinical-flow.md` — Clinical workflow logic  
- `setup.md` — Installation and configuration  

---

# 🛠 Tech Stack

- **Firmware:** C++ (ESP32)  
- **Communication:** Wi‑Fi, ESP‑NOW, LoRa (planned)  
- **Architecture:** Modular, multi‑layer, cloud‑ready  
- **Hardware:** ESP32‑based devices  

---

# ⚠️ Disclaimer

CareLink is an educational and experimental project.  
It is **not** a certified medical device and must not be used for diagnosis, treatment, or real clinical decision‑making.

---

# 🌟 Closing Note

CareLink is built with a simple mission:  
**to bring reliability, clarity, and continuity to bedside communication in real‑world clinical environments.**

It is a project shaped by experience, designed with intention, and engineered for resilience.


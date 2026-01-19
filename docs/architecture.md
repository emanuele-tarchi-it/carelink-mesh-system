# CareLink — System Architecture

CareLink is a resilient clinical IoT ecosystem designed for real‑world bedside monitoring, nurse workflows, and emergency alerts.  
Its architecture is modular, fault‑tolerant, and built to operate even in unstable network conditions.

---

## 🏗️ High‑Level Architecture

CareLink is composed of three main layers:

### **1. Bedside Nodes**
- ESP32‑based patient‑side devices  
- Vital sign acquisition  
- Local clinical logic  
- Emergency button  
- Multi‑layer communication (Wi‑Fi + ESP‑NOW, LoRa planned)  
- Automatic fallback when the network is unstable  

### **2. Nurse Gateway**
- Central coordinator  
- Aggregates data from all bedside nodes  
- Manages alerts, acknowledgments, and escalation  
- Ensures continuity during Wi‑Fi outages  
- Prepares data for cloud dashboards (future)  

### **3. Cloud‑Ready Layer (Future)**
- Ward‑wide dashboards  
- Analytics and trends  
- Remote supervision  
- Integration with hospital systems  

---

## 🔄 Communication Model

CareLink uses a **multi‑layer communication strategy** to avoid single points of failure:

| Layer      | Purpose | Strengths |
|------------|---------|-----------|
| **Wi‑Fi**  | High‑bandwidth operations | Fast, standard, easy to integrate |
| **ESP‑NOW** | Low‑latency peer‑to‑peer | Works without Wi‑Fi, resilient |
| **LoRa (planned)** | Long‑range redundancy | Works through walls, low power |

Nodes automatically switch to the most reliable layer available.

---

## 🧠 Clinical Logic Overview

Each bedside node performs:

- threshold‑based checks  
- trend detection  
- emergency button handling  
- escalation triggers  
- acknowledgment loops with the gateway  

The gateway aggregates and validates all incoming events.

---

## 🧩 Modularity

CareLink’s architecture allows each component to evolve independently:

- communication layers  
- clinical logic  
- gateway logic  
- cloud integration  
- hardware modules  

This ensures long‑term scalability and maintainability.

---

## 🛡️ Resilience Principles

CareLink is designed to:

- continue operating during Wi‑Fi instability  
- maintain communication even if the gateway temporarily loses connectivity  
- avoid data loss  
- ensure patient → nurse communication at all times  

Resilience is not a feature — it is the foundation of the system.


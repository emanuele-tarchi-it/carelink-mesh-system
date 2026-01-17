# CareLink Mesh System — Architecture

CareLink Mesh System is designed as a resilient, multi‑layer IoT communication network for hospital wards.  
Its architecture ensures continuous operation across different network conditions, combining Wi‑Fi, ESP‑NOW, and a future LoRa mesh layer to guarantee reliable delivery of clinical alerts.

---

## 1. System Overview

CareLink Mesh System consists of three primary components:

- **Patient Nodes**  
  Bedside devices equipped with sensors and backup power. They generate alerts when thresholds are exceeded or when manually triggered.

- **Nurse Nodes**  
  Portable devices carried by nursing staff. They receive alerts, allow alarm acknowledgment, and provide an emergency “call for help” function.

- **Gateway**  
  A central coordination point that receives alerts, logs events, synchronizes node data, and interfaces with local or cloud services.

The system is designed to remain operational even during partial or complete network outages.

---

## 2. Communication Layers

CareLink Mesh System uses a tiered communication strategy:

### **2.1 Wi‑Fi (Primary Channel)**
Used for:
- Patient Node → Gateway communication  
- Nurse Node → Gateway communication  
- Synchronization with PC or cloud services  
- Firmware updates (future)

### **2.2 ESP‑NOW (Fallback Channel)**
Activated when Wi‑Fi is unavailable.  
Provides:
- Low‑latency peer‑to‑peer messaging  
- Direct Patient Node → Nurse Node communication  
- Basic multi‑hop forwarding (planned)  
- ACK and retransmission logic

### **2.3 LoRa Mesh (Future Emergency Layer)**
Designed for extended outages or long‑range coverage.  
Provides:
- Multi‑hop mesh routing  
- Low‑bandwidth critical messaging  
- High resilience in degraded environments

---

## 3. Node Types

### **3.1 Patient Node**
Hardware: ESP8266 or ESP32  
Power: mains + backup battery  
Functions:
- Sensor monitoring (vitals, motion, custom inputs)  
- Threshold‑based alert generation  
- Manual alert button (optional)  
- Communication via Wi‑Fi → ESP‑NOW → LoRa (fallback order)

### **3.2 Nurse Node**
Hardware: ESP32 or M5Stack  
Power: rechargeable battery  
Interface:
- Small display (OLED/TFT)  
- Buttons for:
  - Alarm acknowledgment (with confirmation)
  - Emergency assistance request (long‑press or double‑press safety logic)
Functions:
- Receive alerts  
- Send ACK with operator ID and timestamp  
- Broadcast emergency requests to nearby nodes  

### **3.3 Gateway**
Hardware: ESP32 or PC running Python  
Functions:
- Collect alerts from nodes  
- Log events locally or to cloud  
- Synchronize configuration across nodes  
- Provide a single point of integration for dashboards or hospital systems  

---

## 4. Message Flow

### **4.1 Alert Flow**
1. Patient Node detects threshold breach  
2. Sends alert via Wi‑Fi  
3. If Wi‑Fi unavailable → ESP‑NOW  
4. If ESP‑NOW unavailable → LoRa (future)  
5. Nurse Nodes receive alert  
6. Nurse acknowledges alert  
7. ACK sent to Gateway and all nodes  
8. Event logged with operator ID and timestamp  

### **4.2 Assistance Request Flow**
1. Nurse presses “Help” button (long‑press or double‑press)  
2. Message broadcast to nearby Nurse Nodes  
3. Gateway logs event  
4. Optional: escalate to cloud or PC dashboard  

---

## 5. Resilience Strategy

CareLink Mesh System is designed for fault tolerance:

- **Network fallback:**  
  Wi‑Fi → ESP‑NOW → LoRa  
- **Power resilience:**  
  Backup batteries on all nodes  
- **Mesh routing:**  
  Multi‑hop forwarding when gateway is out of range  
- **ACK + retransmission:**  
  Ensures message delivery  
- **Local logging:**  
  Events stored even without cloud connectivity  

---

## 6. Scalability

The architecture supports scaling across:

- individual rooms  
- entire wards  
- multiple hospital floors  
- multiple buildings (with LoRa mesh)

Each node has a unique ID and can be grouped by:
- ward  
- sector  
- room  
- bed  

Configuration is synchronized via the Gateway.

---

## 7. Future Cloud Integration (v1.0)

Planned AWS components:

- **API Gateway** – entry point for node communication  
- **AWS Lambda** – serverless processing of alerts  
- **DynamoDB** – event storage  
- **SNS / EventBridge** – notifications and escalation  
- **Web Dashboard** – monitoring and analytics  

---

## 8. Disclaimer

CareLink Mesh System is a technical and educational prototype inspired by real clinical workflows.  
It is not a certified medical device.

# CareLink Mesh System — Roadmap

This roadmap outlines the planned evolution of CareLink Mesh System, from a local prototype to a resilient, cloud‑integrated IoT network for hospital wards.

---

## v0.1 — Local Prototype (Single Ward, Wi‑Fi Only)

**Goal:** Validate the core concept with a minimal, fully local setup.

**Scope:**
- Implement basic Patient Node and Nurse Node behavior
- Use Wi‑Fi as the only communication channel
- Run the Gateway as a Python script on a local PC or single ESP32

**Planned Features:**
- Patient Node:
  - Manual alert trigger (button)
  - Optional simulated sensor alerts (threshold‑based)
- Nurse Node:
  - Receive alerts from Gateway
  - Display patient/bed ID and alert type
  - Acknowledge alerts via button
- Gateway:
  - Receive alerts from Patient Nodes
  - Forward alerts to Nurse Nodes
  - Log events (file or console) with:
    - timestamp  
    - node ID  
    - alert type  
    - acknowledgment status  

**Success Criteria:**
- End‑to‑end alert flow works reliably on a local network
- Nurse can receive and acknowledge alerts
- Events are logged consistently

---

## v0.2 — ESP‑NOW Fallback (Resilient Local Network)

**Goal:** Ensure communication continuity when Wi‑Fi is unavailable.

**Scope:**
- Introduce ESP‑NOW as a fallback channel
- Enable direct node‑to‑node communication

**Planned Features:**
- Automatic fallback from Wi‑Fi to ESP‑NOW when the Gateway is unreachable
- Direct Patient Node → Nurse Node messaging
- Basic ACK and retry logic:
  - resend if no ACK within a timeout
  - configurable retry count
- Optional:
  - Simple multi‑hop forwarding (manual routing rules)

**Success Criteria:**
- Alerts are delivered even when Wi‑Fi is down
- ACK and retry logic reduces message loss
- System remains usable in degraded network conditions

---

## v0.3 — LoRa Mesh (Experimental Emergency Layer)

**Goal:** Add a long‑range, low‑bandwidth emergency communication layer.

**Scope:**
- Integrate LoRa radios for critical messaging
- Experiment with mesh‑like behavior for extended coverage

**Planned Features:**
- LoRa as a tertiary fallback when both Wi‑Fi and ESP‑NOW are unavailable
- Basic mesh behavior:
  - multi‑hop forwarding between nodes
  - configurable max hop count
- Message types over LoRa:
  - critical alerts
  - emergency assistance requests
- Simple congestion control:
  - minimal message size
  - limited frequency of transmissions

**Success Criteria:**
- Critical alerts can traverse multiple hops via LoRa
- System remains operational in “worst‑case” network scenarios
- LoRa usage stays within regional regulatory limits

---

## v0.4 — Configuration & Identity Management

**Goal:** Make the system manageable at scale.

**Scope:**
- Introduce structured configuration and identity for nodes

**Planned Features:**
- Unique IDs for:
  - wards  
  - rooms  
  - beds  
  - nodes  
- Configuration sync via Gateway:
  - assign beds to Patient Nodes
  - assign Nurse Nodes to wards/sectors
- Basic PC interface (CLI or simple UI) to:
  - view node status
  - update configuration
  - review logs

**Success Criteria:**
- Nodes can be identified and grouped logically
- Configuration changes propagate reliably
- Logs are meaningful at ward/room/bed level

---

## v1.0 — Cloud Integration (AWS‑Ready)

**Goal:** Extend the system beyond local infrastructure and enable centralized monitoring.

**Scope:**
- Connect the Gateway to AWS
- Introduce serverless processing and persistent storage

**Planned Features:**
- API Gateway as entry point for alerts and events
- AWS Lambda functions for:
  - processing alerts
  - storing events
  - triggering notifications
- DynamoDB for:
  - event logs
  - node registry
  - configuration data
- Basic web dashboard:
  - list of active alerts
  - event history
  - node status overview

**Success Criteria:**
- Local system can operate standalone and sync with cloud when available
- Events are stored and queryable in DynamoDB
- Dashboard reflects real‑time and historical data

---

## v1.1+ — Hardening, Security & Compliance (Future Work)

**Potential Areas:**
- Message encryption and authentication between nodes
- Role‑based access control for dashboards and tools
- Integration with hospital IT systems (where applicable)
- Performance and reliability testing in simulated environments
- Documentation for deployment and maintenance

---

## Disclaimer

This roadmap is indicative and may evolve as the project grows.  
CareLink Mesh System is a technical and educational prototype and is not a certified medical device.

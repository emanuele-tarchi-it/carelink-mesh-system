# 🔗 CareLink Pairing Flow — v0.4
### *Secure, nurse‑first bedside pairing between Patient Node and Nurse Node*

CareLink v0.4 refines the pairing mechanism to ensure safe, explicit, and nurse‑validated assignment of each Patient Node to a specific Nurse Node and bed identity.

The pairing process is designed to be simple, predictable, and fully aligned with real ward workflows.

---

## 1. 🛏️ Bed Identity Assignment

Each Patient Node receives two critical identifiers:

- **bed_id**  
- **nurse_mac**

These values are:

- configured via **Captive Portal**  
- validated for integrity  
- stored persistently in **EEPROM**  
- restored automatically on every boot  

This ensures each Patient Node always knows *which bed it represents* and *which nurse it must communicate with*.

---

## 2. 🔄 Pairing Handshake

When the Patient Node boots:

1. Loads `bed_id` and `nurse_mac` from EEPROM  
2. Initializes ESP‑NOW  
3. Sends a **pairing request** to the assigned Nurse Node  
4. Nurse Node validates:  
   - MAC address  
   - bed assignment  
   - pairing status  
5. Nurse Node replies with **pairing confirmation**  
6. Patient Node OLED displays:  
   **“Paired with Nurse Node”**  
7. Monitoring mode begins

If the Nurse Node does not respond:

- the Patient Node retries pairing  
- after timeout, the Captive Portal is re‑enabled for reconfiguration  

---

## 3. 🛡️ Safety Principles

CareLink enforces strict safety rules to prevent accidental or unsafe pairing:

- **No automatic pairing**  
  A Patient Node pairs only with the nurse explicitly configured.

- **No broadcast pairing**  
  Pairing requests are unicast to the assigned Nurse Node only.

- **Nurse‑first validation**  
  The nurse is always the first human in the loop.

- **Persistent storage with fallback defaults**  
  If EEPROM is corrupted, the node enters Captive Portal mode.

- **Explicit re‑assignment**  
  Changing bed or nurse requires a reset and manual confirmation.

---

## 4. 📝 Notes for v0.5

Planned enhancements:

- encrypted pairing tokens  
- QR‑based nurse assignment  
- multi‑nurse redundancy  
- cloud‑assisted pairing audit trail  



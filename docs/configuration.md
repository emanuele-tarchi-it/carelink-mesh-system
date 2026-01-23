# ⚙️ CareLink Configuration — v0.4

CareLink v0.4 introduces a unified and persistent configuration system for each Patient Node.  
Configuration is performed through a captive portal on first boot or after a factory reset.

---

## 🧩 1. Stored Parameters

The following values are stored persistently in EEPROM:

- **bed_id**  
  Numeric identifier for the patient’s bed.

- **nurse_mac**  
  ESP‑NOW MAC address of the assigned Nurse Node.

- **pairing_status**  
  Indicates whether the Patient Node has successfully paired.

- **Wi‑Fi credentials** *(reserved for v0.5)*  
  Not used in v0.4, but the structure is already allocated.

All parameters include corruption checks and safe defaults.

---

## 💾 2. Storage Model

Configuration is stored in EEPROM with:

- **integrity check** (simple signature)  
- **default fallback** if data is missing or corrupted  
- **atomic write** to avoid partial updates  
- **factory reset** via long‑press button  

This ensures the Patient Node always boots into a valid state.

---

## 🌐 3. Captive Portal Behavior

The Patient Node exposes a Wi‑Fi Access Point when:

- the device boots for the first time  
- EEPROM is empty or corrupted  
- a factory reset is triggered  

### Portal Fields

- **Bed ID**  
- **Nurse MAC Address**  
- **Save & Reboot**

### After saving:

- values are written to EEPROM  
- the device reboots automatically  
- the pairing handshake with the Nurse Node begins  

If pairing fails, the AP is re‑enabled for reconfiguration.

---

## 🔄 4. Reset Procedure

Hold the reset button for **5 seconds**:

- clears EEPROM  
- restores default configuration  
- restarts the Captive Portal  

This allows quick re‑assignment of a Patient Node to a different bed or nurse.

---

## 📝 5. Notes for v0.5

Planned improvements:

- WPA2‑protected AP  
- QR‑based provisioning  
- Wi‑Fi onboarding for cloud sync  
- encrypted configuration storage  


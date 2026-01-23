# 🌐 Captive Portal — v0.4

The Patient Node exposes a Wi‑Fi Access Point on first boot or after a factory reset.  
This allows bedside configuration without external tools or serial access.

---

## 📝 Portal Fields

- **Bed ID**  
  Unique numeric identifier for the patient’s bed.

- **Nurse MAC Address**  
  The ESP‑NOW MAC of the assigned Nurse Node.

- **Save & Reboot**  
  Commits configuration and restarts the device.

---

## ⚙️ Behavior

- After saving, all values are written to **EEPROM**  
- The device performs an **automatic reboot**  
- On startup, the Patient Node begins the **pairing handshake** with the Nurse Node  
- If pairing succeeds, the node enters **monitoring mode**  
- If pairing fails, the AP is re‑enabled for reconfiguration

---

## 📡 Access Point Details

- **SSID:** `CareLink-Setup`  
- **Security:** Open (v0.4)  
- **Portal:** Auto‑redirect captive portal  
- **Timeout:** AP shuts down after 5 minutes of inactivity

---

## 🔐 Notes for v0.5

- WPA2 AP  
- Optional password printed on OLED  
- Nurse discovery via broadcast  
- Cloud provisioning fallback


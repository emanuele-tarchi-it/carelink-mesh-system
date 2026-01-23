#include "storage_sd.h"
#include <FS.h>
#include <SD.h>
#include <vector>

// ============================================================
//  Inizializzazione SD
// ============================================================
bool initSD() {
    if (!SD.begin()) {
        M5.Lcd.setCursor(10, 200);
        M5.Lcd.setTextSize(2);
        M5.Lcd.setTextColor(RED);
        M5.Lcd.print("SD init failed");
        return false;
    }

    // Se il file non esiste, crealo con header v0.4
    if (!SD.exists("/pending.csv")) {
        File f = SD.open("/pending.csv", FILE_WRITE);
        if (f) {
            f.println("timestamp,bed_id,bpm,spo2,temperature,shock_index,alert_type");
            f.close();
        }
    }

    return true;
}

// ============================================================
//  Timestamp (stringa)
// ============================================================
String getTimestamp() {
    // Se RTC non configurato, usa millis()
    time_t now = time(nullptr);
    if (now < 100000) {
        return String(millis());
    }

    struct tm *t = localtime(&now);

    char buf[32];
    sprintf(buf, "%04d-%02d-%02d %02d:%02d:%02d",
            t->tm_year + 1900,
            t->tm_mon + 1,
            t->tm_mday,
            t->tm_hour,
            t->tm_min,
            t->tm_sec);

    return String(buf);
}

// ============================================================
//  Aggiunge una riga raw al file
// ============================================================
void appendLine(const String &line) {
    File f = SD.open("/pending.csv", FILE_APPEND);
    if (!f) return;

    f.println(line);
    f.close();
}

// ============================================================
//  Logga un pacchetto CareLink (v0.4)
// ============================================================
void logTelemetry(const carelink_msg_t &msg) {
    String line = "";

    line += getTimestamp();       line += ",";
    line += msg.bed_id;           line += ",";
    line += String(msg.bpm);      line += ",";
    line += String(msg.spo2);     line += ",";
    line += String(msg.temperature, 2); line += ",";
    line += String(msg.shock_index, 3); line += ",";
    line += String(msg.alert_type);

    appendLine(line);
}

// ============================================================
//  Legge tutte le righe in pending.csv
// ============================================================
std::vector<String> readPendingLines() {
    std::vector<String> lines;

    File f = SD.open("/pending.csv", FILE_READ);
    if (!f) return lines;

    while (f.available()) {
        String line = f.readStringUntil('\n');
        line.trim();
        if (line.length() > 0) {
            lines.push_back(line);
        }
    }

    f.close();
    return lines;
}

// ============================================================
//  Svuota pending.csv dopo sincronizzazione
// ============================================================
void clearPendingFile() {
    SD.remove("/pending.csv");

    File f = SD.open("/pending.csv", FILE_WRITE);
    if (f) {
        f.println("timestamp,bed_id,bpm,spo2,temperature,shock_index,alert_type");
        f.close();
    }
}
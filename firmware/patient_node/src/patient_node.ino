#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SparkFun_MAX3010x.h>

// --- Display settings ---
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// --- MAX30102 sensor ---
MAX30105 particleSensor;

// --- Bed ID (hardcoded per ora) ---
String bed_id = "B12";

// --- Blink management ---
unsigned long lastBlink = 0;
bool blinkState = false;

// --- Vitals ---
int spo2 = 97;
int bpm = 75;
bool spo2Valid = false;
bool bpmValid = false;

// --- Timing ---
unsigned long lastRead = 0;
const unsigned long readInterval = 500; // ms

// --- Funzione: mostra i parametri vitali sul display ---
void showVitals(int spo2, int bpm, String bed_id, bool spo2Valid, bool bpmValid) {
    bool spo2Critical = spo2Valid && (spo2 < 90);
    bool bpmCritical = bpmValid && (bpm < 50 || bpm > 120);
    bool critical = spo2Critical || bpmCritical;

    // Lampeggio in caso critico
    if (critical) {
        if (millis() - lastBlink > 300) {
            lastBlink = millis();
            blinkState = !blinkState;
            display.invertDisplay(blinkState);
        }
    } else {
        display.invertDisplay(false);
    }

    display.clearDisplay();

    // --- Fascia gialla (parte alta) ---
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.print("Bed: ");
    display.print(bed_id);

    display.setTextSize(2);
    display.setCursor(0, 12);

    if (critical) {
        if (spo2Critical) {
            display.print("SpO2 ");
            display.print(spo2);
            display.print("%");
        } else if (bpmCritical) {
            display.print("BPM ");
            display.print(bpm);
        }
    } else {
        // Nessun critico: fascia gialla solo per ID letto
        // (già stampato sopra)
    }

    // --- Fascia blu (parte bassa) ---
    if (!critical) {
        display.setTextSize(2);
        display.setCursor(0, 32);
        display.print("O2 ");
        if (spo2Valid) {
            display.print(spo2);
        } else {
            display.print("--");
        }

        display.setCursor(0, 52);
        display.print("HR ");
        if (bpmValid) {
            display.print(bpm);
        } else {
            display.print("--");
        }
    }

    display.display();
}

// --- Inizializzazione MAX30102 ---
bool setupMAX30102() {
    if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) {
        Serial.println("MAX30102 not found.");
        return false;
    }

    Serial.println("MAX30102 found.");

    particleSensor.setup(); // configurazione base SparkFun
    particleSensor.setPulseAmplitudeRed(0x0A);
    particleSensor.setPulseAmplitudeIR(0x0A);
    particleSensor.setPulseAmplitudeGreen(0); // non usato

    return true;
}

// --- Lettura semplificata di SpO2 e BPM ---
// Nota: per una lettura clinicamente affidabile servirebbe un algoritmo più complesso.
// Qui usiamo la logica base della libreria SparkFun.
void readVitals() {
    long irValue = particleSensor.getIR();

    if (irValue < 5000) {
        // dito non presente / segnale debole
        spo2Valid = false;
        bpmValid = false;
        return;
    }

    // Qui potresti integrare l'algoritmo di calcolo SpO2/BPM.
    // Per ora usiamo valori fittizi o derivati da funzioni demo.
    // Puoi sostituire questa parte con l'algoritmo reale quando pronto.

    // Placeholder: simulazione leggera per testare il layout
    static int fakeSpo2 = 97;
    static int fakeBpm = 75;

    // Piccola variazione per simulare
    fakeSpo2 += random(-1, 2);
    fakeBpm += random(-2, 3);

    if (fakeSpo2 < 85) fakeSpo2 = 85;
    if (fakeSpo2 > 99) fakeSpo2 = 99;

    if (fakeBpm < 50) fakeBpm = 50;
    if (fakeBpm > 130) fakeBpm = 130;

    spo2 = fakeSpo2;
    bpm = fakeBpm;
    spo2Valid = true;
    bpmValid = true;
}

void setup() {
    Serial.begin(115200);
    delay(1000);

    Serial.println("=== CareLink Patient Node v0.1 ===");
    Serial.println("HW-364A + OLED dual-color + MAX30102");
    Serial.println();

    // I2C: SDA = 14 (D5), SCL = 12 (D6)
    Wire.begin(14, 12);

    // Display
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println("SSD1306 allocation failed");
        for (;;);
    }

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("CareLink Patient Node");
    display.println("Init MAX30102...");
    display.display();

    // MAX30102
    if (!setupMAX30102()) {
        display.setCursor(0, 20);
        display.println("MAX30102 ERROR");
        display.display();
        while (true) {
            delay(1000);
        }
    }

    display.setCursor(0, 20);
    display.println("MAX30102 OK");
    display.display();
    delay(1000);
}

void loop() {
    if (millis() - lastRead > readInterval) {
        lastRead = millis();
        readVitals();
    }

    showVitals(spo2, bpm, bed_id, spo2Valid, bpmValid);

    delay(100);
}

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SparkFun_MAX30205.h>

extern "C" {
  #include "algorithm.h"
}

#include "carelink_protocol.h"

// -------------------------
//  HW & BUS CONFIG (HW-364A)
// -------------------------

#define I2C_SDA 14  // D5
#define I2C_SCL 12  // D6

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// MAX30102
#define MAX30102_ADDR 0x57

// MAX30205
MAX30205 tempSensor;
bool tempValid = false;
float temperatureC = 0.0f;

// Algoritmo Maxim
#define BUFFER_SIZE 100
uint32_t irBuffer[BUFFER_SIZE];
uint32_t redBuffer[BUFFER_SIZE];

int32_t spo2 = 0;
int8_t spo2Valid = 0;
int32_t heartRate = 0;
int8_t heartRateValid = 0;

// Blink / visual urgency
unsigned long lastBlink = 0;
bool blinkState = false;

// Bed ID (v0.2: hardcoded, v0.3: configurabile)
char bed_id[4] = "B12";

// -------------------------
//  MAX30102 low-level
// -------------------------

void max30102Write(uint8_t reg, uint8_t value) {
    Wire.beginTransmission(MAX30102_ADDR);
    Wire.write(reg);
    Wire.write(value);
    Wire.endTransmission();
}

void max30102ReadFIFO(uint32_t *ir, uint32_t *red) {
    Wire.beginTransmission(MAX30102_ADDR);
    Wire.write(0x07); // FIFO_DATA_REG
    Wire.endTransmission(false);
    Wire.requestFrom(MAX30102_ADDR, (uint8_t)6);

    if (Wire.available() == 6) {
        uint32_t un_red = 0;
        uint32_t un_ir = 0;

        un_red |= (uint32_t)Wire.read() << 16;
        un_red |= (uint32_t)Wire.read() << 8;
        un_red |= (uint32_t)Wire.read();
        un_red &= 0x03FFFF;

        un_ir |= (uint32_t)Wire.read() << 16;
        un_ir |= (uint32_t)Wire.read() << 8;
        un_ir |= (uint32_t)Wire.read();
        un_ir &= 0x03FFFF;

        *red = un_red;
        *ir = un_ir;
    }
}

void setupMAX30102() {
    max30102Write(0x09, 0x40); // reset
    delay(100);

    max30102Write(0x02, 0x00); // interrupts off
    max30102Write(0x03, 0x00);

    max30102Write(0x08, 0x4F); // FIFO config
    max30102Write(0x09, 0x03); // SpO2 mode
    max30102Write(0x0A, 0x27); // SpO2 config

    max30102Write(0x0C, 0x24); // LED RED
    max30102Write(0x0D, 0x24); // LED IR
}

// -------------------------
//  Clinical logic
// -------------------------

float computeShockIndex(int spo2Val, int bpmVal) {
    if (spo2Val <= 0) return 0.0f;
    return (float)bpmVal / (float)spo2Val;
}

bool checkInfectionAlert(float temp, int spo2Val, int bpmVal, float shockIndex) {
    if (temp <= 38.0f) return false;

    if (temp > 38.0f && bpmVal > 100) return true;
    if (temp > 38.0f && shockIndex > 1.0f) return true;
    if (temp > 38.0f && spo2Val < 94) return true;

    return false;
}

uint8_t computeAlertType(bool sosButton,
                         bool infectionAlert,
                         bool shockCritical) {
    if (sosButton) return ALERT_SOS;
    if (shockCritical) return ALERT_SHOCK;
    if (infectionAlert) return ALERT_INFECTION;
    return ALERT_NORM;
}

// -------------------------
//  Sensors read
// -------------------------

void readVitals() {
    for (int i = 0; i < BUFFER_SIZE; i++) {
        max30102ReadFIFO(&irBuffer[i], &redBuffer[i]);
        delay(10); // ~100 Hz
    }

    maxim_heart_rate_and_oxygen_saturation(
        irBuffer,
        BUFFER_SIZE,
        redBuffer,
        &spo2,
        &spo2Valid,
        &heartRate,
        &heartRateValid
    );
}

void readTemperature() {
    if (!tempValid) return;

    float t = tempSensor.readTemperature();
    if (t > 30.0f && t < 45.0f) {
        temperatureC = t;
    } else {
        tempValid = false;
    }
}

// -------------------------
//  Display
// -------------------------

void showVitals(const carelink_msg_t &msg,
                bool spo2Critical,
                bool shockCritical,
                bool tempCritical,
                bool infectionAlert) {

    bool critical = spo2Critical || shockCritical || tempCritical || infectionAlert;

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

    display.setTextSize(1);
    display.setCursor(0, 0);
    display.print("Bed: ");
    display.print(msg.bed_id);

    display.setTextSize(2);
    display.setCursor(0, 12);

    if (critical) {
        if (spo2Critical) {
            display.print("SpO2 ");
            display.print(msg.spo2);
        } else if (shockCritical) {
            display.print("sSI ");
            display.print(msg.shock_index, 2);
        } else if (tempCritical || infectionAlert) {
            display.print("TEMP ");
            display.print(msg.temperature, 1);
        }

        display.setTextSize(1);
        display.setCursor(0, 48);
        if (infectionAlert) display.print("INFECTION ALERT");
        else if (tempCritical) display.print("FEVER ALERT");
        else if (shockCritical) display.print("SHOCK ALERT");
        else if (spo2Critical) display.print("OXYGEN ALERT");

        display.display();
        return;
    }

    display.setTextSize(2);
    display.setCursor(0, 32);
    display.print("O2 ");
    display.print(msg.spo2);

    display.setCursor(0, 52);
    display.print("HR ");
    display.print(msg.bpm);

    display.setTextSize(1);
    display.setCursor(80, 32);
    display.print(msg.temperature, 1);
    display.print("C");

    display.display();
}

// -------------------------
//  Message build & send
// -------------------------

void buildMessage(carelink_msg_t &msg,
                  uint8_t alertType,
                  float shockIndex) {
    memcpy(msg.bed_id, bed_id, 4);
    msg.timestamp   = millis();
    msg.alert_type  = alertType;
    msg.bpm         = (heartRateValid ? (uint16_t)heartRate : 0);
    msg.spo2        = (spo2Valid ? (uint8_t)spo2 : 0);
    msg.temperature = (tempValid ? temperatureC : 0.0f);
    msg.shock_index = shockIndex;
}

void sendMessageSerial(const carelink_msg_t &msg) {
    Serial.write((const uint8_t *)&msg, sizeof(carelink_msg_t));
}

// -------------------------
//  SETUP
// -------------------------

void setup() {
    Serial.begin(115200);
    delay(200);

    Wire.begin(I2C_SDA, I2C_SCL);

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        while (true) delay(1000);
    }

    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("CareLink Patient Node");
    display.println("v0.2 Clinical Intelligence");
    display.display();

    setupMAX30102();

    if (!tempSensor.begin()) {
        tempValid = false;
    } else {
        tempValid = true;
    }

    delay(1000);
}

// -------------------------
//  LOOP
// -------------------------

void loop() {
    readVitals();
    readTemperature();

    int spo2Val = (spo2Valid ? spo2 : -1);
    int bpmVal  = (heartRateValid ? heartRate : -1);

    float shockIndex = computeShockIndex(spo2Val, bpmVal);

    bool spo2Critical   = spo2Valid && (spo2Val < 90);
    bool shockCritical  = (shockIndex > 1.2f);
    bool tempCritical   = tempValid && (temperatureC > 39.0f);
    bool infectionAlert = checkInfectionAlert(temperatureC, spo2Val, bpmVal, shockIndex);

    // v0.2: nessun pulsante SOS ancora
    bool sosButton = false;

    uint8_t alertType = computeAlertType(sosButton, infectionAlert, shockCritical);

    carelink_msg_t msg;
    buildMessage(msg, alertType, shockIndex);

    sendMessageSerial(msg);

    showVitals(msg, spo2Critical, shockCritical, tempCritical, infectionAlert);

    delay(200); // ~5 Hz
}

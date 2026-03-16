#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize LCD: address 0x27, 16 columns, 2 rows
LiquidCrystal_I2C lcd(0x27, 16, 2);

// --- Pin Definitions ---
const int PULSE_PIN = A0;
const int LED_PIN = 13;

// --- Signal Processing Variables ---
int signalValue = 0;
int threshold = 550;
int bpm = 0;

// --- Timing Variables ---
unsigned long lastBeatTime = 0;
unsigned long currentTime = 0;
unsigned long beatInterval = 0;
bool beatDetected = false;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Heart Rate Mon.");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
  delay(2000);
  lcd.clear();
}

void loop() {
  signalValue = simulatePulseSignal();
  currentTime = millis();

  if (signalValue > threshold && !beatDetected) {
    beatDetected = true;
    digitalWrite(LED_PIN, HIGH);

    beatInterval = currentTime - lastBeatTime;
    lastBeatTime = currentTime;

    if (beatInterval > 300 && beatInterval < 2000) {
      bpm = 60000 / beatInterval;
    }

    // Classify heart rate
    String status = "";
    if (bpm < 60) status = "Bradycardia";
    else if (bpm <= 100) status = "Normal";
    else status = "Tachycardia";

    lcd.setCursor(0, 0);
    lcd.print("BPM: ");
    lcd.print(bpm);
    lcd.print("       ");
    lcd.setCursor(0, 1);
    lcd.print(status);
    lcd.print("          ");

    Serial.print("BPM: ");
    Serial.print(bpm);
    Serial.print(" | Status: ");
    Serial.println(status);
  }

  if (signalValue < threshold) {
    beatDetected = false;
    digitalWrite(LED_PIN, LOW);
  }

  delay(10);
}

// Simulate a pulse sensor signal
int simulatePulseSignal() {
  float timeSeconds = millis() / 1000.0;
  float heartRateHz = 75.0 / 60.0;
  float wave = sin(2 * PI * heartRateHz * timeSeconds);
  return (int)(512 + 400 * wave);
}
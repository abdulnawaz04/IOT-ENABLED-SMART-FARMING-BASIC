/*
  IoT Enabled Smart Farming System
  Board: Arduino Uno
  Sensors: Soil Moisture (analog), DHT11, IR sensor
  Communication: SIM900A/SIM800-series GSM module (AT commands)

  Wiring (assumed):
    Soil moisture AO -> A0
    DHT11 DATA        -> D3
    IR sensor OUT     -> D2
    GSM TX            -> D7 (Arduino SoftwareSerial RX)
    GSM RX            -> D8 (Arduino SoftwareSerial TX, level-shift as required)
    Common GND between Arduino, sensors and GSM module

  IMPORTANT:
    - Replace the phone number below with the farmer's number in international format.
    - Power the GSM module from a suitable external supply; do not power it from
      the Arduino 5V pin. Check the exact module voltage/current requirements.
    - Calibrate dryValue and wetValue for your particular soil sensor.
    - This example sends an SMS once per minute. Adjust SMS_INTERVAL_MS as needed.
    - The IR sensor logic below assumes an active-LOW output when an object is detected.
*/

#include <SoftwareSerial.h>
#include <DHT.h>

#define SOIL_PIN A0
#define IR_PIN   2
#define DHT_PIN  3

#define DHT_TYPE DHT11
DHT dht(DHT_PIN, DHT_TYPE);

// SoftwareSerial constructor: (Arduino RX, Arduino TX)
SoftwareSerial gsm(7, 8);

const char PHONE_NUMBER[] = "+91XXXXXXXXXX"; // Replace with the farmer's number

// Example calibration values only. Read your sensor in dry and wet soil.
const int dryValue = 850;
const int wetValue = 350;

const int moistureThreshold = 30; // Percentage below which soil is reported as dry
const unsigned long SMS_INTERVAL_MS = 60000UL;

unsigned long previousSmsTime = 0;

void setup() {
  Serial.begin(9600);
  gsm.begin(9600);

  pinMode(IR_PIN, INPUT);
  dht.begin();

  Serial.println(F("IoT Smart Farming System"));
  Serial.println(F("Initializing GSM module..."));

  delay(3000);
  sendATCommand("AT", 1000);
  sendATCommand("ATE0", 1000);       // Disable command echo
  sendATCommand("AT+CMGF=1", 1000);  // Set SMS text mode

  Serial.println(F("System ready."));
}

void loop() {
  if (millis() - previousSmsTime >= SMS_INTERVAL_MS) {
    previousSmsTime = millis();
    readSensorsAndSendReport();
  }
}

void readSensorsAndSendReport() {
  const int soilRaw = analogRead(SOIL_PIN);

  // Map calibrated sensor readings to 0-100%.
  // If your sensor behaves in the opposite direction, swap dryValue/wetValue.
  int soilMoisture = map(soilRaw, dryValue, wetValue, 0, 100);
  soilMoisture = constrain(soilMoisture, 0, 100);

  const float temperature = dht.readTemperature();
  const float humidity = dht.readHumidity();

  // Many IR obstacle modules are active LOW; verify your module.
  const bool objectDetected = (digitalRead(IR_PIN) == LOW);

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println(F("Error: DHT sensor reading failed. Check wiring and sensor type."));
    return;
  }

  const char* soilStatus =
      (soilMoisture < moistureThreshold) ? "DRY - Water required" : "MOIST - Normal";
  const char* irStatus =
      objectDetected ? "Object detected" : "No object detected";

  Serial.println(F("--------------------------------"));
  Serial.print(F("Soil raw: "));
  Serial.println(soilRaw);
  Serial.print(F("Soil moisture: "));
  Serial.print(soilMoisture);
  Serial.println(F("%"));

  Serial.print(F("Temperature: "));
  Serial.print(temperature, 1);
  Serial.println(F(" C"));

  Serial.print(F("Humidity: "));
  Serial.print(humidity, 1);
  Serial.println(F("%"));

  Serial.print(F("IR status: "));
  Serial.println(irStatus);
  Serial.println(soilStatus);

  String message;
  message.reserve(180);
  message += F("SMART FARMING REPORT\n");
  message += F("Soil Moisture: ");
  message += String(soilMoisture);
  message += F("%\nTemperature: ");
  message += String(temperature, 1);
  message += F(" C\nHumidity: ");
  message += String(humidity, 1);
  message += F("%\nSoil Status: ");
  message += soilStatus;
  message += F("\nIR Sensor: ");
  message += irStatus;

  sendSMS(message);
}

void sendSMS(const String& message) {
  Serial.println(F("Sending SMS..."));

  gsm.println(F("AT+CMGF=1"));
  delay(500);

  gsm.print(F("AT+CMGS=\""));
  gsm.print(PHONE_NUMBER);
  gsm.println(F("\""));
  delay(1000);

  gsm.print(message);
  gsm.write(26); // Ctrl+Z sends the SMS

  delay(5000);
  Serial.println(F("SMS send command completed. Check GSM/network response if delivery fails."));
}

void sendATCommand(const __FlashStringHelper* command, unsigned long waitMs) {
  gsm.println(command);
  delay(waitMs);

  while (gsm.available()) {
    Serial.write(gsm.read());
  }
}

# IoT Enabled Smart Farming System

## Project Overview

The **IoT Enabled Smart Farming System** is an Arduino-based agricultural monitoring project designed to help farmers monitor important environmental and soil conditions.

The system uses sensors to collect real-time information about soil moisture, temperature, humidity and nearby object detection. 
A GSM module sends sensor information to the farmer through SMS notifications.

The main objective is to support efficient farming, improve monitoring and reduce the need for continuous manual observation.

## Objectives

- Monitor soil moisture levels.
- Measure temperature and humidity.
- Detect nearby objects using an IR sensor.
- Send farming information to farmers through GSM.
- Support better agricultural monitoring.

## Hardware Components

| Component | Purpose |
|---|---|
| Arduino Uno | Main controller |
| Soil Moisture Sensor | Measures soil moisture |
| DHT11 Sensor | Measures temperature and humidity |
| IR Sensor | Detects nearby objects |
| GSM Module (SIM900A/SIM800) | Sends SMS notifications |
| Jumper Wires | Hardware connections |
| Power Supply | Powers the system |

## Software Requirements

- Arduino IDE
- Arduino Uno Board Package
- DHT Sensor Library by Adafruit
- Adafruit Unified Sensor Library
- SoftwareSerial Library (included with Arduino AVR core)

## Working Principle

1. The soil moisture sensor measures the moisture level in the soil.
2. The DHT11 sensor measures temperature and humidity.
3. The IR sensor detects nearby objects.
4. Arduino Uno processes the collected sensor data.
5. The GSM module sends the monitoring report to the farmer through SMS.
6. Sensor readings are also displayed in the Arduino Serial Monitor.

## Circuit Connections

| Component | Arduino Pin |
|---|---|
| Soil Moisture Sensor AO | A0 |
| DHT11 Data | D3 |
| IR Sensor OUT | D2 |
| GSM TX | D7 |
| GSM RX | D8 |

**Note:** GSM TX connects to Arduino D7, and Arduino D8 connects to GSM RX. 
Use appropriate voltage-level conversion and an external power supply for the GSM module.

## Project Features

- Soil moisture monitoring
- Temperature monitoring
- Humidity monitoring
- IR-based object detection
- SMS notifications using GSM
- Periodic sensor data collection
- Serial Monitor output

## Installation and Setup

1. Download or clone this repository.
2. Open `IoT_Smart_Farming.ino` in Arduino IDE.
3. Install the required DHT libraries.
4. Connect the sensors and GSM module according to the circuit connections.
5. Update the farmer's mobile number in the Arduino code.
6. Calibrate the soil moisture sensor.
7. Select Arduino Uno and the correct COM port.
8. Upload the code to Arduino Uno.
9. Open Serial Monitor at 9600 baud.
10. Check sensor readings and GSM SMS functionality.

## Applications

- Agricultural monitoring
- Smart farming systems
- Soil moisture monitoring
- Greenhouse monitoring
- Remote farm monitoring

## Future Enhancements

- Automatic irrigation using a relay and water pump.
- Mobile application integration.
- Cloud-based sensor data storage.
- Live web dashboard.
- AI-based crop monitoring.
- Weather-based irrigation recommendations.

## Repository Structure

```text
IOT-ENABLED-SMART-FARMING-BASIC/
│
├── README.md
├── IoT_Smart_Farming.ino
└── LICENSE
```

## Conclusion

This project demonstrates how Internet of Things technology can be used in agriculture to improve monitoring and provide useful information to farmers. 
It combines Arduino, sensors and GSM communication to create a basic smart farming solution.

## Technologies Used

`Arduino` `IoT` `Embedded C++` `GSM` `Sensors` `Smart Agriculture`

---

**Note:** This repository contains an educational prototype. The hardware connections and sensor calibration may need adjustment depending on the modules used.

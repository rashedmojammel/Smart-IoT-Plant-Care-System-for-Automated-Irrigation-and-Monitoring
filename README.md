markdown

# 🌱 Smart IoT Plant Care System
### Automated Irrigation and Monitoring using NodeMCU ESP8266

> A microprocessor project by **Group 4 – Section M**  
> American International University – Bangladesh (AIUB)  
> Department of Computer Science & Engineering

---

## 👥 Team Members

| Name | Student ID |
|---|---|
| Rashedul Alam | 23-50536-1 |
| Shaikh Sameer | 23-50556-1 |
| Kallol Dey | 23-50540-1 |
| Md. Fazla Rabbi | 23-50062-1 |
| Zifanur Rahman | 23-50518-1 |

---

## 📖 Overview

The Smart IoT Plant Care System is an automated plant irrigation solution designed to reduce manual watering, conserve water, and keep plants healthy. It uses a NodeMCU ESP8266 microcontroller to collect real-time sensor data and control a water pump based on soil moisture levels. Users can monitor and manage the system remotely via the **Blynk IoT mobile app**.

The project supports the following UN Sustainable Development Goals:
- **SDG 6** – Clean Water and Sanitation
- **SDG 9** – Industry, Innovation, and Infrastructure
- **SDG 15** – Life on Land

---

## ✨ Features

- 💧 **Automatic irrigation** triggered when soil moisture drops below 35%
- 🌡️ **Temperature & humidity monitoring** via DHT11 sensor
- 🌧️ **Rain detection** to prevent unnecessary watering
- 🐾 **PIR motion detection** with buzzer alert for animal activity
- 📱 **Remote monitoring & control** through the Blynk mobile app
- 🖥️ **Real-time LCD display** of all sensor readings
- 🔘 **Manual override** via physical push button
- 🔋 **Battery-powered** (7.4V / 18650 rechargeable cells)

---

## 🔧 Hardware Components

| Component | Cost (BDT) |
|---|---|
| NodeMCU ESP8266 | 340 |
| Soil Moisture Sensor | 80 |
| Rain Drop Sensor | 80 |
| DHT11 Temperature & Humidity Sensor | 120 |
| 3.7V Lithium Battery × 2 | 78 each |
| 1-Channel 5V Relay Module | 85 |
| Mini Water Pump | 120 |
| 16×2 LCD Display (I2C) | 220 |
| Half-size Breadboard × 2 | 75 each |
| Jumper Wires M-M (20 pcs) | 60 |
| Jumper Wires M-F (20 pcs) | 60 |
| Buzzer | 20 |
| LED × 2 | 5 each |
| Push Button | 5 |
| **Total (approx.)** | **~1800 BDT** |

---

## 🏗️ System Architecture

```
Sensors                NodeMCU ESP8266           Outputs
─────────              ───────────────           ───────
Soil Moisture  ──────▶                  ──────▶  Water Pump (via Relay)
DHT11          ──────▶   Processes &   ──────▶  16×2 LCD Display
Rain Drop      ──────▶   Controls      ──────▶  LED Indicators
PIR Motion     ──────▶                  ──────▶  Buzzer
                              │
                              ▼
                       Blynk IoT App
                    (Remote Monitoring)
```

---

## ⚙️ How It Works

1. The **soil moisture sensor** continuously reads soil dryness levels.
2. If moisture falls **below 35%**, the relay activates the water pump automatically.
3. If moisture is **above 35%**, the pump switches off.
4. The **rain sensor** detects rainfall and halts irrigation, sending a "Rain Detected" notification.
5. The **PIR sensor** detects nearby motion and triggers the buzzer + a "Motion Detected" push notification.
6. The **DHT11 sensor** monitors ambient temperature and humidity, displayed on the LCD.
7. All data is streamed live to the **Blynk dashboard** for remote viewing and manual control.

---

## 📱 Blynk Dashboard

The mobile dashboard displays:
- Real-time **temperature** and **humidity**
- Current **soil moisture** level
- **Rain** and **motion** detection status
- Manual **pump switch** and **PIR switch** controls

---

## 🧪 Simulation

Components were individually simulated in **Proteus** using the Arduino IDE:

| Sensor | Result |
|---|---|
| Soil Moisture | Displays moisture % on LCD |
| PIR Motion | Shows "Motion!" / "No Motion" |
| Rain Drop | Shows "Rain Detected" / "No Rain" |
| DHT11 | Displays temperature & humidity |
| Water Pump (Relay) | Toggles ON/OFF based on moisture threshold |

---

## ⚠️ Limitations

- Sensor readings (soil moisture, rain) may not always be highly precise
- Battery requires frequent recharging for continuous or large-scale use
- Remote monitoring via Blynk requires an active internet connection
- Light rainfall may not be reliably detected by the rain sensor
- Manual intervention still needed for troubleshooting and sensor recalibration
- Scaling to commercial farm size increases cost significantly

---

## 🔮 Future Improvements

- Add **light, pH, and nutrient sensors** for deeper plant health monitoring
- Integrate **weather forecast APIs** for predictive irrigation
- Incorporate **solar power** for off-grid energy efficiency
- Apply **machine learning** for AI-driven irrigation scheduling
- Support **multi-zone irrigation** management
- Enhance the mobile app with **scheduling and data analytics** features

---

## 📚 References

Full references are listed in the project report. Key related works include studies on Arduino-based irrigation, NodeMCU + Blynk plant watering systems, ESP32 home automation, and solar-powered IoT irrigation published across IEEE Xplore, Procedia Computer Science, and various international engineering journals (2016–2024).

---

## 📄 License

This project was developed for academic purposes at AIUB. All rights reserved by the project team.

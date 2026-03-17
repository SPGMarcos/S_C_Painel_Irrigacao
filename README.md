# 🌱 Smart Irrigation Panel

A local-first irrigation controller built with ESP8266, designed to keep working even without internet or MQTT.

---

## 📸 Hardware Setup
  
![Panel](images/hardware.jpg)

---

## 🎯 Why I built this

I needed a reliable irrigation system that wouldn't depend on cloud services or stop working if the connection failed.

Most solutions rely heavily on external systems, so I designed this to run fully locally, with MQTT and Home Assistant as optional layers.

---

## 🔧 What it does

- Controls 2 independent solenoid valves  
- Runs up to 3 scheduled irrigation cycles per day  
- Works fully offline (no cloud required)  
- Optional MQTT integration with Home Assistant  
- Web interface for configuration and control  
- Stores all settings locally (survives reboot and power loss)  

---

## 🔄 How it works

- The user sets schedules using the web interface  
- Configuration is stored in LittleFS  
- Time is synchronized using NTP  
- Every minute, the system checks if a cycle should start  
- Relays are triggered with a small delay to protect the hardware  

Basic logic used:

```cpp

🧠 System Architecture
Local mode

User
↓
Web Interface (ESP8266)
↓
Internal HTTP Server
↓
Control Logic
↓
Relays → Valves

With Home Assistant

Home Assistant
↓
MQTT Broker
↓
ESP8266
↓
Relay Module (Serial)
↓
Valves

⚙️ Key Features
Manual control

Independent valve control

Real-time updates

MQTT state sync

Scheduled automation

Up to 3 daily cycles

Minute-based comparison (no external scheduler)

Both valves can run together

1s delay between activations (hardware protection)

Time sync

Uses pool.ntp.org

Updates every 60 seconds

Configured timezone (Brazil)

Persistence

Uses LittleFS (/config.txt)

Stores schedules, states and MQTT config

Recovers automatically after reboot

WiFi provisioning

Uses WiFiManager

Creates ESP_Irrigacao AP if no Wi-Fi is saved

No hardcoded credentials needed

📡 Home Assistant Integration

Uses MQTT Discovery to automatically create entities:

Valve 1

Valve 2

Topics:

irrigacao_esp/v1/state
irrigacao_esp/v1/set
irrigacao_esp/v2/state
irrigacao_esp/v2/set

Auto discovery:

homeassistant/switch/irrigacao_esp_v1/config
homeassistant/switch/irrigacao_esp_v2/config

This allows:

Auto detection in Home Assistant

State synchronization

Bidirectional control

🌐 Web Interface

Dark-themed responsive interface with:

Toggle switches

Schedule configuration

Cycle control

Auto refresh (5s)

Advanced settings

Factory reset

Built using:

HTML5

CSS

JavaScript (Fetch API)

JSON

PROGMEM (RAM optimization)

🔌 Hardware

ESP8266

2-channel relay module (serial protocol 0xA0)

5V power supply

127V/220V solenoid valves

🔄 Relay Communication

Serial protocol:

[A0][Relay][State][Checksum]

Example:

byte cmd[4] = {0xA0, relay, state, checksum};
🛡️ Reliability Features

Delay between valve activation

Internal state control (isIrrigating)

Automatic MQTT reconnection

Local persistence (power loss safe)

Web-based factory reset

⚙️ Design Decisions

ESP8266 for low cost and Wi-Fi capability

Local-first architecture (no cloud dependency)

MQTT is optional, not required

LittleFS instead of EEPROM for flexibility

Serial relay module to simplify wiring

⚠️ Limitations

No sensor feedback yet (time-based irrigation only)

Requires Wi-Fi for MQTT features

No remote access without external setup

🌍 Real Use Cases

Home gardens

Small farms

Greenhouses

📈 Future Improvements

Soil moisture sensors

Individual valve scheduling

LoRa remote control

Weather-based automation

Advanced dashboard

👨‍💻 Author

Marcos Gabriel Ferreira Miranda
IoT Developer | Residential and Agricultural Automation
Belo Horizonte - MG
int cur = timeClient.getHours() * 60 + timeClient.getMinutes();

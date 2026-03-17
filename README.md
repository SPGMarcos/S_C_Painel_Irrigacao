# S_C_Painel_Irrigacao
🌱 Smart Irrigation Panel

ESP8266 + MQTT + Home Assistant + Web Interface
Smart panel for controlling 2 solenoid valves with scheduled automation and native integration with Home Assistant.

📌 Overview

This project consists of a smart irrigation panel based on ESP8266, capable of:

Controlling 2 independent solenoid valves

Running built-in scheduled automation

Automatically integrating with Home Assistant via MQTT Discovery

Providing a responsive web interface

Storing configurations locally

Synchronizing time via NTP

Operating autonomously or integrated with Home Assistant

The system can operate in:

100% local mode (web interface only)

Integrated with Home Assistant

Hybrid mode (manual + automatic + HA)

🎯 Project Goal

Develop an irrigation controller that is:

Cloud-independent

Configurable via browser

Persistent after reboot

Integrable with automation systems

Safe against power loss

Modular and scalable

🧠 System Architecture
User
  ↓
Web Interface (ESP8266)
  ↓
Internal HTTP Server
  ↓
Embedded Logic
  ↓
Relays (Valve 1 and 2)

Home Assistant mode:

Home Assistant
      ↓
    MQTT Broker
      ↓
    ESP8266
      ↓
  Serial Relay Board
      ↓
 Solenoid Valves
🔌 Hardware Used

ESP8266

2-channel relay module (with serial protocol 0xA0)

Stabilized 5V power supply

127V/220V solenoid valves

Physical enclosure panel

⚙️ Main Features
🔹 1. Manual Control

Individual control of each valve

Real-time updates

MQTT synchronization

🔹 2. Scheduled Automation

Up to 3 daily cycles

Configurable schedules via interface

Current minute-based comparison

Simultaneous activation of both valves

1-second delay between activations (electrical protection)

Logic:

int cur = timeClient.getHours() * 60 + timeClient.getMinutes();

Avoids external dependency for timing.

🔹 3. NTP Time Sync

Synchronization with pool.ntp.org

Updates every 60 seconds

Configured timezone (-10800 for Brazil)

🔹 4. Persistence with LittleFS

Stores:

Schedules

Active cycles

Automation state

MQTT configuration

Saved file:

/config.txt

Ensures the system restarts with the last valid configuration.

🔹 5. WiFiManager

Automatic provisioning

Creates "ESP_Irrigacao" network if no Wi-Fi is saved

Intuitive configuration portal

Eliminates the need for hardcoded network credentials.

🔹 6. Home Assistant Integration (MQTT Discovery)

The system automatically creates 2 entities:

Valve 1

Valve 2

Topics:

irrigacao_esp/v1/state
irrigacao_esp/v1/set
irrigacao_esp/v2/state
irrigacao_esp/v2/set

Auto Discovery:

homeassistant/switch/irrigacao_esp_v1/config
homeassistant/switch/irrigacao_esp_v2/config

This enables:

Automatic recognition

State synchronization

Bidirectional control

🌐 Web Interface

Modern dark-themed interface with:

Animated switches

Cycle control

Schedule selection

Auto refresh every 5 seconds

Advanced settings page

Factory reset

Technologies used:

HTML5

Custom CSS

Fetch API

JSON

Dynamic JavaScript

PROGMEM for RAM optimization

🔄 Relay Communication Protocol

Format sent via Serial:

[A0][Relay][State][Checksum]

Example:

byte cmd[4] = {0xA0, relay, state, checksum};

Ensures basic message integrity.

🛡️ Safety and Stability Mechanisms

Delay between valve activations

Internal state control (isIrrigating)

Automatic MQTT reconnection

Persistence in case of power loss

Web-based factory reset

Natural loop watchdog

📡 mDNS

Allows access via:

http://esp_irrigacao.local

No need for a fixed IP.

📈 Scalability

The system was designed for future expansion:

Individual cycle control

Soil moisture sensors

Remote control via LoRa

Advanced dashboard

Weather integration

Seasonal control

📊 Technical Highlights

✔ Automatic MQTT integration
✔ Hybrid architecture (local + HA)
✔ Embedded responsive interface
✔ Autonomous system
✔ Embedded persistence
✔ Smart provisioning
✔ Modular code

👨‍💻 Author

Marcos Gabriel Ferreira Miranda

IoT Developer | Residential and Agricultural Automation

Belo Horizonte - MG

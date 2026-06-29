<div align="center">

<img src="https://raw.githubusercontent.com/NEXALAB-ID/.github/main/assets/banner.png" width="100%" alt="NEXALAB ID Banner"/>

<p>&nbsp;</p>

[![Organization](https://img.shields.io/badge/GitHub-NEXALAB--ID-0ea5e9?style=for-the-badge&logo=github&logoColor=white)](https://github.com/NEXALAB-ID)
[![Board](https://img.shields.io/badge/Board-ESP32-000000?style=for-the-badge&logo=espressif&logoColor=white)](#)
[![Language](https://img.shields.io/badge/Language-C++-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)](#)
[![License](https://img.shields.io/badge/License-MIT-22c55e?style=for-the-badge)](#)

</div>

<br/>

---

## About

**esp32-ota** is a collection of ESP32 Over-the-Air (OTA) firmware update examples. OTA allows you to update your ESP32 firmware wirelessly without a physical USB connection — useful for deployed devices that are difficult to access directly.

---

## Contents

| Example | Description |
|:--------|:------------|
| **BasicOTA** | Update firmware directly from Arduino IDE over WiFi |
| **OTA_WebServer** | Update firmware by uploading a `.bin` file via a browser |
| **OTA_GitHub** | Pull and flash firmware directly from a GitHub release |

---

## Notes

> **WiFi Credentials Warning** — Do not commit your actual WiFi credentials to GitHub. Replace `YOUR_SSID` and `YOUR_PASSWORD` locally, and revert before pushing.

> **OTA_GitHub Firmware URL** — Replace `YOUR_FIRMWARE_URL` with the direct download URL of your `.bin` file from a GitHub Release. Do not commit the actual URL if it contains sensitive tokens.

---

## Requirements

- ESP32 board (any variant)
- [Arduino IDE](https://www.arduino.cc/en/software) with ESP32 board support installed
- Libraries:
  - `WiFi.h` — built-in with ESP32 Arduino core
  - `ArduinoOTA.h` — built-in with ESP32 Arduino core
  - `WebServer.h` — built-in with ESP32 Arduino core
  - `HTTPClient.h` — built-in with ESP32 Arduino core
  - `Update.h` — built-in with ESP32 Arduino core

---

## Getting Started

1. Clone this repository
   ```bash
   git clone https://github.com/NEXALAB-ID/esp32-ota.git
   ```
2. Open the example you want in Arduino IDE
3. Replace `YOUR_SSID` and `YOUR_PASSWORD` with your WiFi credentials
4. Select your ESP32 board under **Tools → Board**
5. Upload via USB for the first time — subsequent updates can be done via OTA

---

## How Each Example Works

**BasicOTA**
Upload the sketch via USB first. After that, your ESP32 will appear as a network port in Arduino IDE. Select it under **Tools → Port** and upload new sketches wirelessly.

**OTA_WebServer**
After uploading, open a browser and go to the IP address shown in Serial Monitor. Upload a compiled `.bin` file through the web interface to update the firmware.

**OTA_GitHub**
The ESP32 fetches a `.bin` firmware file from a GitHub Release URL on boot and flashes itself automatically. Useful for automatic updates on deployed devices.

---

## Project Structure

```
esp32-ota/
├── BasicOTA/
│   └── BasicOTA.ino
├── OTA_WebServer/
│   └── OTA_WebServer.ino
└── OTA_GitHub/
    └── OTA_GitHub.ino
```

---

## Contributing

Found a bug or want to add more OTA examples? Feel free to open a [Discussion](https://github.com/NEXALAB-ID/discussions/discussions) or submit a Pull Request.

---

<div align="center">

<sub>Part of NEXALAB ID &nbsp;·&nbsp; <strong>Innovate | Build | Connect</strong></sub>

</div>

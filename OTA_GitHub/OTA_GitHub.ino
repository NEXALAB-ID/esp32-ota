// NOTE: Do not commit your actual WiFi credentials to GitHub.
// Replace YOUR_SSID, YOUR_PASSWORD, and YOUR_FIRMWARE_URL locally, and revert before pushing.

#include <WiFi.h>
#include <HTTPClient.h>
#include <Update.h>

const char* ssid         = "YOUR_SSID";
const char* password     = "YOUR_PASSWORD";
const char* firmware_url = "YOUR_FIRMWARE_URL";
// Example: "https://github.com/NEXALAB-ID/esp32-ota/releases/download/v1.0.0/firmware.bin"

void connectWiFi() {
  Serial.print("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");
}

void performOTA() {
  HTTPClient http;
  http.begin(firmware_url);
  http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);

  int httpCode = http.GET();

  if (httpCode == HTTP_CODE_OK) {
    int contentLength = http.getSize();
    Serial.printf("Firmware size: %d bytes\n", contentLength);

    if (!Update.begin(contentLength)) {
      Update.printError(Serial);
      return;
    }

    WiFiClient* stream = http.getStreamPtr();
    size_t written = Update.writeStream(*stream);
    Serial.printf("Written: %u bytes\n", written);

    if (Update.end()) {
      Serial.println("OTA Update Complete! Rebooting...");
      delay(1000);
      ESP.restart();
    } else {
      Update.printError(Serial);
    }
  } else {
    Serial.printf("HTTP Error: %d\n", httpCode);
  }

  http.end();
}

void setup() {
  Serial.begin(115200);
  connectWiFi();

  Serial.println("Checking for firmware update...");
  performOTA();
}

void loop() {
  // Nothing here — OTA runs once on boot
}

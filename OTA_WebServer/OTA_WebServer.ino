// NOTE: Do not commit your actual WiFi credentials to GitHub.
// Replace YOUR_SSID and YOUR_PASSWORD locally, and revert before pushing.

#include <WiFi.h>
#include <WebServer.h>
#include <Update.h>

const char* ssid     = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

WebServer server(80);

const char* upload_page = R"(
<!DOCTYPE html>
<html>
<head>
  <title>NEXALAB OTA Update</title>
  <style>
    body { font-family: Arial, sans-serif; text-align: center; margin-top: 50px; background: #0a0a0f; color: #fff; }
    h1 { color: #38bdf8; }
    input[type=file] { margin: 20px; }
    input[type=submit] { background: #38bdf8; color: #000; border: none; padding: 10px 24px; cursor: pointer; font-size: 16px; border-radius: 4px; }
  </style>
</head>
<body>
  <h1>NEXALAB ESP32 OTA Update</h1>
  <form method="POST" action="/update" enctype="multipart/form-data">
    <input type="file" name="firmware" accept=".bin"><br/>
    <input type="submit" value="Upload Firmware">
  </form>
</body>
</html>
)";

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected!");
  Serial.print("Open browser at: http://");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, []() {
    server.send(200, "text/html", upload_page);
  });

  server.on("/update", HTTP_POST, []() {
    server.send(200, "text/plain", Update.hasError() ? "Update Failed!" : "Update Success! Rebooting...");
    delay(1000);
    ESP.restart();
  }, []() {
    HTTPUpload& upload = server.upload();
    if (upload.status == UPLOAD_FILE_START) {
      Serial.printf("Uploading: %s\n", upload.filename.c_str());
      if (!Update.begin(UPDATE_SIZE_UNKNOWN)) Update.printError(Serial);
    } else if (upload.status == UPLOAD_FILE_WRITE) {
      if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) Update.printError(Serial);
    } else if (upload.status == UPLOAD_FILE_END) {
      if (Update.end(true)) Serial.printf("Update Success! Size: %u bytes\n", upload.totalSize);
      else Update.printError(Serial);
    }
  });

  server.begin();
  Serial.println("OTA Web Server Ready!");
}

void loop() {
  server.handleClient();
}

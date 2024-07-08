#include "ota.h"
#include "configs.h"
#include "screen.h"

void createAP()
{
  if (getConfig("ota") == "1")
  {
    waitScreen();
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
      delay(500);
      Serial.print(".");
    }
    wellcome();
  }
}

void updateCodeOta()
{
  if (getConfig("ota") == "1")
  {
    
  }
}

void update_started() {
  Serial.println("CALLBACK:  HTTP update process started");
}

void update_finished() {
  Serial.println("CALLBACK:  HTTP update process finished");
}

void update_progress(int cur, int total) {
  Serial.printf("CALLBACK:  HTTP update process at %d of %d bytes...\n", cur, total);
}

void update_error(int err) {
  Serial.printf("CALLBACK:  HTTP update fatal error code %d\n", err);
}

void otaHandle()
{
  if (getConfig("ota") == "1")
  {
    Serial.println("Update SPIFFS...");

    WiFiClient client;

    t_httpUpdate_return ret = httpUpdate.updateSpiffs(client, PATH_SPIFFS);
    if (ret == HTTP_UPDATE_OK) {
      Serial.println("Update sketch...");
      ret = httpUpdate.update(client,  PATH_FIRMWARE);

      switch (ret) {
        case HTTP_UPDATE_FAILED:
          Serial.printf("HTTP_UPDATE_FAILED Error (%d): %s", httpUpdate.getLastError(), httpUpdate.getLastErrorString().c_str());
          break;

        case HTTP_UPDATE_NO_UPDATES:
          Serial.println("HTTP_UPDATE_NO_UPDATES");
          break;

        case HTTP_UPDATE_OK:
          Serial.println("HTTP_UPDATE_OK");
          break;
      }
    }
  }
}
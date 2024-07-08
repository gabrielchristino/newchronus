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
    File file = SPIFFS.open("/firmware.bin");
    if (file)
    {
      Serial.println("delete file");
      SPIFFS.remove("/firmware.bin");
    }

    file.close();

    HTTPClient http;
    http.begin(PATH);
    int httpCode = http.GET();

    if (httpCode == HTTP_CODE_OK)
    {
      String firmwareData = http.getString();
      file = SPIFFS.open("/firmware.bin", FILE_WRITE);
      if (!file)
      {
        SPIFFS.remove("/firmware.bin");
        Serial.println("Failed to open file for writing");
        return;
      }
      file.print(firmwareData);
      file.close();
      Serial.println("Firmware downloaded and saved to SPIFFS");

      file = SPIFFS.open("/firmware.bin");

      if (!file)
      {
        saveConfig("ota", "0");
        SPIFFS.remove("/firmware.bin");
        Serial.println("Failed to open file for reading");
        return;
      }

      Serial.println("Starting update..");

      size_t fileSize = file.size();
      Serial.println(fileSize);

      if (!Update.begin(UPDATE_SIZE_UNKNOWN))
      {
        saveConfig("ota", "0");
        SPIFFS.remove("/firmware.bin");
        Serial.println("Cannot do the update");
        return;
      };

      Update.write(file);

      if (Update.end())
      {
        SPIFFS.remove("/firmware.bin");
        Serial.println("Successful update");
      }
      else
      {
        saveConfig("ota", "0");
        SPIFFS.remove("/firmware.bin");
        Serial.println("Error Occurred: " + String(Update.getError()));
        return;
      }

      file.close();

      saveConfig("ota", "0");
      SPIFFS.remove("/firmware.bin");

      Serial.println("Reset in 4 seconds...");
      delay(4000);

      ESP.restart();
    }
    else
    {
      Serial.println("Error downloading firmware");
    }
    http.end();
  }
}

void otaHandle()
{
  if (getConfig("ota") == "1")
  {
  }
}
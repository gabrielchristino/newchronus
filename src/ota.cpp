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
    HTTPClient http;
    http.begin(PATH);
    int httpCode = http.GET();

    if (httpCode == HTTP_CODE_OK)
    {
      Serial.println("Firmware downloaded and saved to SPIFFS");

      Serial.println("Starting update..");

      size_t fileSize = http.getString().length();
      Serial.println(fileSize);

      if (!Update.begin(UPDATE_SIZE_UNKNOWN))
      {
        saveConfig("ota", "0");
        Serial.println("Cannot do the update");
        return;
      };
  
      Update.writeStream(http.getStream());

      if (Update.end())
      {
        Serial.println("Successful update");
      }
      else
      {
        saveConfig("ota", "0");
        Serial.println("Error Occurred: " + String(Update.getError()));
        return;
      }


      saveConfig("ota", "0");

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
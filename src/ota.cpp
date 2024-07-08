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
    WiFiClient otaClient;
    HTTPClient http;
    http.begin(PATH);
    int httpCode = http.GET();

    if (httpCode == HTTP_CODE_OK)
    {

      saveConfig("ota", "0");

      Serial.println("Starting update..");

      size_t fileSize = http.getString().length();
      Serial.println(fileSize);
      t_httpUpdate_return hur;
      hur = httpUpdate.update(otaClient, PATH);

      switch (hur)
      {
      case HTTP_UPDATE_FAILED:
        Serial.printf("HTTP_UPDATE_FAILED Error (%d): %s\n\n",
                      httpUpdate.getLastError(), httpUpdate.getLastErrorString().c_str());
        break;
      case HTTP_UPDATE_NO_UPDATES:
        Serial.println("HTTP_UPDATE_NO_UPDATES\n");
        break;
      case HTTP_UPDATE_OK:

        Serial.println("Reset in 4 seconds...");
        delay(4000);

        ESP.restart();
        break;
      }
    }
    else
    {
      saveConfig("ota", "0");
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
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

void otaHandle()
{
  if (getConfig("ota") == "1")
  {
    WiFiClient client;
    t_httpUpdate_return ret = httpUpdate.update(client, PATH);
    // Or:
    //t_httpUpdate_return ret = httpUpdate.update(client, "server", 80, "/file.bin");

    switch (ret) {
      case HTTP_UPDATE_FAILED:
        Serial.printf("HTTP_UPDATE_FAILED Error (%d): %s\n", httpUpdate.getLastError(), httpUpdate.getLastErrorString().c_str());
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
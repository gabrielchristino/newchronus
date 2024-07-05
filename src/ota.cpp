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
  }
}
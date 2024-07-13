#include "ota.h"
#include "configs.h"
#include "screen.h"

WiFiMulti wifiMulti;

void createAP()
{
  if (getConfig("ota") == "1")
  {
    saveConfig("ota", "0");
    waitScreen();
    // wifiMulti.addAP(getWifi("ssid1").c_str(), getWifi("passwd1").c_str());
    // wifiMulti.addAP(getWifi("ssid2").c_str(), getWifi("passwd2").c_str());

    // while (wifiMulti.run() != WL_CONNECTED)
    // {
    //   delay(500);
    //   Serial.print(".");
    // }
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
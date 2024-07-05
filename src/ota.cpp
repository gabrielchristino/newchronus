#include "ota.h"
#include "configs.h"
#include "screen.h"

void createAP()
{
  if (getConfig("ota") == "1")
  {
    // Begin connecting to WiFi using the provided SSID and password
    WiFi.begin(ssid, password);

    // Display connection progress
    Serial.print("Connecting to WiFi");

    // Wait until WiFi is connected
    while (WiFi.status() != WL_CONNECTED)
    {
      delay(500);
      Serial.print(".");
    }

    // Print confirmation message when WiFi is connected
    Serial.println("WiFi connected");
    wellcome();
  }
}

void HttpEvent(HttpEvent_t *event)
{
  switch (event->event_id)
  {
  case HTTP_EVENT_ERROR:
    Serial.println("Http Event Error");
    break;
  case HTTP_EVENT_ON_CONNECTED:
    Serial.println("Http Event On Connected");
    break;
  case HTTP_EVENT_HEADER_SENT:
    Serial.println("Http Event Header Sent");
    break;
  case HTTP_EVENT_ON_HEADER:
    Serial.printf("Http Event On Header, key=%s, value=%s\n", event->header_key, event->header_value);
    break;
  case HTTP_EVENT_ON_DATA:
    break;
  case HTTP_EVENT_ON_FINISH:
    Serial.println("Http Event On Finish");
    break;
  case HTTP_EVENT_DISCONNECTED:
    Serial.println("Http Event Disconnected");
    break;
  }
}

void updateCodeOta()
{
  if (getConfig("ota") == "1")
  {
    HttpsOTA.onHttpEvent(HttpEvent);
    Serial.println("Starting OTA");
    HttpsOTA.begin(PATH, server_certificate);

    Serial.println("Please Wait it takes some time ...");
  }
}

void otaHandle()
{
  if (getConfig("ota") == "1")
  {
    otastatus = HttpsOTA.status();
    if (otastatus == HTTPS_OTA_SUCCESS)
    {
      Serial.println("Firmware written successfully. To reboot device, call API ESP.restart() or PUSH restart button on device");
    }
    else if (otastatus == HTTPS_OTA_FAIL)
    {
      Serial.println("Firmware Upgrade Fail");
    }
  }
}
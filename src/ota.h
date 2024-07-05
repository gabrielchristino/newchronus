#include <WiFi.h>
#include <SPIFFS.h>
#include "Update.h"
#include <WiFiClientSecure.h>

// Define WiFi credentials
#define ssid "SSID"
#define password "PASSWORD"

// Define server details and file path
#define HOST "raw.githubusercontent.com"
#define PATH "/gabrielchristino/newchronus/develop/.pio/build/esp32doit-devkit-v1/firmware.bin"
#define PORT 443

// Define the name for the downloaded firmware file
#define FILE_NAME "firmware.bin"

void createAP();
void updateCodeOta();
void otaHandle();
void performOTAUpdateFromSPIFFS();
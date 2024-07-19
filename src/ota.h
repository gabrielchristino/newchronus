#include <WiFi.h>
#include <WiFiMulti.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <Update.h>


// Define server details and file path
#define PATH_FIRMWARE "https://raw.githubusercontent.com/gabrielchristino/newchronus/develop/.pio/build/esp32doit-devkit-v1/firmware.bin"
#define PATH_SPIFFS "https://raw.githubusercontent.com/gabrielchristino/newchronus/develop/.pio/build/esp32doit-devkit-v1/spiffs.bin"

void createAP();
void updateCodeOta();
void otaHandle();

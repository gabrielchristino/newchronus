#include <WiFi.h>

#include <HTTPClient.h>
#include <HTTPUpdate.h>

// Define WiFi credentials
#define ssid "iPhone"
#define password "mmmm0000"

// Define server details and file path
#define PATH "https://raw.githubusercontent.com/gabrielchristino/newchronus/develop/.pio/build/esp32doit-devkit-v1/firmware.bin"

void createAP();
void updateCodeOta();
void otaHandle();

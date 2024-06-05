#include <Arduino.h>
#include <SPIFFS.h>

// #define OTA_ENABLED
// #define SERIAL_ENABLED

void initSPIFFS();
String searchForKey(File file, String key);
String getConfig(String key);
void replaceLine(File file, String startOfLine, String newLine);
void saveConfig(String key, String value);
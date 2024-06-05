#include <configs.h>
#define CONFIG_FILE "/config.txt"

void initSPIFFS()
{
  SPIFFS.begin(true);
}

String searchForKey(File file, String key)
{
  String line;
  while (file.available())
  {
    line = file.readStringUntil('\n');
    int index = line.indexOf(key);
    if (index != -1)
    {
      return line.substring(index + key.length() + 1);
    }
  }
  return "";
}

String getConfig(String key)
{
  File file = SPIFFS.open(CONFIG_FILE, FILE_READ);
  String configData = searchForKey(file, key);
  file.close();
  return configData;
}

void replaceLine(File file, String startOfLine, String newLine)
{
  String buffer;
  String line;
  while (file.available())
  {
    line = file.readStringUntil('\n');
    if (line.startsWith(startOfLine))
    {
      buffer += newLine + "\n";
    }
    else
    {
      buffer += line + "\n";
    }
  }

  file.close();

  file = SPIFFS.open(CONFIG_FILE, FILE_WRITE);

  file.print(buffer);
  file.close();
}

void saveConfig(String key, String value)
{
  File file = SPIFFS.open(CONFIG_FILE, FILE_READ);
  replaceLine(file, key, key + ":" + value);
  file.close();
}
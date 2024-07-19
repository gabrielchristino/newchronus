#include "ota.h"
#include "configs.h"
#include "screen.h"

WiFiMulti wifiMulti;


WebServer server(80);

const char* serverIndex =
"<script src='https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js'></script>"
"<form method='POST' action='#' enctype='multipart/form-data' id='upload_form'>"
   "<input type='file' name='update'>"
        "<input type='submit' value='Update'>"
    "</form>"
 "<div id='prg'>progress: 0%</div>"
 "<script>"
  "$('form').submit(function(e){"
  "e.preventDefault();"
  "var form = $('#upload_form')[0];"
  "var data = new FormData(form);"
  " $.ajax({"
  "url: '/update',"
  "type: 'POST',"
  "data: data,"
  "contentType: false,"
  "processData:false,"
  "xhr: function() {"
  "var xhr = new window.XMLHttpRequest();"
  "xhr.upload.addEventListener('progress', function(evt) {"
  "if (evt.lengthComputable) {"
  "var per = evt.loaded / evt.total;"
  "$('#prg').html('progress: ' + Math.round(per*100) + '%');"
  "}"
  "}, false);"
  "return xhr;"
  "},"
  "success:function(d, s) {"
  "console.log('success!')"
 "},"
 "error: function (a, b, c) {"
 "}"
 "});"
 "});"
 "</script>";

void createAP()
{
  if (getConfig("ota") == "1")
  {
    // saveConfig("ota", "0");
    waitScreen();
    // Serial.println(getWifi("ssid1").c_str());
    // Serial.println(getWifi("passwd1").c_str());
    // Serial.println(getWifi("ssid2").c_str());
    // Serial.println(getWifi("passwd2").c_str());
    wifiMulti.addAP(getWifi("ssid1").c_str(), getWifi("passwd1").c_str());
    wifiMulti.addAP(getWifi("ssid2").c_str(), getWifi("passwd2").c_str());

    while (wifiMulti.run() != WL_CONNECTED)
    {
      delay(500);
      Serial.print(".");
    }
    MDNS.begin("chronvs");
    wellcome();
  }
}

void updateCodeOta()
{
  if (getConfig("ota") == "1")
  {
    
server.on("/", HTTP_GET, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/html", serverIndex);
  });
  /*handling uploading firmware file */
  server.on("/update", HTTP_POST, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
    ESP.restart();
  }, []() {
    HTTPUpload& upload = server.upload();
    if (upload.status == UPLOAD_FILE_START) {
      Serial.printf("Update: %s\n", upload.filename.c_str());
      if (!Update.begin(UPDATE_SIZE_UNKNOWN)) { //start with max available size
        Update.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_WRITE) {
      /* flashing firmware to ESP*/
      if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
        Update.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_END) {
      if (Update.end(true)) { //true to set the size to the current progress
        Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
        saveConfig("ota", "0");
      } else {
        Update.printError(Serial);
        saveConfig("ota", "0");
      }
    }
  });
  server.begin();

  }
}

void otaHandle()
{
  if (getConfig("ota") == "1")
  {
    server.handleClient();
  }
}
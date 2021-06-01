#include <ESP8266WiFi.h>

//--- 2021-06-01
#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>
#include <DNSServer.h>
//#if defined(ESP8266)
#include <ESP8266WebServer.h>
//#else
//#include <WebServer.h>
//#endif


//#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager


void exe_ota()
{
  Serial.println("Start Update");
  t_httpUpdate_return ret = ESPhttpUpdate.update("http://www.xxxxxx.com/updates/Update2.bin"); //<--- ส่วนนี้ต้องแก้เป็น url/address ของไฟล์ที่เราต้องการ download มา update นะครับ
  switch (ret) {
    case HTTP_UPDATE_FAILED:
      Serial.printf("HTTP_UPDATE_FAILD Error (%d): %s", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
      break;
    case HTTP_UPDATE_NO_UPDATES:
      Serial.println("HTTP_UPDATE_NO_UPDATES");
      break;
    case HTTP_UPDATE_OK:
      Serial.println("HTTP_UPDATE_OK");
      break;
  }
}

//--- 2020-12-24 For ESP32
//#include <WiFi.h>
//#include <esp_wifi.h>

// ตั้งค่าพอร์ตเป็นพอร์ต 80, 2021-06-01
WiFiServer server(80);


void wifi_init() {
  WiFi.begin(ssid, pwd);

  while( WiFi.status() != WL_CONNECTED ) {
    Serial.println(".");
    delay(100);
  }

  Serial.println("WiFi connected");
  
  // เริ่มการทำงานของ Server
  server.begin();  // 2021-06-01

  //--- 2021-06-01
  //WiFiManager wifiManager;
  //wifiManager.autoConnect("AutoConnectAP");


  
} 

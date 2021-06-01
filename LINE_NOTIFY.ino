//--------------
//LINE NOTIFY API
String LINE_TOKEN = "JJQNbsiyAisnZ3YAmFLQFvCC4i0zAPyNQ6tIoS5dPaF"; //--- 2020-11-17,"TOKEN HERE";
//---------------------------------------------------------
void SendLINE()
{
String LINE_Message("ทดสอบส่งภาษาไทย"); 
Line_Notify(LINE_Message);
}
//-------------------------------------------------
//------------------------------------------------
void Line_Notify(String message)
{
    Serial.println ("\nconnected LINE");
    Serial.println(WiFi.localIP());
    WiFiClientSecure client;
    if (!client.connect("notify-api.line.me", 443)) {
    Serial.println("connection failed");
    return;   
  }
  //---------------------------------------
  String req = "";
  req += "POST /api/notify HTTP/1.1\r\n";
  req += "Host: notify-api.line.me\r\n";
  req += "Authorization: Bearer " + String(LINE_TOKEN) + "\r\n";
  req += "Cache-Control: no-cache\r\n";
  req += "User-Agent: MCU\r\n";
  req += "Content-Type: application/x-www-form-urlencoded\r\n";
  req += "Content-Length: " + String(String("message=" + message).length()) + "\r\n";
  req += "\r\n";
  req += "message=" + message;
   Serial.println(req);
  client.print(req);
  delay(20);
   Serial.println("-------------");
  while(client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      break;
     
    }
   // Serial.println("line:");
   
  }
   Serial.println("-------------");
  return; 
   //WiFi.disconnect();
}//END Line_Notify
//------------------------------------------------------------------

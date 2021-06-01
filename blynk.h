

#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>   // --- 2020-10-08
SimpleTimer timer;

void CheckConnection(){
  Connected2Blynk = Blynk.connected();
  if(!Connected2Blynk){
    Serial.println("Not connected to Blynk server"); 
    Blynk.connect(3333);  // timeout set to 10 seconds and then continue without Blynk  
  }
  else{
    Serial.println("Connected to Blynk server");     
  }
}

void blynk_init() {
  Serial.println("Starting blynk");
  //Blynk.config(token);
  Blynk.config(token,"robotplanet.org",8080); /* 2020-10-07 */
  //Blynk.connect(5000);
  Blynk.connect(3333);  //--- 2020-10-08, timeout set to 10 seconds and then continue without Blynk  
  
  if(Blynk.connected()) {
    Connected2Blynk = true; //--- 2020-10-08
    Serial.println("Blynk connected");
  } else {
    Serial.println("Blynk can't be connected");
  }
  timer.setInterval(11000L, CheckConnection); //--- 2020-10-08, check if still connected every 11 seconds 
} 

static inline void blynk_run() {
  // --- 2020-10-08
  //if(Connected2Blynk) {
  if(Blynk.connected()) {
        Blynk.run();
  }else{
    Blynk.connect(3333);  //---2020-10-08, timeout set to 10 seconds and then continue without Blynk  
    Serial.println("Offline");
    delay(100);
  }  
} 

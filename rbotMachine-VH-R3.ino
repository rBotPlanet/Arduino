
//#include <Blynk.h>
//#include <WiFi.h>

//#define BLYNK_PRINT Serial 
//#include
//#include
//#include <config.h>
//#include <wifi.h>
//#include <blynk.h>
//#include <motor.h>

#include "config.h"
#include "wifi.h"
#include "blynk.h"
#include "motor.h"
#include "MySQL_basic.h"

//#include <BlynkSimpleEsp8266.h>
//#include <ESP8266WiFi.h>


#define BLYNK_PRINT Serial 

/* --- 2020-11-10
#define RightMotorSpeed 5 // D1 <-> IN1
#define RightMotorDir 0 // 2020-10-12, 0  // D2 <-> IN2
#define LeftMotorSpeed 4 // 2020-10-12, 4  // D3 <-> IN3
#define LeftMotorDir 2  // D4 <-> IN4
--- */

#define RightMotorSpeed D1 // D1 <-> IN1
#define RightMotorDir D3 // 2020-10-12, 0  // D2 <-> IN2
#define LeftMotorSpeed D2 // 2020-10-12, 4  // D3 <-> IN3
#define LeftMotorDir D4  // D4 <-> IN4
 
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
//char auth[] = "8DqNIKru-QsqCAQ8f6ULuB_3LTs2OBc1"; // Token ที่ Copy มาจาก Email =xxxxxxxxxxx";
//char ssid[] = "robotplanet"; //"robotplanet_2.4g"; // ชื่อ WIFI ที่ใช้เชื่อมต่อ
//char pass[] = "robotic7092"; // ""Gnopnraerahc7092";// รหัส WIFI ที่ใช้เชื่อมต่อ


void setup()
{
 //Serial.begin(9600);  // 9600, 115200
 //Blynk.begin(auth, ssid, pass);
 //pinMode(RightMotorSpeed, OUTPUT);
 //pinMode(RightMotorDir, OUTPUT);
 //pinMode(LeftMotorSpeed, OUTPUT);
 //pinMode(LeftMotorDir, OUTPUT);

  // Sample query
  //char query[] = "SELECT population FROM world.city WHERE name = 'New York'";
  //char query[] = "SELECT Version FROM rMachine_schema.rMachine Where MachineID = ";
  //char *query = "SELECT Version FROM rMachine_schema.rMachine Where MachineID = '" + __FILE__ + "'";
  char *query = "SELECT Version FROM rMachine_schema.rMachine Where MachineID = '";
  row_values *row = NULL;
  long head_count = 0;
  char* sqldata;


  Serial.begin(115200);

  wifi_init();
  blynk_init();
  
  motor_init();
  Blynk.virtualWrite(V5, firmware); // 2020-11-05
  Serial.println("Start program by arduinona.com");

  //--- MySQL connection
  //--- Convert
  //const char* macStr = "90-A2-AF-DA-14-11";
  //byte mac[6];
  //parseBytes(macStr, '-', mac, 6, 16);

  /* ---
  char str[] = "B4:21:8A:F0:3A:AD";
  char* str;
  uint8_t MAC[6];
  char* ptr;

  str = WiFi.macAddress();
  MAC[0] = strtol( strtok(str,":"), &ptr, HEX );
  for( uint8_t i = 1; i < 6; i++ )
  {
    MAC[i] = strtol( strtok( NULL,":"), &ptr, HEX );
  }
  Serial.print(MAC[0], HEX);

  const char* ipStr = "50.100.150.200";
  byte ip[4];
  parseBytes(ipStr, '.', ip, 4, 10);

  const char* macStr = "90-A2-AF-DA-14-11";
  byte mac[6];
  parseBytes(macStr, '-', mac, 6, 16);
   --- */
  
  for( uint8_t i = 1; i < 6; i++)
  
  WiFi.mode(WIFI_STA);  
  // Set your new MAC Address
  uint8_t newMACAddress[] = {0x32, 0xAE, 0xA4, 0x07, 0x0D, 0x66};
  //uint8_t newMACAddress[] = WiFi.macAddress();
  //esp_wifi_set_mac(ESP_IF_WIFI_STA, &newMACAddress[0]);
  wifi_set_macaddr(STATION_IF, &newMACAddress[0]);

  //mac_addr = WiFi.macAddress(); //--- Additional
  Ethernet.begin(mac_addr);
  Serial.println("Connecting...");
  if (conn.connect(server_addr, 3306, user, password)) {
    delay(1000);
  }
  else
    Serial.println("Connection failed.");

  // --- Query data from MySQL
  // Initiate the query class instance
  MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
  // Execute the query
  //query = query & "'" & __FILE__ & "'";
  strcat(query, __FILE__);
  strcat(query, "'");
  cur_mem->execute(query);
  Serial.println(query);
  // Fetch the columns (required) but we don't use them.
  column_names *columns = cur_mem->get_columns();

  // Read the row (we are only expecting the one)
  column_names *cols = cur_mem->get_columns();
  do {
    row = cur_mem->get_next_row();
    if (row != NULL) {
      for (int i = 0; i < cols->num_fields; i++)
      {
        //if (strcmp(cols->fields[i]->name,"Version") == 0) {
        if (cols->fields[i]->name == "Version") {
            firmware = row->values[i];
          }
      }
      head_count = atol(row->values[0]);
      //sqldata = row->values[0];
      //firmware = row->values[0];
      
      //&firmware = &row->values[0];
      //Blynk.virtualWrite(V5, &row->values[0]); // 2020-12-25
      //row->values[0].toCharArray(firmware, row->values[0].length());
      //sqldata.toCharArray(firmware, sqldata.length());
    }
  } while (row != NULL);
  Blynk.virtualWrite(V5, firmware); // 2020-12-25
  
  // Deleting the cursor also frees up memory used
  delete cur_mem;

  // Show the result
  Serial.print("  NYC pop = ");
  Serial.println(head_count);

  delay(500);

  Serial.println("2) Demonstrating using a local, global cursor.");
  // Execute the query
  cur.execute(query);
  // Fetch the columns (required) but we don't use them.
  cur.get_columns();
  // Read the row (we are only expecting the one)
  do {
    row = cur.get_next_row();
    if (row != NULL) {
      head_count = atol(row->values[0]);
    }
  } while (row != NULL);
  // Now we close the cursor to free any memory
  cur.close();

  // Show the result but this time do some math on it
  Serial.print("  NYC pop = ");
  Serial.println(head_count);
  Serial.print("  NYC pop increased by 12 = ");
  Serial.println(head_count+12);
  
}
 
void loop()
{

  //--- 2021-06-01
  if (WiFi.status() == WL_CONNECTED)
    exe_ota();
  
  /* Blynk.run(); // 2020-10-07 */
  blynk_run(); // 2020-10-07
  timer.run(); // 2020-10-08
  /*  Additional */
  //float yf = mapf(control[1], 0, 1023, -1.0, 1.0); 
  //float xf = mapf(control[0], 0, 1023, -0.3, 0.3);  //ความเร็วเลี้ยวกำหนดตรงนี้ เริ่มต้นที่ 0.3 เร็วกว่านี้จะคุมไม่ทันเอานา

  float yf = mapf(control[1], 0, 1023, -0.5, 0.5); 
  float xf = mapf(control[0], 0, 1023, -0.1, 0.1); 

  float norm = sqrtf(xf*xf + yf*yf);
  if(norm<1.0) norm = 1.0;
  float dir[2] = { xf/norm, yf/norm };
  
  /*
  float left = dir[1] + dir[0];
  float right = dir[1] - dir[0];
  */

  leftspeed = dir[1] + dir[0];
  rightspeed = dir[1] - dir[0];

  /*
  float force = sqrtf( left*left + right*right );
  if(force<1.0) force = 1.0;
  float wheel[2] = { left/force, right/force };
  */

  float force = sqrtf( leftspeed*leftspeed + rightspeed*rightspeed );
  if(force<1.0) force = 1.0;
  float wheel[2] = { leftspeed/force, rightspeed/force };

  //--- 2020-10-12
  //minSpeed = MIN_PWM_SPD;

  //motor_cmd(left,right);
}

void Speed()
{
  //minSpeed = mSpeed
}

void halt()
{
 /*
 digitalWrite(RightMotorDir, HIGH);
 digitalWrite(LeftMotorDir, HIGH);
 digitalWrite(RightMotorSpeed, HIGH);
 digitalWrite(LeftMotorSpeed, HIGH);
 */
 digitalWrite(RightMotorDir, HIGH);
 digitalWrite(LeftMotorDir, HIGH);
 /* --- 2020-11-06
 digitalWrite(RightMotorSpeed, LOW);
 digitalWrite(LeftMotorSpeed, LOW);
 --- */
 motor_cmd(0, 0); // 2020-11-06
}
 
void forward()
{
  /*
 digitalWrite(RightMotorDir, HIGH);
 digitalWrite(LeftMotorDir, HIGH);
 digitalWrite(RightMotorSpeed, HIGH);
 digitalWrite(LeftMotorSpeed, HIGH);
 */
 digitalWrite(RightMotorDir, HIGH);
 digitalWrite(LeftMotorDir, HIGH);
 motor_cmd(leftspeed,rightspeed);
}

void reverse()
{
 digitalWrite(RightMotorDir, LOW);
 digitalWrite(LeftMotorDir, LOW);
 //digitalWrite(RightMotorSpeed, HIGH);
 //digitalWrite(LeftMotorSpeed, HIGH);
 motor_cmd(leftspeed,rightspeed);
}
 
//--- 2020-10-12, void right()
void left()
{
 digitalWrite(RightMotorDir, LOW);
 digitalWrite(LeftMotorDir, HIGH);
 //digitalWrite(RightMotorSpeed, HIGH);
 //digitalWrite(LeftMotorSpeed, LOW);

 //digitalWrite(RightMotorDir, HIGH);
 //digitalWrite(LeftMotorDir, LOW);
 //digitalWrite(RightMotorSpeed, HIGH);
 //digitalWrite(LeftMotorSpeed, HIGH);
 
 //motor_cmd(leftspeed,rightspeed);
 
 //motor_cmd(leftspeed,0);
 motor_cmd(0, rightspeed);
}
 
//--- 2020-10-12, void left()
void right()
{
 digitalWrite(RightMotorDir, HIGH);
 digitalWrite(LeftMotorDir, LOW);
 
 //digitalWrite(RightMotorSpeed, LOW);
 //digitalWrite(LeftMotorSpeed, HIGH);

 //digitalWrite(RightMotorDir, LOW);
 //digitalWrite(LeftMotorDir, HIGH);
 
 //digitalWrite(RightMotorSpeed, HIGH);
 //digitalWrite(LeftMotorSpeed, HIGH);
 
 //motor_cmd(leftspeed,rightspeed);
 //motor_cmd(leftspeed,0);
 
 //--- 2020-10-12, motor_cmd(0,rightspeed);
 motor_cmd(leftspeed, 0);
}
 
BLYNK_WRITE(V0)
{
 if (param[0])
 {
   control[0] = param[0].asInt();
   control[1] = param[1].asInt();
   forward();
 }
 else
   halt();
}
 
BLYNK_WRITE(V1)
{
 if (param[0])
 {
   control[0] = param[0].asInt();
   control[1] = param[1].asInt();
   left(); //reverse();
 }
 else
   halt();
}
 
BLYNK_WRITE(V2)
{
 if (param[0])
 {
   control[0] = param[0].asInt();
   control[1] = param[1].asInt();
   right();
 }
 else
   halt();
}
 
BLYNK_WRITE(V3)
{
 if (param[0])
 {
   control[0] = param[0].asInt();
   control[1] = param[1].asInt();
   reverse(); //left();
 }
 else
   halt();
}

BLYNK_WRITE(V4)
{
 if (param[0])
 {
   //Speed(param[0].asInt);
   minSpeed = param.asInt();
 }
 sprintf(buf, "Speed => %i", minSpeed);
 Serial.println(buf);
 /* ---
 else
   minSpeed = minSpeed; --- */
}

BLYNK_WRITE(V5)
{
  //Blynk.virtualWrite(V5, firmware);
}

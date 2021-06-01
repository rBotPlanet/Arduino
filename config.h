
const char* ssid = "robotplanet";
const char* pwd = "robotic7092";
//const char* token = "wxzlQgWrtUR20E6XarFT2E8XFlF0nVH3";//"qyKL59CfllpEEwfti2IPJMu0uq6M_N7e";//"8DqNIKru-QsqCAQ8f6ULuB_3LTs2OBc1";
//const char* token = "Bq-XseWKpEj0acLLcRNjeEH3AciqJumF"; // Modified on 2020-11-06
const char* token = "6xIp8I7iCOWyEK3B4DZ3IA9pVIORdC_a"; //Modified on 2021-06-01

int control[2] = {0,0};
float leftspeed = 0;
float rightspeed = 0;
double motorspeed = 0;
bool Connected2Blynk = false; /* --- 2020-10-08*/
int minSpeed = 250; // 2020-10-12
char buf[10];  // 2020-11-05
//char firmware[] = "Firmware V 1.1.1.1";
//char firmware[] = "Firmware V 1.1.1.2"; // Modified on 2020-11-06
//char* firmware = "Firmware V 1.1.1.3";  // 2020-12-25
char* firmware = "Firmware V 2.1.1.3";  // 2021-06-01

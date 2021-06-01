#include <Ethernet.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

byte mac_addr[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
//--- uint8_t mac_addr[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

//IPAddress server_addr(10,0,1,35);  // IP of the MySQL *server* here
IPAddress server_addr(157,230,253,169);  // IP of the MySQL *server* here
char user[] = "root";              // MySQL user login username
//char password[] = "secret";        // MySQL user login password
char password[] = "Robotic@569170";        // MySQL user login password

// Sample query
//char query[] = "SELECT population FROM world.city WHERE name = 'New York'";
//char *query;

EthernetClient client;
MySQL_Connection conn((Client *)&client);
// Create an instance of the cursor passing in the connection
MySQL_Cursor cur = MySQL_Cursor(&conn);

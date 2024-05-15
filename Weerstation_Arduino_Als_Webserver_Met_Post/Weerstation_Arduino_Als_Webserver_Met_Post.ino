/* Thomas Nobel(500485), Simon Baars(550925), Oguz Uncu(550545)
 * Weerstation als webserver
 */


//Includes
#include <SPI.h> // needed for Arduino versions later than 0018
#include <Ethernet.h> //Include the Ethernet Library

//Defines
#define RED 4 //The red light has digital pin 4
#define YELLOW 3 //The yellow light has digital pin 3
#define GREEN 2 //The green light has digital pin 2
#define aantalPinnetjes 3 //Aantal aangesloten lampjes
#define TEMP 0 //The temperature sensor has analog pin 0
#define LICHT 1 // The light sensor has analog pin 1
#define temperatuur (22.8 / 698.0) * (float)analogRead(TEMP)
#define lux (482.0 / 893.0) * (float)analogRead(LICHT)

//The Servers
EthernetServer server(80); //The EthernetServer
EthernetClient client; //The EthernetClient

//Settings
IPAddress ip (192, 168, 137, 3);// ip address for ethernet shield (has to be unique for every weather station connected to the gateway!)

//Constant variables
const int MAX_PAGENAME_LEN = 8; // max characters in page name
const int PROGMEM ledPins[] = {GREEN, YELLOW, RED}; //An array containing all leds' pins that will be used

//Variables

String *webData;//Values containing webdata
byte mac[] = {0x28, 0xD2, 0x44, 0x94, 0x2c, 0x78}; // max address for ethernet shield
char buffer[MAX_PAGENAME_LEN + 1]; // additional character for terminating null
String httpData = ""; //The http request
int minTemp = 0; //Minimal temperature, used for ledmanagement
int maxTemp = 100;//Maximal temperature, used for ledmanagement

//Set the web server up
void setup() {
  Serial.begin(9600); //Start the serial
  Ethernet.begin(mac, ip);  //Begin the Arduino's Ethernet
  server.begin(); //Open the server
  for (int i = 0 ; i < aantalPinnetjes; i++) {
    pinMode(ledPins[i], OUTPUT);//Set all leds' pins to output
  }
  delay(1000);//Just a second before we'll continue
  Serial.println(F("Ready"));
}

void loop() {
  client = server.available();//Check if the server is available
  if (client) {
    Serial.println(F("Connected!"));
    boolean type = 0;//Create a boolean for the type (GET or POST)
    while (client.connected()) {
      if (client.available()) {
        // GET, POST, or HEAD
        memset(buffer, 0, sizeof(buffer)); // clear the buffer
        if (client.readBytesUntil('/', buffer, MAX_PAGENAME_LEN))
        {
          if (strcmp(buffer, "GET ") == 0 )//Decide if it was a GET or POST request
            type = 0;
          else if (strcmp(buffer, "POST ") == 0)
            type = 1;
          memset(buffer, 0, sizeof(buffer)); // clear the buffer
          if (client.readBytesUntil( ' ', buffer, MAX_PAGENAME_LEN ))//Read the pagename
          {
            readHttpData();//Store the request that the client got in the httpData string
            if (strcasecmp(buffer, "data") == 0) {//If the buffer contains the data page
              int waardes[] = {0, 1, 2, 3};//Values we'd like to show (0 = Amount of Lux, 1 = Minimal Temperature, 2 = Maximal Temperature, 3 = Temperature)
              getWaardes(waardes, 4, true);//Get the values and put them in the webData variable
              returnJson(webData, 4);//Process the webData by showing the webpage
              Serial.println("data");
            } else if (strcasecmp(buffer, "lux") == 0) {//If the buffer contains the lux page
              int waardes[] = {0};//Values we'd like to show (0 = Amount of Lux, 1 = Minimal Temperature, 2 = Maximal Temperature, 3 = Temperature)
              getWaardes(waardes, 1, true);//Get the values and put them in the webData variable
              returnJson(webData, 1);//Process the webData by showing the webpage
              Serial.println("lux");
            } else if (strcasecmp(buffer, "temp") == 0) {//If the buffer contains the temp page
              int waardes[] = {1, 2, 3};//Values we'd like to show (0 = Amount of Lux, 1 = Minimal Temperature, 2 = Maximal Temperature, 3 = Temperature)
              getWaardes(waardes, 3, true);//Get the values and put them in the webData variable
              returnJson(webData, 3);//Process the webData by showing the webpage
              Serial.println("temp");
            } else if (strcasecmp(buffer, "") == 0) { //If the buffer contains nothing
              if (type == 0) {//Only for get requests
                int waardes[] = {0, 1, 2, 3};//Values we'd like to show (0 = Amount of Lux, 1 = Minimal Temperature, 2 = Maximal Temperature, 3 = Temperature)
                getWaardes(waardes, 4, false);//Get the values and put them in the webData variable
                createWebpage(webData, 4);//Process the webData by showing the webpage
              }
            } else if (strcasecmp(buffer, "temp/mintemp") == 0) { //If the buffer contains the mintemp page
              processPostDataIfAvailable(false);//Check for postdata and process it
            } else if (strcasecmp(buffer, "temp/maxtemp") == 0) { //If the buffer contains the maxtemp page
              processPostDataIfAvailable(true);//Check for postdata and process it
            } else {
              send404();//404 page
            }
          }
        }
        break;
      }
    }
    delay(1);//Wait a millisecond
    for (int i = 0; i < aantalPinnetjes; i++) {
      digitalWrite(ledPins[i], LOW);//Turn all leds off
    }
    digitalWrite(bepaalWelkeLed(), HIGH); //Except for one
    client.stop();//Stop the connection
    httpData = "";//Empty the httpData string
  }
}










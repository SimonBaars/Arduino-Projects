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
#define CELSIUS (22.8 / 698.0) * (float)analogRead(TEMP) //Get temperature in celsius
#define LUX (482.0 / 893.0) * (float)analogRead(LICHT) //Get light value in lux

//The Servers
EthernetServer server(80); //The EthernetServer
EthernetClient client; //The EthernetClient

//Settings
IPAddress ip (192, 168, 137, 3);// ip address for ethernet shield (has to be unique for every weather station connected to the gateway!)
IPAddress iphost (192, 168, 137, 1); // ip address for gateway
const String weatherStationId = "\"Oguz\""; //The ID of the weather station, to be registered in the gateway

//Constant variables
const int MAX_PAGENAME_LEN = 20; // max characters in page name
const int PROGMEM ledPins[] = {GREEN, YELLOW, RED}; //An array containing all leds' pins that will be used
const String httpVersion = "HTTP/1.1";
const String apiPath = "/WeerstationBP/Api/";
const String http = "http://";

//Variables
float minTemp = 0;
float maxTemp = 100;
bool boundariesObtained = false;
long prevMillis = 0;
char buffer[MAX_PAGENAME_LEN + 1]; // additional character for terminating null
byte mac[] = {0x90, 0xA2, 0xDA, 0x0E, 0xF4, 0x66}; // max address for ethernet shield
String httpData = ""; //Stores the complete response, to be filled by readHttp()

//Setup code
void setup() {
  Serial.begin(9600); //Start the Serial at baudrate 9600
  Ethernet.begin(mac, ip); //Begin the Arduino's Ethernet
  server.begin(); //Open the server
  for (int i = 0 ; i < aantalPinnetjes; i++) {
    pinMode(ledPins[i], OUTPUT); //Set all leds' pins to output
  }
  delay(1000); //Just a second before we'll continue by registering our weather station
  if (client.connect(iphost, 80)) { //We'll try to connect
    registreerWeerstation(); //Register the weatherstation by sending a POST request containing our IP and our ID
    doFlush(); //Flush the client by reading every byte but not storing those bytes in the Arduino
    client.stop(); // Transfer has been completed, the connection can be closed
    Serial.println(F("Ready")); //The Arduino is ready!
  } else {
    Serial.println(F("Not Ready")); //The Arduino could NOT register
  }
}

//Looping code
void loop() {
  if (prevMillis + 5000 < millis()) {//If 5 seconds have ellapsed we'll try to send the sensordata to the gateway
    if (boundariesObtained) { //We first want to have received the temperature boundaries
      if (client.connect(iphost, 80)) { //Let's try to connect
        manageLeds(); //Turn leds on or off
        sendMeasuresToGateway(); //Send the current measures to the gateway
        doFlush(); //Flush the client
        prevMillis = millis(); //Reset the timer
        client.stop(); //Close the connection
      }
    }
  }
  delay(10); //Let's wait a few milliseconds after all we've been through

  client = server.available(); //Check if the server is available (is there a post request for us to process?)
  if (client) { //If there is a post request for us to process we will
    while (client.connected()) { //We'll stay processing as long as there are post requests for us to process
      if (client.available()) { //If there's data available for the client we can go read it
        memset(buffer, 0, sizeof(buffer)); // clear the buffer
        if (client.readBytesUntil('/', buffer, MAX_PAGENAME_LEN)) //Fill the buffer with the type of request (POST, GET, PUT, ect.)
        {
          memset(buffer, 0, sizeof(buffer)); // clear the buffer
          if (client.readBytesUntil(' ', buffer, MAX_PAGENAME_LEN )) //Fill the buffer with the name of the page the gateway will send it's POST request to
          {
            if (strcasecmp(buffer, "temperatuurgrenzen") == 0) { //Check if the post request is actually adressed to "temperatuurgrenzen"
              readHttpData(); //set the variable httpData to the complete http request
              processPostDataIfAvailable(); //Here we'll check for any valid POST data
            }
          }
        }
        break;
      }
    }
    delay(1); //Wait 1 millisecond before closing the connection
    client.stop(); //Close the connection
    httpData = ""; //Empty the httpData string

  }
}


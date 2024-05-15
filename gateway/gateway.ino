#include <SPI.h> // needed for Arduino versions later than 0018
#include <Ethernet.h>
#define RED 4
#define YELLOW 3
#define GREEN 2
#define aantalPinnetjes 3
#define DRUKKNOP 5
#define TEMP 0
#define LICHT 1
#define TEMP (22.8 / 698.0) * (float)analogRead(0)
#define LUX (482.0 / 893.0) * (float)analogRead(1)

const int pinnenLeds[] = {GREEN, YELLOW, RED};
const int interval = 2000;
bool ledstate = 1;
float temperatuur;
float lux;
String *webData;
boolean minTempIsset = false;
const String weerstationid = "\"Oguz\"";

byte mac[] = {0x90, 0xA2, 0xDA, 0x0E, 0xF4, 0x66}; // max address for ethernet shield
IPAddress ip (192, 168, 137, 3);// ip address for ethernet shield
IPAddress iphost(192, 168, 137, 1); // ip address for host

const int MAX_PAGENAME_LEN = 20; // max characters in page name
char buffer[MAX_PAGENAME_LEN + 1]; // additional character for terminating null

EthernetServer server(80);
EthernetClient client;

String httpData = "";
float minTemp = 33;
float maxTemp = 66;
long prevMillis = 0;
const String httpVersie = "HTTP/1.1";
const String apiPath = "/WeerstationBP/Api/";
const String http = "http://";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Ethernet.begin(mac, ip);
  server.begin();
  for (int i = 0 ; i < aantalPinnetjes; i++) {
    pinMode(pinnenLeds[i], OUTPUT);
  }
  pinMode(DRUKKNOP, INPUT);
  delay(1000);
  Serial.println(F("Ready"));
}

void loop() {
  // put your main code here, to run repeatedly:
  if (client.connect(iphost, 80)) {
    if (prevMillis + 5000 < millis()) {
      //registreerWeerstation();
     //doFlush();
     regelLedjes();
      sendMeasuresToGateway();
      doFlush();
      prevMillis = millis();
    }
    client.stop();
  }
  delay(10);
  client = server.available();
  if (client) {
    Serial.println(F("Server is available"));
    //boolean type = 0;
    while (client.connected()) {
      if (client.available()) {
        // GET, POST, or HEAD
        memset(buffer, 0, sizeof(buffer)); // clear the buffer
        if (client.readBytesUntil('/', buffer, MAX_PAGENAME_LEN))
        {
          /*if (strcmp(buffer, "GET ") == 0 )
            type = 0;
          else if (strcmp(buffer, "POST ") == 0)
            type = 1;*/
          // look for the page name
          memset(buffer, 0, sizeof(buffer)); // clear the buffer
          if (client.readBytesUntil(' ', buffer, MAX_PAGENAME_LEN ))
          {
            //Serial.println(buffer);
            readHttpData();
            /*if (strcasecmp(buffer, "data") == 0) {
              int waardes[] = {0, 1, 2, 3};
              getWaardes(waardes, 4, true);
              returnJson(webData, 4);
              Serial.println("data");
            } else if (strcasecmp(buffer, "lux") == 0) {
              int waardes[] = {0};
              getWaardes(waardes, 1, true);
              returnJson(webData, 1);
              Serial.println("lux");
            } else if (strcasecmp(buffer, "temp") == 0) {
              int waardes[] = {1, 2, 3};
              getWaardes(waardes, 3, true);
              returnJson(webData, 3);
              Serial.println("temp");
            } else if (strcasecmp(buffer, "") == 0) {

              //if (type == 0) {
              int waardes[] = {0, 1, 2, 3};
              getWaardes(waardes, 4, false);
              createWebpage(webData, 4);
              //}
            } */
            if (strcasecmp(buffer, "temperatuurgrenzen") == 0) {
              processPostDataIfAvailable(false);
            }
            /* else {
               send404();
             }*/
          }
        }
        break;
      }
    }
    delay(1);
    client.stop();
    //free(&httpData);
    httpData = "";

  }
}

void regelLedjes() {
  digitalWrite(bepaalWelkeLed(temperatuur), HIGH);
  for (int i = 0; i < aantalPinnetjes; i++) {
    if (pinnenLeds[i] != bepaalWelkeLed(temperatuur)) {
      digitalWrite(pinnenLeds[i], LOW);
    }
  }
}


/*void sendHeader(char *title)
{
  // send a standard http response header
  client.println(F("HTTP/1.1 200 OK"));
  client.println(F("Content-Type: text/html"));
  client.println();
  client.print(F("<html><head><title>"));
  client.println(title);
  client.println(F("</title><body>"));
}
*/
/*
void createWebpage(String waardes[], int nWaardes)
{
  sendHeader("Groetservice");
  client.print("<h3>");
  for (int i = 0; i < nWaardes; i++) {
    client.print(waardes[i]);
    client.print("<BR>");
  }
  client.println("</h3>");
  client.println(F("</body></html>"));
}
*/

/*void returnJson(String waardes[], int nWaardes) {
  client.println(F("HTTP/1.1 200 OK"));
  client.println(F("Content-Type: application/json"));
  createLineContentLength(92);
  client.println();
  createContentLine(waardes, nWaardes);
}*/

String createContentLine(String waardes[], String waardes2[], int nWaardes) {
  String contentLine = "{";
  for (int i = 0; i < nWaardes; i++) {
    contentLine += "\"";
    contentLine += waardes[i];
    contentLine += "\":";
    contentLine += waardes2[i];
    if (i != nWaardes - 1) {
      contentLine += ",";
    }
  }
  contentLine += "}";
  return contentLine;
}

void createLineContentLength(int contentLength) {
  client.print(F("Content-Length: "));
  client.println(String(contentLength));
}

/*String maakWaarde(String waardeString, float waardeFloat, boolean isJson) {
  String waarde = "";
  if (isJson) {
    waarde += "\"";
  }
  waarde += waardeString;
  if (isJson) {
    waarde += "\"";
  }
  waarde += ": ";
  waarde += waardeFloat;
  return waarde;
}*/

void registreerWeerstation(){
   client.print(F("POST "));
   client.print(http);
  client.print(getIp(iphost, false));
  client.print(apiPath);
  client.print(F("WeerstationID "));
  client.println(httpVersie);
  client.println(F("Content-type: application/json"));
  createLineHost();
  String waardes[] = {"Ip", "Id"};
  String waardes2[] = {getIp(ip,true), weerstationid};
  String content = createContentLine(waardes, waardes2, 2);
  int contentlengte = content.length() + 1;
  createLineContentLength(contentlengte);
  client.println();
  client.println(content);
}

void processPostDataIfAvailable(bool minTempIsset) {
  client.println(httpVersie);
  client.println(F(" 204 No Content"));
  client.println();
  int contentLength = getContentLength(httpData);
  Serial.println(contentLength);
  readContent(httpData.substring(httpData.length() - contentLength , httpData.length()));
}

void readContent(String content) {
  for (int i = 0; i < content.length(); i++) {
    String currentData = content.substring(i, i + 7);
    currentData.toLowerCase();
    if (currentData.equals(F("minimum"))) {
      minTemp = getNumberAt(content, i + 9);
    } else if (currentData.equals(F("maximum"))) {
      maxTemp = getNumberAt(content, i + 9);
    }
  }
}

float getNumberAt(String string, int i) {
  int j;
  for (j = i;  j < string.length(); j++) {
    if (!((string.charAt(j) >= '0' && string.charAt(j) <= '9') || string.charAt(j) == '.')) {
      return (string.substring(i, j)).toFloat();
    }
  }
  return 0.0;
}

int getContentLength(String data) {
  Serial.println(data);
  for (int i = 0; i < data.length() - 15; i++) {
    if (data.substring(i, i + 15) == F("Content-Length:")) {
      return int(getNumberAt(data, i + 16));
    }
  }
  return 0;
}

void readHttpData() {
  while (client.available()) {
    httpData += char(client.read());
    delay(3);
  }
  Serial.println(httpData);
}

int bepaalWelkeLed(float temperatuur) {
  if (temperatuur < minTemp) {
    return YELLOW;
  }
  else if (temperatuur > maxTemp) {
    return RED;
  }
  return GREEN;
}

void sendMeasuresToGateway() {
  String timestamp = getTimeStamp();
  client.print(F("POST "));
  client.print(http);
  client.print(getIp(iphost, false));
  client.print(apiPath);
  client.print(F("Weerstation "));
  client.println(httpVersie);
  client.println(F("Content-type: application/json"));
  createLineHost();
  String waardes[] = {"weatherstation", "timestamp", "temperature", "illuminance"};
  String waardes2[] = {weerstationid, timestamp, String(TEMP), String(LUX)};
  String content = createContentLine(waardes, waardes2, 4);
  Serial.println(content);
  int contentlengte = content.length();
  createLineContentLength(contentlengte);
  client.println();
  client.println(content);
  /*while (!client.available()) {

  }
  String timestamp2 = "";
  while (client.available()) {
    timestamp2 += char(client.read());
    delay(5);
  }
  Serial.println(timestamp2);*/
}

void createLineHost() {
  client.print(F("Host: "));
  client.println(iphost);
}

String getIp(IPAddress ip, bool quotes) {
  String ipString = "";
  if (quotes) {
    ipString += "\"";
  }
  for (int i = 0; i < 4; i++) {
    ipString += String(ip[i]);
    if (i != 3) {
      ipString += ".";
    }
  }
  if (quotes) {
    ipString += "\"";
  }
  return ipString;
}

String getTimeStamp() {
  client.print(F("GET "));
  client.print(http);
  client.print(iphost);
  client.print(apiPath);
  client.print(F("tijd "));
  client.println(httpVersie);
  createLineHost();
  client.println();
  while (!client.available()) {

  }
  String timestamp = "";
  while (client.available()) {
    timestamp += char(client.read());
    //Serial.println(timestamp);
    delay(5);
  }
  timestamp = timestamp.substring(timestamp.length() - getContentLength(timestamp) , timestamp.length());
  Serial.println(timestamp);
  return timestamp;
}

void doFlush(){
  while (!client.available()) {

  }
  while (client.available()) {
    client.read();
    delay(5);
  }
}
/*
void getWaardes(int waardes[], int nWaardes, boolean isJson) {
  webData = new String[nWaardes];
  for (int i = 0; i < nWaardes; i++) {
    switch (waardes[i]) {
      case 0: webData[i] = maakWaarde("temperatuur", lux, isJson); break;
      case 1: webData[i] = maakWaarde("illuminance", minTemp, isJson); break;
      case 2: webData[i] = maakWaarde("weatherstation", maxTemp, isJson); break;
      case 3: webData[i] = maakWaarde("timestamp", temperatuur, isJson); break;
    }

  }
}
*/

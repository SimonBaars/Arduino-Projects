#include <SPI.h> // needed for Arduino versions later than 0018
#include <Ethernet.h>
#include <avr/pgmspace.h> // for progmem
#define P(name) static const unsigned char name[] PROGMEM // declare a static string

byte mac[] = {0x28, 0xD2, 0x44, 0x94, 0x2c, 0x78}; // max address for ethernet shield
byte ip[] = {192, 168, 0, 10}; // ip address for ethernet shield

const int MAX_PAGENAME_LEN = 8; // max characters in page name
char buffer[MAX_PAGENAME_LEN + 1]; // additional character for terminating null

EthernetServer server(80);
EthernetClient client;

String httpData = "";
String groet = "hallo";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Ethernet.begin(mac, ip);
  server.begin();
  delay(1000);
  Serial.println(F("Ready"));
}

void loop() {
  // put your main code here, to run repeatedly:
  client = server.available();
  if (client) {
      Serial.println(F("Ready"));
    boolean type = 0;
    while (client.connected()) {
      if (client.available()) {
        // GET, POST, or HEAD
        memset(buffer, 0, sizeof(buffer)); // clear the buffer
        if (client.readBytesUntil('/', buffer, MAX_PAGENAME_LEN))
        {
          if (strcmp(buffer, "GET ") == 0 )
            type = 0;
          else if (strcmp(buffer, "POST ") == 0)
            type = 1;
          // look for the page name
          memset(buffer, 0, sizeof(buffer)); // clear the buffer
          if (client.readBytesUntil( '/', buffer, MAX_PAGENAME_LEN ))
          {
            readHttpData();
            if (strcasecmp(buffer, "groet") == 0) {
              if (type == 0) {
                showAnalog(getGetData());
              } else {
                processPostDataIfAvailable();
              }
            } else {
              send404();
            }
          }
        }
        break;
      }
    }
    delay(1);
    client.stop();
    httpData="";
  }
}

String getGetData() {
  int i = 0;
  String data = "";
  while (httpData.substring(i, i + 9) != " HTTP/1.1" && httpData.length() > i + 10) {
    data += char(httpData.charAt(i));
    i++;
  }
  return data;
}

void send404()
{
  // send a 404
  client.println(F("HTTP/1.1 404 NOT FOUND"));
  client.println();
}

void sendHeader(char *title)
{
  // send a standard http response header
  client.println(F("HTTP/1.1 200 OK"));
  client.println(F("Content-Type: text/html"));
  client.println();
  client.print(F("<html><head><title>"));
  client.println(title);
  client.println(F("</title><body>"));
}

void showAnalog(String persoon)
{
  sendHeader("Groetservice");
  client.print("<h1>");
  client.print(groet);
  client.print(" ");
  client.print(persoon);
  client.println("</h1>");
  // output the value of each analog input pin

  client.println(F("</body></html>"));
}

void processPostDataIfAvailable() {
  client.println(F("HTTP/1.1 204 No Content"));
  client.println();
  int contentLength = getContentLength();
  if (contentLength != 0) {
    groet = httpData.substring(httpData.length() - contentLength , httpData.length() );
  }
}

int getContentLength() {
  for (int i = 0; i < httpData.length() - 15; i++) {
    if (httpData.substring(i, i + 15) == "Content-Length:") {
      i += 16;
      for (int j = i;  j < httpData.length(); j++) {
        if (!(httpData.charAt(j) >= '0' && httpData.charAt(j) <= '9')) {
          return (httpData.substring(i, j)).toInt();
        }
      }
    }
  }
  return 0;
}

void readHttpData() {
  while (client.available()) {
    httpData += char(client.read());
  }
  Serial.println(httpData);
}


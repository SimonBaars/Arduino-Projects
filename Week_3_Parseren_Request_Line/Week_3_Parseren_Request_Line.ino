//Parseren Request-Line door Oguz Uncu en Simon Baars (550545 & 550925)
#define LF '\n'
#define CR '\r'
#define GROOTTE 3
#include <SPI.h>
#include <Ethernet.h>
#include "Internet.h"

byte mac[] = { 0x90, 0xA2, 0xDA, 0x0E, 0xF4, 0x66 };
IPAddress ip(192, 168, 137, 3); // IP of Arduino (web client
RequestLine r = {new String[GROOTTE],GROOTTE };

EthernetServer server(80);
EthernetClient client;

//       GET http://192.168.137.1/WebApplication2/api/groet/Arduinootje HTTP/1.1

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Ethernet.begin(mac, ip);
  server.begin();
  delay(1000);
  emptyRequestLine();
  Serial.println(F("Ready"));
}

void loop() {
  getRequest();
  emptyRequestLine();
}

void getRequest() {
  client = server.available();
  if (client) {
    while (client.connected()) {
      int space = 0;
      while (client.available()) {
        char c = client.read();
        boolean breakIt = false;
        switch (c) {
          case LF:
          case CR:
            breakIt = true;
            break;
        }
        if (breakIt) {
          break;
        }
        if (c == ' ') {
          space++;
        }
        else {
          r.request[space] += c;
        }
        delay(10); // give input some time do to it's thing
      }
      printRequestLine();
      break;
    }
    while (client.available()) {
      client.read();
    }
    client.stop();
  }
}

void emptyRequestLine() {
  for (int i = 0; i < r.arraySize; i++) {
    r.request[i] = "";
  }
}

void printRequestLine() {
  for (int i = 0; i < r.arraySize; i++) {
    if (i == 1) {
      Serial.print(ip);
    }
    Serial.print(r.request[i]);
    if (i != (r.arraySize - 1)) {
      Serial.print(" ");
    }
  }
}



#include <SPI.h>
#include <Ethernet.h>
#include "structs.h"
#define AANTALANALOGPORTS 2
// check your ethernet shield
// Make sure it's unique
byte mac[] = { 0x90, 0xA2, 0xDA, 0x0E, 0xF4, 0x66 };
IPAddress server(192, 168, 0, 1); // IP of webserver
IPAddress ip(192, 168, 0, 10); // IP of Arduino (web client)
EthernetClient client;
RequestLine r = {"http://192.168.0.1/WeerstationBp/API/WeerStation", POST};
const int analogPorts[]={0,1};

void setup() {
  Serial.begin(9600);
  Ethernet.begin(mac, ip);
}
void loop() {
  Serial.println("Connecting...");
  if (client.connect(server, 80)) {
    // connected to webserver
    Serial.println("Connected to webserver");
    // Send HTTP request to server
    postRequest();
    while (!client.available()) {
      delay(5); // let's take five. Here we should check for time out
    }
    Serial.println("Response received:");
    while (client.available()) {
      char c = client.read();
      Serial.print(c);
      delay(1); // give input some time do to it's thing
    }
    Serial.println();
    Serial.println("Response read, now we can disconnect.");
    if (!client.connected()) {
      Serial.println("disconnecting...");
      client.stop();
    }
    Serial.println("We are disconnected");
  }
  else {
    Serial.println("Connection failed");

    client.print("GET http://");
    client.print(server);
    client.println("/WeerstationBp/API/WeerStation HTTP/1.1");
    client.print("Host: ");
    getIp();
    client.println("Connection: close"); // we work disconnected
    client.println(); // always one empty line between headers and content
    delay(100);
    while (client.available()) {
      char c = client.read();
      Serial.print(c);
      delay(1); // give input some time do to it's thing
    }
  }
  Serial.println("The end. Now wait for 5 seconds");
  delay(10000);
}

void postRequest() {
  createLineRequest(r);
  createLineHost();
  createLineContentType();
  createLineContentLength();
  client.println("Connection: close"); // we work disconnected
  client.println(); // always one empty line between headers and content
  createLineBody();

  //time_t t = now();
  //Serial.println(t);
  // also when no content!
  Serial.println("Request send... wait for response");
}

void createLineRequest(RequestLine r) {
  client.print(bepaalMethod(r));
  client.print(" ");
  client.print(r.url);
  client.println(" HTTP/1.1");
}

String bepaalMethod(RequestLine r) {
  if (r.method == POST) {
    return "POST";
  }
  else if (r.method == GET) {
    return "GET";
  }
  else if (r.method == DELETE) {
    return "DELETE";
  }
}

void createLineHost() {
  client.print("Host: ");
  getIp();
}

void createLineContentType() {
  client.println("Content-Type: application/json");
}

void createLineContentLength() {
  client.print("Content-Length: ");
  client.println(getContentLength());
}

void createLineBody() {
  client.print("{\"Temperatuur\":");
  client.print(analogRead(0));
  client.print(",\"min_temp\":");
  client.print(analogRead(0));
  client.print(",\"max_temp\":");
  client.print(analogRead(0));
  client.print(",\"Ip_adress\":");
  getIp();
  client.print(",\"Lichtintensiteit\":");
  client.print(analogRead(1));
  client.print(",\"Tijdstip\":");
  //tijdstip
  client.println("}");
}

void getIp() {
  client.print("'");
  client.print(server);
  client.println("'");
}

byte getContentLength(){
byte contentLength=87;
  for(byte i=0; i<AANTALANALOGPORTS;i++){
    contentLength+=String(analogRead(analogPorts[i])).length();
  }
  contentLength+=6;
  return contentLength;
}


#include <SPI.h>
#include <Ethernet.h>
#include "Internet.h"

byte mac[] = { 0x90, 0xA2, 0xDA, 0x0E, 0xF4, 0x66 };
IPAddress server(192, 168, 137, 1); // IP of webserver
IPAddress ip(192, 168, 137, 3); // IP of Arduino (web client)
EthernetClient client;
RequestLine r = {POST, "WebApplication2/api/"};

String bepaalMethod(http_methods method) {
  if (method == POST) {
    return "POST";
  } else if (method == GET) {
    return "GET";
  }
  return "DELETE";
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
 Ethernet.begin(mac, ip);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(analogToDatabase("afstand",2)){
    Serial.println("Database insert succesful!");
  } else {
    Serial.println("Database insert unsuccesful!");
  }
  delay(5000);
}

boolean analogToDatabase(String database, int analogPort){
  if(client.connect(server, 80)){
    createLineRequest(r,database);
    createLineHost();
    client.println("Content-type: application/json");
    createLineContentLength(100);
    client.println();
    createContentLine(database,analogPort);
    while(!client.available()){
 delay(5); // let's take five. Here we should check for time out
 }
 client.stop();
    return true;
  }
  return false;
}

int createContentLine(String database, int analogPort){
  client.print("{\"");
  client.print(database);
  client.print("\":");
  client.print(String(analogRead(analogPort)));
  client.println("}");
}

void createLineRequest(RequestLine r, String database) {
  client.print(bepaalMethod(r.method));
  client.print(" http://");
  getIp();
  client.print("/");
  client.print(r.path);
  client.print(database);
  client.println(" HTTP/1.1");
}

void createLineHost(){
  client.print("Host: ");
  getIp();
  client.println("");
}

void createLineContentLength(int contentLength){
  client.print("Content-Length: ");
  client.println(String(contentLength));
}

void getIp(){
  for (int i = 0; i < 4; i++) {
    client.print(String(server[i]));
    if (i != 3) {
      client.print(".");
    }
  }
}

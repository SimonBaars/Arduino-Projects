#include <SPI.h>
#include <Ethernet.h>
// check your ethernet shield
// Make sure it's unique
byte mac[] = { 0x90,0xA2,0xDA,0x0E,0xF4,0x66 };
IPAddress server(192,168,137,1); // IP of webserver
IPAddress ip(192,168,137,3); // IP of Arduino (web client)
EthernetClient client;
void setup(){
 Serial.begin(9600);
 Ethernet.begin(mac, ip);
}
void loop(){
 Serial.println("Connecting...");
 
 Serial.println("The end. Now wait for 10 seconds");
 delay(10000);
}

void putDataInDatabase(String data, int analogPort, int dataLength){
  if(client.connect(server, 80)){
 // connected to webserver
 Serial.println("Connected to webserver");
 // Send HTTP request to server
 client.println("POST http://192.168.137.1/WebApplication2/api/temperatuur HTTP/1.1");
 client.println("Host: 192.168.137.1");
 client.println("Content-type: application/json");
 String test2 = "Content-Length: ";
 char buf[256];
sprintf(buf, "%d",analogRead(analogPort));
 test2+=(12+strlen(buf));
 client.println(test2);
 Serial.println(test2);
 client.println("Connection: close"); // we work disconnected
 client.println(); // always one empty line between headers and content
 String testding = "{\"celsius\":";
 testding += analogRead(1);
 testding += "}";
 client.println(testding);
 Serial.println(testding);
 // also when no content!
 Serial.println("Request send... wait for response");
 while(!client.available()){
 delay(5); // let's take five. Here we should check for time out
 }
 Serial.println("Response received:");
 while(client.available()){
 char c = client.read();
 Serial.print(c);
 delay(1); // give input some time do to it's thing
 }

 Serial.println();
 Serial.println("Response read, now we can disconnect.");
 if(!client.connected()){
 Serial.println("disconnecting...");
 client.stop();
 }
 Serial.println("We are disconnected");
 }
 else {
 Serial.println("Connection failed");

 client.println("GET http://192.168.137.1/WebApplication2/api/temperatuur HTTP/1.1");
 client.println("Host: 192.168.137.1");
 client.println("Connection: close"); // we work disconnected
 client.println(); // always one empty line between headers and content
delay(100);
while(client.available()){
 char c = client.read();
 Serial.print(c);
 delay(1); // give input some time do to it's thing
 }
 }
}


#include <SPI.h>
#include <Ethernet.h>
//#include <time.h>
// check your ethernet shield
// Make sure it's unique
byte mac[] = { 0x90,0xA2,0xDA,0x0E,0xF4,0x66 };
IPAddress server(192,168,0,1); // IP of webserver
IPAddress ip(192,168,0,10); // IP of Arduino (web client)
EthernetClient client;
void setup(){
 Serial.begin(9600);
 Ethernet.begin(mac, ip);
}
void loop(){
 Serial.println("Connecting...");
 if(client.connect(server, 80)){
 // connected to webserver
 Serial.println("Connected to webserver");
 // Send HTTP request to server
 postRequest();

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

 client.println("GET http://192.168.0.1/iotweek2/api/temperatuur HTTP/1.1");
 client.println("Host: 192.168.0.1");
 client.println("Connection: close"); // we work disconnected
 client.println(); // always one empty line between headers and content
delay(100);
while(client.available()){
 char c = client.read();
 Serial.print(c);
 delay(1); // give input some time do to it's thing
 }
 }
 Serial.println("The end. Now wait for 5 seconds");
 delay(10000);
}

void postRequest(){
client.println("POST http://192.168.0.1/iotweek2/api/temperatuur HTTP/1.1");
 client.println("Host: 192.168.0.1");
 client.println("Content-type: application/json");
 String test2 = "Content-Length: ";
 char buf[256];
sprintf(buf, "%fd",analogRead(0));
 test2+=(74+strlen(buf));
 client.println(test2);
 Serial.println(test2);
 client.println("Connection: close"); // we work disconnected
 client.println(); // always one empty line between headers and content
 String testding = "{\"celsius\":";
 testding += analogRead(0);
 testding += ",\"fahrenheit\":";
 int fahrenheit= analogRead(0)/10;
 testding += fahrenheit;
 testding += ",\"Ip_address\":192168010";
 testding += ",\"Lichtintensiteit\":";
 int lichtintensiteit = analogRead(1)/10;
 testding += lichtintensiteit;
 testding += "}";
 client.println(testding);
  Serial.println(testding);
  //time_t t = now();
  //Serial.println(t);
}


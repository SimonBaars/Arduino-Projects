#include <ICMPPing.h>
#include <SPI.h>
#include <Ethernet.h>
// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192,168,137, 3);
EthernetServer server(80);

void setup(){
// start the Ethernet connection and the server:
Ethernet.begin(mac, ip);
server.begin();
}
void loop() {
}


#include <SPI.h>
#include <Ethernet.h>
#include <ICMPPing.h>
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; // max address for ethernet shield
byte ip[] = {192, 168, 137, 1}; // ip address for ethernet shield
IPAddress pingAddr(192, 168, 137, 3); // ip address to ping
//set manually Control Panel - Network and Sharing Centre - Local Area Status - Properties
SOCKET pingSocket = 0;
char buffer [256];
ICMPPing ping(pingSocket, (uint16_t)random(0, 255));
void setup()
{
// start Ethernet
Ethernet.begin(mac, ip);
Serial.begin(9600);
}
void loop()
{
ICMPEchoReply echoReply = ping(pingAddr, 4);
if (echoReply.status == SUCCESS)
{
sprintf(buffer,
"Reply[%d] from: %d.%d.%d.%d: bytes=%d time=%ldms TTL=%d",
echoReply.data.seq,
echoReply.addr[0],
echoReply.addr[1],
echoReply.addr[2],
echoReply.addr[3],
REQ_DATASIZE,
millis() - echoReply.data.time,
echoReply.ttl);
}
else
{
sprintf(buffer, "Echo request failed; %d", echoReply.status);
}
Serial.println(buffer);
delay(500);
}


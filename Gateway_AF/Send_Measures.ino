//Send the measured values to the gateway
void sendMeasuresToGateway() {
  String timestamp = getTimeStamp(); //Get the timestamp and put it in the timestamp string
  client.print(F("POST ")); //It's a post request. We'll print that to the client.
  client.print(http);//Prints "http://" to the client
  client.print(getIp(iphost, false));//Print our IP. Using the getIp method due to errors in the usage of String(iphost)
  client.print(apiPath);//Print the path to the API of the gateway
  client.print(F("Weerstation "));//We'll print it to the Weerstation page of the gateway
  client.println(httpVersion);//End this line with "HTTP/1.1"
  client.println(F("Content-type: application/json"));//Print the content type
  createLineHost();//Print the Host line
  String waardes[] = {"weatherstation", "timestamp", "temperature", "illuminance"};//The content is going to contain the Id, the timestamp, the temperature (in celsius) and the illuminance (in lux)
  String waardes2[] = {weatherStationId, timestamp, String(TEMP), String(LUX)}; //Create a string array containing the actual values
  String content = createContentLine(waardes, waardes2, 4); //Create the actual content line with the in the line above created 4 values
  Serial.println(content);
  createLineContentLength(content.length());//print the line containing the content length to the client
  client.println();//One blank line
  client.println(content);//And last but not least the content
}

//Create a get request for the timestamp and return it
String getTimeStamp() {
  client.print(F("GET ")); //It's a get request. We'll print that to the client.
  client.print(http);//Prints "http://" to the client
  client.print(iphost);//Print our IP.
  client.print(apiPath);//Print the path to the API of the gateway
  client.print(F("tijd "));//We'll print it to the tijd page of the gateway
  client.println(httpVersion);//End this line with "HTTP/1.1"
  createLineHost();//Print the Host line
  client.println();//End with one blank line
  while (!client.available()) { //Wait for the client to come available

  }
  String timestamp = "";
  while (client.available()) {
    timestamp += char(client.read()); //Fill the timestamp variable
    delay(5);
  }
  timestamp = timestamp.substring(timestamp.length() - getContentLength(timestamp) , timestamp.length()); //Gather the length of the timestamp (content) part of the stuff the gateway sent us and we'll create a string containing the timestamp with it
  return timestamp; //Then return it 
}

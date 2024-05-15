//Register the weather station
void registreerWeerstation() {
  client.print(F("POST ")); //Print the fact that we're doing a POST request
  client.print(http); //Prints "http://" to the client
  client.print(getIp(iphost, false)); //Print our IP. Using the getIp method due to errors in the usage of String(iphost)
  client.print(apiPath); //Print the path to the API of the gateway
  client.print(F("WeerstationID ")); //We're gonna POST to the "WeerstationID" webpge
  client.println(httpVersion); //End this line with "HTTP/1.1"
  client.println(F("Content-type: application/json")); //Print the content type
  createLineHost(); //Print the Host line
  String valueNames[] = {"Ip", "Id"}; //The content is going to contain the Ip and the Id of this weatherstation
  String values[] = {getIp(ip, true), weatherStationId}; //get the IP and the weatherStationID
  String content = createContentLine(valueNames, values, 2); //Create the content line with 2 values
  createLineContentLength(content.length()); //Now we know our content we can create the line containing the content length
  client.println(); //So far our request, let's head over to our content
  client.println(content);//Print the actual content to the client
}

//Creates the content line. 
// @params valueNames[] (the names of the stuff you'd like to insert), values[] (the values you'd like to insert), nValues (amount of values you're going to insert).
String createContentLine(String valueNames[], String values[], int nValues) {
  String contentLine = "{"; //Open the contentline
  for (int i = 0; i < nValues; i++) {
    contentLine += "\""; //Add a double quote
    contentLine += valueNames[i]; //Then the name of the value you're going to insert
    contentLine += "\":"; //Then anouther quote followed by a colon
    contentLine += values[i]; //Finished by the actual value
    if (i != nValues - 1) {
      contentLine += ","; //For every value other than the last we'll add a comma
    }
  }
  contentLine += "}"; // End the contentline
  return contentLine; //And return it
}

//Print the content-length line to the client
// @params contentLength (the content-length value)
void createLineContentLength(int contentLength) {
  client.print(F("Content-Length: ")); //Print Content-Length followed by a colon
  client.println(String(contentLength)); //followed by the actual content length
}

//Print the host line using the ip of the host
void createLineHost() {
  client.print(F("Host: "));
  client.println(iphost);
}

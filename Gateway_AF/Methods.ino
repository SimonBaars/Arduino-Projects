//Read a string from number i to the end. It'll return the first number it'll find.
// @params string (a string containing a number somewhere), i (that somewhere is i)
float getNumberAt(String string, int i) {
  for (int j = i;  j < string.length(); j++) {//we'll check the whole string for numbers
    if (!((string.charAt(j) >= '0' && string.charAt(j) <= '9') || string.charAt(j) == '.')) { //As we're searching for a float we can keep looping as long as we find a number or a '.'
      return (string.substring(i, j)).toFloat(); //Convert the found number to a float and return it
    }
  }
  return 0.0;
}

//Read a string searching for the content length. We'll return the content length if it was found, if not, the content length is simply 0.
// @params data (the string we are searching for the content length)
int getContentLength(String data) {
  for (int i = 0; i < data.length() - 15; i++) {
    if (data.substring(i, i + 15) == F("Content-Length:")) { //If the string we're currently checking is actually "Content-Length:"
      return int(getNumberAt(data, i + 16)); //We'll return the number we can find there converted to an integer
    }
  }
  return 0;
}

//Read through everythings that's available to the client and add it to the httpData string
void readHttpData() {
  while (client.available()) { //As long as we can find characters
    httpData += char(client.read()); //Add the found character to the httpData string
    delay(3);
  }
}

//In some instances String(ip) doesn't work correctly. Here we'll create the ip string manually.
// @params ip (the IP Adress we want to convert to a string), quotes (do we want quotes around the string or not?)
String getIp(IPAddress ip, bool quotes) {
  String ipString = "";
  if (quotes) {
    ipString += "\"";
  }
  for (int i = 0; i < 4; i++) {
    ipString += String(ip[i]);
    if (i != 3) {
      ipString += ".";
    }
  }
  if (quotes) {
    ipString += "\"";
  }
  return ipString;
}

//Flush the client, as the .flush() method doesn't work correctly sometimes
void doFlush() {
  while (!client.available()) {//Wait for the client to come available

  }
  while (client.available()) { //Read everything into nothingness
    client.read();
    delay(5);
  }
}

//Read a string searching for the content length. We'll return the content length if it was found, if not, the content length is simply 0.
int getContentLength() {
  for (int i = 0; i < httpData.length() - 15; i++) {
    if (httpData.substring(i, i + 15) == "Content-Length:") {
      i += 16;
      for (int j = i;  j < httpData.length(); j++) {
        if (!((httpData.charAt(j) >= '0' && httpData.charAt(j) <= '9') || httpData.charAt(j)=='.')) {
          return (httpData.substring(i, j)).toInt();
        }
      }
    }
  }
  return 0;
}

//Reads all that is available and stores it in the httpData string
void readHttpData() {
  while (client.available()) {
    httpData += char(client.read());
  }
  Serial.println(httpData);
}

//Prints the content line in json to the client
void returnJson(String waardes[], int nWaardes) {
  client.println(F("HTTP/1.1 200 OK"));
  client.println(F("Content-Type: application/json"));
  createLineContentLength(92);
  client.println();
  createContentLine(waardes, nWaardes);
}

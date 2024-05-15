// send a 404
void send404()
{
  client.println(F("HTTP/1.1 404 NOT FOUND"));
  client.println();
}

// send a standard http response header
// @params title (the title of the header)
void sendHeader(char *title)
{
  client.println(F("HTTP/1.1 200 OK"));
  client.println(F("Content-Type: text/html"));
  client.println();
  client.print(F("<html><head><title>"));
  client.println(title);
  client.println(F("</title><body>"));
}

//create a simple webpage containing values
// @params waardes[](The values to be displayed on the page), nWaardes (the amount of values)
void createWebpage(String waardes[], int nWaardes)
{
  sendHeader("Groetservice");
  client.print("<h3>");
  for (int i = 0; i < nWaardes; i++) {
    client.print(waardes[i]);
    client.print("<BR>");
  }
  client.println("</h3>");
  client.println(F("</body></html>"));
}

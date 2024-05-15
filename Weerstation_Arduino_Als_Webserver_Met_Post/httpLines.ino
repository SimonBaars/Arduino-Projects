//Create the content length line
// @params contentLength (the size of the content length)
void createLineContentLength(int contentLength) {
  client.print("Content-Length: ");
  client.println(String(contentLength));
}

//Create the entire content line
// @params waardes[] (Strings we'd like to name the values), nWaardes (the amount of values)
void createContentLine(String waardes[], int nWaardes) {
  client.println("{");
  for (int i = 0; i < nWaardes; i++) {
    client.print("  ");
    client.print(waardes[i]);
    if (i != nWaardes - 1) {
      client.println(",");
    } else {
      client.println();
    }
    Serial.println(waardes[i]);
  }
  client.println("}");
}

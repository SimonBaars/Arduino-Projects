//Process POST data if it is available
void processPostDataIfAvailable() {
  client.print(httpVersion); //Let's begin with the response. As we're just processing POST data there's no content. We'll tell the gateway this by returning a 204 No Content.
  client.println(F(" 204 No Content"));
  client.println();// And an empty line
  readContent(httpData.substring(httpData.length() - getContentLength(httpData) , httpData.length())); //Afterwards we'll do the actual reading of the content sending the content
}

//Read the min and max temperature
// @params content (the content line we've received)
void readContent(String content) {
  for (int i = 0; i < content.length()-8; i++) { //Go through the complete content -8 (because the last 8 bytes can NEVER contain what we're looking for, as, if they would, there wouldn't be any space anymore for the number to be in)
    String currentData = content.substring(i, i + 7); //capture "minimum", "maximum" or anything else we'll might find
    currentData.toLowerCase(); //If there's uppercase characters we'll set 'em to lowercase
    if (currentData.equals(F("minimum"))) { //Minimum temperatures
      minTemp = getNumberAt(content, i + 9); //set the minimum temperature to the number we'll find here
    } else if (currentData.equals(F("maximum"))) {//Maximum temperatures
      maxTemp = getNumberAt(content, i + 9);//set the maximum temperature to the number we'll find here
    }
  }
  boundariesObtained = true;//Now we can start sending the values to the gateway
}

//Check the min and max temperature to decide what pin will set to HIGH
// @params temperature (the current temperature)
int bepaalWelkeLed(float temperature) {
  if (temperature < minTemp) { //If the temperature is less than the minimal temperature the YELLOW light will burn
    return YELLOW;
  }
  else if (temperature > maxTemp) {//If the temperature is more than the maximal temperature the RED light will burn
    return RED;
  }
  return GREEN;//In all other cases the GREEN light will burn
}

//Manages turning the leds on and off
void manageLeds() {
  for (int i = 0; i < aantalPinnetjes; i++) { 
    digitalWrite(ledPins[i], LOW); //Set all pins to the LOW value
  }
  digitalWrite(bepaalWelkeLed(CELSIUS), HIGH); //Set the right pin to HIGH
}

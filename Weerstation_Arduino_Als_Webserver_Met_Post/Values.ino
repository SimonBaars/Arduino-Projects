//Fills webData with the right values
void getWaardes(int waardes[], int nWaardes, boolean isJson) { //(0 = Amount of Lux, 1 = Minimal Temperature, 2 = Maximal Temperature, 3 = Temperature)
  webData = new String[nWaardes];
  for (int i = 0; i < nWaardes; i++) {
    switch (waardes[i]) {
      case 0: webData[i] = maakWaarde("Aantal lux", lux, isJson); break;
      case 1: webData[i] = maakWaarde("Min Temperatuur", minTemp, isJson); break;
      case 2: webData[i] = maakWaarde("Max Temperatuur", maxTemp, isJson); break;
      case 3: webData[i] = maakWaarde("Temperatuur", temperatuur, isJson); break;
    }

  }
}

//Check the post data for values and change the temperature if it is actually available
// @params minTempIsset (if the maxtemp has to be set instead of the mintemp)
void processPostDataIfAvailable(bool minTempIsset) {
  client.println(F("HTTP/1.1 204 No Content"));
  client.println();
  int contentLength = getContentLength();
  if (contentLength != 0) {
    float toBeTemp = (httpData.substring(httpData.length() - contentLength , httpData.length())).toFloat();
    if (minTempIsset) {
      maxTemp=toBeTemp;
    }
    else {
      minTemp=toBeTemp;
    }
  }
}

//Create the content line data for a value
// @params waardeString (the name of the value that you want the json code of), waardeFloat (the value as a float), isJson (does the output have to be json or not?)
String maakWaarde(String waardeString, float waardeFloat, boolean isJson) {
  String waarde = "";
  if (isJson) {
    waarde += "\"";
  }
  waarde += waardeString;
  if (isJson) {
    waarde += "\"";
  }
  waarde += ": ";
  waarde += waardeFloat;
  return waarde;
}


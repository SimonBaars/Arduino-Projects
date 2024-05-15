//Check the min and max temperature to decide what pin will set to HIGH
// @params temperature (the current temperature)
int bepaalWelkeLed() {
  if (temperatuur < minTemp) { //If the temperature is less than the minimal temperature the YELLOW light will burn
    return YELLOW;
  }
  else if (temperatuur > maxTemp) {//If the temperature is more than the maximal temperature the RED light will burn
    return RED;
  }
  return GREEN;//In all other cases the GREEN light will burn
}


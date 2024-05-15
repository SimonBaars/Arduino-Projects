#include "temperature.h"
#include "Arduino.h"
#include "humidity.h"
#include "misc.h"

// Returns the temperature sensor and rounds it at 0.5
float readTemperature() {
  float temp = (5.0 * analogRead(TEMPPIN) * 100.0) / 1024.0;
  
  temp = roundAt(temp, 0.5);

  //Serial.println(temp);
  
  /*float dhttemp = readDHTtemperature();

  if (temp > dhttemp + tempmargindegrees || temp < dhttemp - tempmargindegrees) 
    return TEMP_OUT_OF_BOUND;
  else if (temp <= 0) 
    return INVALID_TEMP_LM35;*/
    
  return temp;
}


#include "humidity.h"
#include "misc.h"
#include "config.h"

DHT dht(DHTPIN, DHTTYPE);

/* Initialise humidity sensor. */
void initHumidity() {
  dht.begin();
}

/* Read the current humidity percentage. */
int readHumidity() {
  int h = dht.readHumidity();
  if (isnan(h)) 
    return INVALID_HUMIDITY;
  
  return h;
}

/* Returns the current temperature from the DHT sensor. */
float readDHTtemperature() {
  float t = dht.readTemperature();
  if (isnan(t)) 
    return INVALID_TEMP_DHT;
  
  return roundAt(t, 0.5);
}

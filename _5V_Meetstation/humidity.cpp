#include "humidity.h"
#include "misc.h"

DHT dht(DHTPIN, DHTTYPE);

/* Initialise humidity sensor. */
void initHumidity() {
  dht.begin();
}

/* Read the current humidity percentage. */
int readHumidity() {
  interrupts();
  int h = dht.readHumidity();
  if (h <= 0 || isnan(h)) 
    return INVALID_HUMIDITY;
  noInterrupts();
  return h;
}

/* Returns the current temperature from the DHT sensor. */
float readDHTtemperature() {
  interrupts();
  float t = dht.readTemperature();
  if (t <= 0 || isnan(t)) 
    return INVALID_TEMP_DHT;
  noInterrupts();
  return t;
}

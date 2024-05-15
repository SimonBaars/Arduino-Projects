#ifndef _HUMIDITY_H
#define _HUMIDITY_H

#include <DHT.h>
#include "Arduino.h"

#define DHTTYPE DHT11
#define DHTPIN 5

// Initialising
void initHumidity();

// Returns the humidity
int readHumidity();

// Returns the temperature
float readDHTtemperature();

#endif

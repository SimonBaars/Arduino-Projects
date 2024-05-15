#ifndef _HUMIDITY_H
#define _HUMIDITY_H

#include <DHT.h>
#include "Arduino.h"

/* Initialise humidity sensor. */
void initHumidity();

/* Returns the current humidity percentage. */
int readHumidity();

/* Returns the current temperature from the DHT sensor. */
float readDHTtemperature();

float roundAt(float value, float interval);

#endif

#ifndef _TEMPERATURE_H
#define _TEMPERATURE_H

#include <OneWire.h>

#define tempmargindegrees 2

extern OneWire* ds;

/* Read the current temperature from the DS18B20. */
float readTemperature();

#endif

#ifndef _LIGHTINTENSITY_H
#define _LIGHTINTENSITY_H

#define LIGHTPIN A1

// ReadLigthRAW value of the analog light pin
int readLightRAW();

// Returns the light value in lux
int readLight();

#endif

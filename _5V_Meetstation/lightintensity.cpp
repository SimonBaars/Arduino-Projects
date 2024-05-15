#include "lightintensity.h"
#include "Arduino.h"
#include "misc.h"

int lightrawmin = 400; // Calibration RAW where lux = 0
int lightrawmax = 900; // Calibration RAW where lux = 567

int luxmin = 0; // Calibration RAW where raw = 400
int luxmax = 567; // Calibration RAW where raw = 900

// ReadLigthRAW value of the analog light pin
int readLightRAW() {
  return analogRead(LIGHTPIN);
}

// Returns the light value in lux
int readLight() {
  int l = map(readLightRAW(), lightrawmin, lightrawmax, luxmin, luxmax);
  if (l <= 0) 
    return INVALID_LIGHT;
  
  return l;
}

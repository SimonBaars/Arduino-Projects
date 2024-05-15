#ifndef _MISC_H
#define _MISC_H

/* Error codes. */
typedef enum {
  TEMP_OUT_OF_BOUND = -99,    //The deviation of the lm35 and the dht is more than 2 degrees
  INVALID_TEMP_LM35,          //The lm35 gives negative falues
  INVALID_TEMP_DHT,           //The dht gives negatives falues
  INVALID_HUMIDITY,           //The humidity sensor gives negative falues
  INVALID_LIGHT,              //The lightsensor gives negative falues
  INVALID_DUST,               //The dust sensor gives negative falues
  DUST_INITIALISING           //The dust sensor is initialising
} error;

// Rounds a value at the given interval (like 0.5)
float roundAt(float value, float interval);

#endif

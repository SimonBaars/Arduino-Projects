#ifndef _ERRORCODES_H_
#define _ERRORCODES_H_

/* 
 * Error codes. 
 */
typedef enum {
  TEMP_OUT_OF_BOUND = -99,    //The deviation of the lm35 and the dht is more than 2 degrees
  INVALID_TEMP,               //The LM35 or DS18B20 gives negative values
  INVALID_TEMP_DHT,           //The dht gives negatives values
  INVALID_HUMIDITY,           //The humidity sensor gives negative values
  INVALID_LIGHT,              //The lightsensor gives negative values
  INVALID_DUST,               //The dust sensor gives negative values
  DUST_INITIALISING,          //The dust sensor is initialising
  INVALID_DOOR,				        //The door returns a percent not between 0 and 100
  SENSOR_UNAVAILABLE,
  LOWBATTERY                  //The battery is almost empty
} error;

#endif /* _ERRORCODES_H_ */

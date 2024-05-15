#ifndef _DATA_CONTROLLER_H
#define _DATA_CONTROLLER_H
 
#include <stdint.h>
#include "dataStructure.h"

/* Send sensor data to the master. */
bool sendData(uint8_t id);

/* Print all the sensor data to the serial. */
void debugPayload(sensorData_t* payload);

#endif /* _DATA_CONTROLLER_H */

#ifndef _DATA_CONTROLLER_H
#define _DATA_CONTROLLER_H
 
#include <stdint.h>

typedef struct __attribute__((packed)){
  unsigned short checksum;
  int8_t id;        
  float temperature;
  int8_t humidity;
  int16_t light;
  int16_t audio;
  int16_t dust;
  int16_t openDoorTime;
  bool motionDetected;
} sensorData_t;

/* Send sensor data to the master. */
bool sendData(int8_t id);

/* Print all the sensor data to the serial. */
void debugPayload(sensorData_t* payload);

#endif /* _DATA_CONTROLLER_H */

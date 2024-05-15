#ifndef _DATA_CONTROLLER_H
#define _DATA_CONTROLLER_H

#include <stdint.h>

typedef struct __attribute__((packed)) {
  int8_t id;          // Node id
  float temperature;
  int8_t humidity;
  int light;
  int audio;
  int dust;
  int openDoorTime;
  bool motionDetected;
  unsigned short checksum;
} sensorData5_t;

/* Send sensor data to the master. */
bool sendData(int8_t id);

/* Print all the sensor data to the serial. */
void debugPayload(sensorData5_t* payload);

#endif /* _DATA_CONTROLLER_H */

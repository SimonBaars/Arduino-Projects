#ifndef _DATASTRUCTURE_H
#define _DATASTRUCTURE_H

/*
 * Data structure
 */ 

 /*Packed: Omdat we de struct aan de andere kant precies op dezelfde volgorde moeten afvangen.
forceren we de struct om in deze volgorde te blijven door gebruik te maken van ((packed)) */

typedef struct __attribute__((packed)) {
  uint8_t id;        
  float temperature;
  int8_t humidity;
  int16_t light;
  int16_t audio;
  int16_t dust;
  int8_t openDoorTime;
  bool motionDetected;
  int8_t battery;
  unsigned short checksum;
} sensorData_t;

#endif /* _DATASTRUCTURE_H */


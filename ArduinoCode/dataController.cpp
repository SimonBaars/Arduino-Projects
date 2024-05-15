#include "dataController.h"
#include "door.h"
#include "humidity.h"
#include "lightintensity.h"
#include "motion.h"
#include "temperature.h"
#include "crc16.h"
#include "misc.h"

#include <stdlib.h>
#include "RF24.h"
#include "RF24Network.h"
#include "RF24Mesh.h"

extern RF24Mesh mesh;

// Fill payload struct with sensor data.
void initPayload(sensorData_t* payload, int8_t id) {
  payload->id = id;
  payload->temperature = readTemperature();
  payload->humidity = readHumidity();
  payload->light = readLightRAW();
  payload->openDoorTime = getOpenDoorTime();
  payload->motionDetected = readMotionDetected();
  payload->audio = SENSOR_UNAVAILABLE;
  payload->dust  = SENSOR_UNAVAILABLE;

  // Calculate checksum.
  payload->checksum = crcsum((unsigned char*)payload, sizeof(sensorData_t) - sizeof(unsigned short), CRC_INIT);
}

// Send the data.
bool sendData(int8_t id) {
  sensorData_t *payload = (sensorData_t*)malloc(sizeof(sensorData_t));
  if (payload == NULL)
    return false;

  // Read sensors
  initPayload(payload, id);

  // Send struct containing data
  if (!mesh.write(((void*)payload), '3', sizeof(sensorData_t))) {
    if (!mesh.checkConnection()) {
      //refresh the network address if fails
      mesh.renewAddress();
      free(payload);
      return false;
    } 
    else {
      free(payload);
      return false;
    }
  }

#ifdef DEBUG
  debugPayload(payload);
#endif

  free(payload);

  return true;
}

void debugPayload(sensorData_t* payload) {
  Serial.print(F("ID: "));
  Serial.println(payload->id);
  Serial.print(F("Temperature: "));
  Serial.println(payload->temperature);
  Serial.print(F("Humidity: "));
  Serial.println(payload->humidity);
  Serial.print(F("Light: "));
  Serial.println(payload->light);
  Serial.print(F("Open door time: "));
  Serial.println(payload->openDoorTime);
  Serial.print(F("Motion: "));
  Serial.println(payload->motionDetected);
  Serial.print(F("Audio: "));
  Serial.println(payload->audio);
  Serial.print(F("Dust: "));
  Serial.println(payload->dust);
  Serial.print(F("Checksum: "));
  Serial.print(payload->checksum);
  
  if (crcverify((unsigned char*)payload, sizeof(sensorData_t)))
    Serial.println(F(" correct"));
  else
    Serial.println(F(" incorrect"));
}

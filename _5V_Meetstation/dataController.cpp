#include "dataController.h"
#include "door.h"
#include "humidity.h"
#include "lightintensity.h"
#include "motion.h"
#include "temperature.h"
#include "dust.h"
#include "sound.h"
#include "crc16.h"
#include "misc.h"

#include <stdlib.h>
#include "RF24.h"
#include "RF24Network.h"
#include "RF24Mesh.h"

extern RF24Mesh mesh;

// Fill payload struct with sensor data.
void initPayload(sensorData5_t* payload, int8_t id) {
  payload->id = id;
  payload->temperature = readTemperature();
  payload->humidity = readHumidity();
  payload->light = readLight();
  payload->audio = getNoiseNumber();
  payload->dust = getDustValue();
  payload->openDoorTime = getOpenDoorTime();
  payload->motionDetected = motionDetected();

  // Calculate checksum.
  payload->checksum = crcsum((unsigned char*)payload, sizeof(sensorData5_t) - sizeof(unsigned short), CRC_INIT);
}

// Send the data.
bool sendData(int8_t id) {
  sensorData5_t *payload = (sensorData5_t*)malloc(sizeof(sensorData5_t));
  if (payload == NULL)
    return false;

  // Read sensors
  initPayload(payload, id);
  //message.set((void*)payload, sizeof(sensorData5_t));

  // Send struct containing data
  if (!mesh.write(((void*)payload), '5', sizeof(sensorData5_t))) {
    if ( ! mesh.checkConnection() ) {
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

  //debugPayload(payload);
  free(payload);

  return true;
}

void debugPayload(sensorData5_t* payload) {
  Serial.print(F("ID: "));
  Serial.println(payload->id);
  Serial.print(F("Temperature: "));
  Serial.println(payload->temperature);
  Serial.print(F("Humidity: "));
  Serial.println(payload->humidity);
  Serial.print(F("Light: "));
  Serial.println(payload->light);
  Serial.print(F("Audio: "));
  Serial.println(payload->audio);
  Serial.print(F("Dust: "));
  Serial.println(payload->dust);
  Serial.print(F("Open door time: "));
  Serial.println(payload->openDoorTime);
  Serial.print(F("Motion: "));
  Serial.println(payload->motionDetected);
  Serial.print(F("Checksum: "));
  Serial.print(payload->checksum);
  if (crcverify((unsigned char*)payload, sizeof(sensorData5_t)))
    Serial.println(F(" correct"));
  else
    Serial.println(F(" incorrect"));
}

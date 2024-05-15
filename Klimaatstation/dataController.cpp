#include "includes.h"
#include "dataController.h"
#include "dataStructure.h"
#include "crc16.h"

#include <stdlib.h>
#include "RF24.h"
#include "RF24Network.h"
#include "RF24Mesh.h"

extern RF24Mesh mesh;

// Payload header
void initPayload(sensorData_t* payload, uint8_t id);

// Fill payload struct with sensor data.
void initPayload(sensorData_t* payload, uint8_t id) {    //Wanneer sensor niet beschikbaar, vervangen door: SENSOR_UNAVAILABLE
  payload->id = id;

#ifdef TEMPPINLM35
  payload->temperature = readTemperatureLM35();
#elif TEMPPINDS18B20
  payload->temperature = readTemperatureDS18();
#else 
  payload->temperature = SENSOR_UNAVAILABLE;
#endif
#ifdef DHTPIN
  payload->humidity = readHumidity();
#else 
  payload->humidity = SENSOR_UNAVAILABLE;
#endif
#ifdef LIGHTPIN
  payload->light = readLightRAW();
#else 
  payload->light = SENSOR_UNAVAILABLE;
#endif
#ifdef DOORPIN
  payload->openDoorTime = getAndResetOpenDoorTime();
#else
  payload->openDoorTime = SENSOR_UNAVAILABLE;
#endif
#ifdef MOTIONPIN
  payload->motionDetected = readAndResetMotionDetected();
#else
  payload->motionDetected = SENSOR_UNAVAILABLE;
#endif
#ifdef SOUNDPIN
  payload->audio = getAndResetPeakAmount();
#else
  payload->audio = SENSOR_UNAVAILABLE;
#endif
#ifdef DUSTPIN
  payload->dust  = getDustValue();
#else
  payload->dust  = SENSOR_UNAVAILABLE;
#endif
#ifdef BATTERYINDICATORPIN
  payload->battery = getBatteryWarning();
#else
  payload->battery = SENSOR_UNAVAILABLE;
#endif

  // Calculate checksum.
  payload->checksum = crcsum((unsigned char*)payload, sizeof(sensorData_t) - sizeof(unsigned short), CRC_INIT);
}

// Send the data.
bool sendData(uint8_t id) {
  sensorData_t *payload = (sensorData_t*)malloc(sizeof(sensorData_t));
  if (payload == NULL)
    return false;

  // Read sensors
  initPayload(payload, id);

  // Send struct containing data
  if (!mesh.write(((void*)payload), SENSORDATAHEADER, sizeof(sensorData_t))) {
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

/*#ifdef DEBUG
  debugPayload(payload);
#endif*/
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
  Serial.print(F("Battery: "));
  Serial.println(payload->battery);
  Serial.print(F("Checksum: "));
  Serial.println(payload->checksum);
  
  if (crcverify((unsigned char*)payload, sizeof(sensorData_t))) {
    Serial.println(F(" correct"));
  }
  else {
    Serial.println(F(" incorrect"));
  }
}

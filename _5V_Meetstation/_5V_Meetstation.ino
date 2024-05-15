/*****************************************************
 **Klimaatstation ICA Studeeromgeving
 **
 **IoT Groep 1 SensorWizards
 **
 **20-11-2015
 *****************************************************/
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

#include <SPI.h>
#include "RF24.h"
#include "RF24Network.h"
#include "RF24Mesh.h"
#include <SPI.h>
#include <EEPROM.h>
#include <DHT.h>

// ID, delay for sending and maximal id
#define ID 2 // current node id 1-254
#define INTERVAL 600000 // 10 minute(s) between sending sensordata
#define MAX_ID 254 // Max id's RF24Mesh supports
#define channel 26 // Channel the mesh operates on

// nRF24L01 initialisation
RF24 radio(9, 10);
RF24Network network(radio);
RF24Mesh mesh(radio, network);

// Time controllers
unsigned long oldmillis = 0;

void setup() {
  // Arduino serial setup.
  Serial.begin(9600);
  while(!Serial)
    ; // Wait for Serial to startup.

  initHumidity(); // Initialize DHT11
  initMotion();   // Initialize HC-SR501
  initAudio();    // Initialize microphone
  initDoor();     // Initialize door sensor
  initDust();     // Initialize GP2Y1010AU0F

  // The timer.
  //sendTimer.interval = (INTERVAL * ID) / MAX_ID;

  // Initialisation node.
  mesh.setNodeID(ID);

  // Connect to the mesh
  //Serial.println(F("Connecting to the mesh..."));
  mesh.begin(channel); // Init mesh on channel 26

  //Serial.println(F("5 volt station started..."));

}

void loop() {
  mesh.update();
  if (millis() - oldmillis > INTERVAL) {
    noInterrupts();
    oldmillis = millis();
    if (!sendData(ID)) {
      Serial.println(F("Error sending data."));
    }

    readTemperature(); // Delete broken value (bug in LM35) WORKAROUND
    interrupts();
  }
}


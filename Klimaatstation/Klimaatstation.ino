/*************************************************
   IoT Groep 1 SensorWizards klimaatstation

   ICA Studeeromgeving

   Internet of Things 2015-2016 S1
 *************************************************/

// For the data
#include "dataController.h"

// Sensor includes
#include "includes.h"

// Sleep libraries
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>

// NRF24l01 libraries
#include "RF24.h"
#include "RF24Network.h"
#include "RF24Mesh.h"
#include <SPI.h> // For the SPI connection to the NRF24l01
#include <EEPROM.h>

#define EEPROMCURRENTRESET 0

// nRF24L01 initialisation
RF24 radio(NRF24_CE, NRF24_CSN); // See config.h
RF24Network network(radio);
RF24Mesh mesh(radio, network);

#ifdef SLEEP
unsigned long connectOldmillis = 0; // Last time it started connecting
unsigned int connectInterval = CONNECTTIME; //   // Interval the station is allowed to try to connect to the mesh again (ms)
#else
unsigned long oldMillis = SENDINTERVAL; // Last time the Arduino sent its data
#endif

volatile int watchdogTimer = SLEEPTIME; // This is the watchdog timer. It counts the amount of times the Arduino slept (watchdog). It is volatile because it is used by an interrupt (sleeping is an interrupt, see ISR(); at the end of this document)

void setup() {

#ifdef DEBUG

  // Arduino serial setup for debugging
  Serial.begin(SERIALBAUDRATE); // See config.h
  while (!Serial)
    ; // Wait for Serial to start

  Serial.println(F("Starting....."));

#endif

#ifdef TEMPPINLM35
  initTemperature(); // Initialize LM35
#endif
#ifdef DHTPIN
  initHumidity(); // Initialize DHT11/DHT22
#endif
#ifdef MOTIONPIN
  initMotion();   // Initialize HC-SR501
#endif
#ifdef SOUNDPIN
  initAudio();    // Initialize microphone
#endif
#ifdef DOORPIN
  initDoor();     // Initialize door/window sensor
#endif
#ifdef DUSTPIN
  initDust();     // Initialize GP2Y1010AU0F (dust sensor)
#endif
#ifdef LIGHTPIN
  initLight();    // Initialise the lightsensor
#endif
#ifdef BATTERYINDICATORPIN
  initBatteryIndicator(); // Initialise the battery indicator
#endif

#ifdef SLEEP
  initSleep();    //Initialise the sleepmode
#endif

  /******
     init Mesh
  */
  mesh.setNodeID(ID);   // Initialisation node. See config.h

  // Connect to the mesh
  mesh.begin(CHANNEL);  // Init mesh on defined channel. See config.h

#ifdef DEBUG
  Serial.println(F("Setup complete"));
  delay(500); // Short break for stability because the Serial is an interrupt
#endif

  /**********************
   WORKAROUND DS18B20
  
   If the sensor station is started by powering it, the DS18B20 breaks.
   By resetting it, it will cause an interrupt and software resets the Arduino.
   The DS18B20 only works if the Arduino is started by software
  */
#ifdef TEMPPINDS18B20
    waitForReset();
#endif

}

void loop() {
  /* Arduino sleep code (only when it is not in use as a relay) */
#ifdef SLEEP
  if (watchdogTimer >= SLEEPTIME) { // If it's time to send
    watchdogTimer = 0; // Reset amount of time slept

    connectOldmillis = millis(); // Time started to connect again to the mesh
    while (millis() - connectOldmillis < connectInterval) { // Reconnect to the mesh
      mesh.update();
    }

    noInterrupts();
#ifdef DEBUG
    if (!sendData(ID)) {
      interrupts(); // Interrupt is neccessary because we need to print
      Serial.println(F("Error sending data."));
      delay(100); // Give time for printing
      noInterrupts(); // Turn them off again for safety
    }
#else
    sendData(ID); // Capute data and send it to the gateway (see dataController.cpp)
#endif
    interrupts(); // Time to monitor again.

    enterSleep(); // Start sleeping again
#ifdef DEBUG
    Serial.println(F("Entering sleep after sending"));
#endif
  } else {
#ifdef DEBUG
    Serial.println(F("Entering sleep after sending"));
#endif
    enterSleep(); // Start sleeping again
  }
#else
  /* Send timer */
  mesh.update(); // Runs constantly to transfer data from other stations to gateway (MESH)
  if (millis() - oldMillis > SENDINTERVAL) { // If it's time to send data
    oldMillis = millis(); // Last time it sent

    //noInterrupts(); // No interrupts allowed for safety
    mesh.update(); // Update again
#ifdef DEBUG
    if (!sendData(ID)) {
      //interrupts(); // Interrupt is neccessary because we need to print
      Serial.println(F("Error sending data."));
      //noInterrupts(); // Turn them off again for safety
    }
#else
    sendData(ID); // Capute data and send it to the gateway (see dataController.cpp)
#endif


    /********
       WORKAROUND

       analogRead breaks at the LM35 code, so we need to call it again. This will make it work the first time and break the second time (this time).
       We've tried to figure it out, spent 2 hours and found this workaround.
     ************/

#ifdef TEMPPINLM35
    readTemperatureLM35();
#endif
    /* END WORKAROUND */

    interrupts(); // Allow interrupts again
  }
#endif
}

// Sleep library Arduino
void enterSleep() {
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);   /* EDIT: could also use SLEEP_MODE_PWR_DOWN for lowest power consumption. */
  sleep_enable();

  /* Now enter sleep mode. */
  sleep_mode();

  /* The program will continue from here after the WDT timeout*/
  sleep_disable(); /* First thing to do is disable sleep. */

  /* Re-enable the peripherals. */
  power_all_enable();
}

// The interrupt of the sleep
ISR(WDT_vect) {
  watchdogTimer++;
}

// Initialise sleep
void initSleep() {
  /*** Setup the WDT ***/
  /* Clear the reset flag. */
  MCUSR &= ~(1 << WDRF);

  /* In order to change WDE or the prescaler, we need to
     set WDCE (This will allow updates for 4 clock cycles).
  */
  WDTCSR |= (1 << WDCE) | (1 << WDE);

  /* set new watchdog timeout prescaler value */
  WDTCSR = 1 << WDP0 | 1 << WDP3; /* 8.0 seconds */
  /* Enable the WD interrupt (note no reset). */
  WDTCSR |= _BV(WDIE);
}

#ifdef TEMPPINDS18B20
void waitForReset() {
  if (EEPROM.read(EEPROMCURRENTRESET) == 0) {
    EEPROM.write(EEPROMCURRENTRESET, 1);
    readTemperatureDS18();
    while (1) {
      // Wait for the user to reset
    }
  }
  else if (EEPROM.read(EEPROMCURRENTRESET) == 1) {
    EEPROM.write(EEPROMCURRENTRESET, 0);
  }
}
#endif

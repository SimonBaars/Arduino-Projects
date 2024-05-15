/*************************************************
 * IoT Groep 1 SensorWizards klimaatstation
 * 
 * ICA Studeeromgeving
 * 
 *************************************************/

#include "misc.h"
#include "door.h"
#include "dataController.h"
#include "door.h"
#include "humidity.h"
#include "motion.h"
#include "temperature.h"
#include "lightintensity.h"
#include "config.h"

// Sleep libraries
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>

#include <SPI.h>
#include "RF24.h"
#include "RF24Network.h"
#include "RF24Mesh.h"
#include <SPI.h>
#include <EEPROM.h>
#include <DHT.h>
#include <OneWire.h>

#define INTERVAL 600000 // 10 minute(s) (600.000 seconds) between sending sensordata
#define MAX_ID 254 // Max id's RF24Mesh supports

// nRF24L01 initialisation
RF24 radio(NRF24_CE, NRF24_CSN);
RF24Network network(radio);
RF24Mesh mesh(radio, network);

Timer connecttimer;
Timer sendTimer;

#define SLEEPTIME 75 //10 minuten slapen, formule: ((10*60)/8 = 75).

volatile int f_wdt = SLEEPTIME;

void setup() {
  // Arduino serial setup.
  Serial.begin(9600);
  while (!Serial)
    ; // Wait for Serial to startup.

  // Initialise sensors.
  initDoor();
  initHumidity();
  initMotion();

  // The timer.
  connecttimer.interval = 1500;

  //Initialise the sleepmode
  initSleep();

  // Initialisation node.
  mesh.setNodeID(ID);

  // Connect to the mesh
  mesh.begin(CHANNEL); // Init mesh on channel 26
}

void loop() {
  if (f_wdt >= SLEEPTIME) {
    f_wdt = 1;
    noInterrupts();
    connecttimer.oldmillis = millis();
    while (millis() - connecttimer.oldmillis < connecttimer.interval) { // Reconnect to the mesh
      mesh.update();
    }
#ifdef DEBUG
    if (!sendData(ID))
      Serial.println("Error sending data.");
#else
    sendData(ID);
#endif
    interrupts();
    doorTimer();
    delay(100);
    enterSleep();
  } else {
    doorTimer();
    delay(100);
    enterSleep();
  }
}

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

ISR(WDT_vect) {
  f_wdt++;
}

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

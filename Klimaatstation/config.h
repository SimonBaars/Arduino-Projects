#ifndef _CONFIG_H
#define _CONFIG_H

/* Serial debugging (comment out to remove serial debugging). */
//#define DEBUG 1
#define SERIALBAUDRATE 9600

/********
 * SLEEP
 *******/
/* If the arduino is able to sleep */
#define SLEEP 1
/* The interval the arduino wil send all the data in seconds*/
#define SENDINTERVAL 600000 // 10 minute(s) (600.000 seconds)
#define SLEEPTIME 75 // 10 minute(s) sleep, formule: ((10minutes*60seconds)/8seconds = 75). Divide it by 8 seconds because the Arduino is able to sleep for 8 seconds max. See 'Technisch ontwerp klimaatstation'.

/***********
 * MESH
 **********/
/* This node's identifier (1-254). */
#define ID 1
/* Channel the mesh network operates on. */
#define CHANNEL 26 
/* Sensor data header: the header of the message on the nrf24 network */
#define SENSORDATAHEADER '3'

#ifdef SLEEP
/* The Arduino has to connect to the mesh again after sleeping, this has to time out after a short period which is defined here (ms). */
#define CONNECTTIME 7500
#endif

/**********
 * SENSORS
 *********/
/* Door pin. */
#define DOORPIN 2
/* Motion pin */
#define MOTIONPIN 3
/* Sound pin */
//#define SOUNDPIN 3
/*DHT pin an type. */
#define DHTTYPE DHT11
#define DHTPIN 5
/* Light sensor pin. */
#define LIGHTPIN A1
/* Temperature pin LM35.(ANALOG 5V) */
#define TEMPPINLM35 A2
/* Tempterature pin DS18 (DIGITAL 3.3V AND 5V)*/
#define TEMPPINDS18B20 4
/* Dust pin */
#define DUSTPIN A0 // Pin for dust value
#define DUSTPOWER 4 // Ledpin for optical dust sensor

/* Pin numbers NRF24L01 */
#define NRF24_CE 9
#define NRF24_CSN 10

/* Pin numbers for the batteryIndicator */
#define BATTERYINDICATORPIN A0 //Pin for the battery voltage indicator
#define referenceVoltage 3.7 //reference voltage, when lower than this value getBatteryWarning gives back an error message.

#endif

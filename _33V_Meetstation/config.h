#ifndef _CONFIG_H
#define _CONFIG_H

/* Serial debugging (comment out to remove serial debugging). */
#define DEBUG 1 

/* This node's identifier (1-254). */
#define ID 1

/* Channel the mesh network operates on. */
#define CHANNEL 26 

/* Door pin. */
#define DOORPIN 2

/*DHT pin an type. */
#define DHTTYPE DHT22
#define DHTPIN 5

/* Light sensor pin. */
#define LIGHTPIN A1

/* Motion pin. */
#define MOTIONPIN 3

/* Temperature pin. */
#define TEMPPIN 4

/* Pin numbers NRF24L01 */
#define NRF24_CE 9
#define NRF24_CSN 10

#endif

#include "timer.h"

Timer mytimer;

void setup() {
  initHumidity();
  mytimer.interval = 1000;
  Serial.begin(9600);
  Serial.println("Weatherstation started!");
}

void loop() {
  if (millis() > mytimer.oldmillis + mytimer.interval) {
    mytimer.oldmillis = millis();

    Serial.print("Temperature DS18B20: ");
    Serial.print(readTemperature());
    Serial.print("\t Humidity DHT-11: ");
    Serial.print(readHumidity());
    Serial.print("\t Temperature DHT-11: ");
    Serial.print(readDHTtemperature());
    Serial.print("\t Lightintensity: ");
    Serial.print(readLight());
    Serial.println();
  }
}


#define DHTTYPE DHT11
#define DHTPIN 5

#include <DHT.h>

DHT dht(DHTPIN, DHTTYPE);

void initHumidity() {
  dht.begin();
}

int readHumidity() {
  int h = dht.readHumidity();
  if (isnan(h)) {
    Serial.println(F("Humidity reading failed!"));
  }
  return h;
}

int readDHTtemperature() {
  int t = dht.readTemperature();
  if (isnan(t)) {
    Serial.println(F("Temperature DHT reading failed!"));
  }
  return t;
}

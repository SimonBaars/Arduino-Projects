#define DHTTYPE DHT11
#define DHTPIN 2

#include <Wire.h>
#include <DHT.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

DHT dht(DHTPIN, DHTTYPE);

//Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

void setup() {
  Serial.begin(9600);
  Serial.println("8x8 LED Matrix Test");

  dht.begin();
  //matrix.begin(0x70);  // pass in the address
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(t) || isnan(h)) {
    Serial.println("Failed to read from DHT");
  }
  else {
    //Serial.print("Temperatuur: ");
    Serial.println(t);

    //Serial.print("Luchtvochtigheid: ");
    Serial.println(h);
    /*
    matrix.setTextSize(1);
    matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
    matrix.setTextColor(LED_ON);
    for (int8_t x = 20; x >= -90; x--) {
      matrix.clear();
      matrix.setCursor(x, 0);
      matrix.print(t);
      matrix.print(" C ");
      matrix.print(h);
      matrix.print("%");
      matrix.writeDisplay();
      delay(100);
    }
    */
  }
}

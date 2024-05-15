#include "dust.h"
#include "Arduino.h"

bool initialized = 0;

// Initialising the dust optical sensor
void initDust() {
  pinMode(ledPower, OUTPUT);
}

// Returns the dust value
float getDustValue() {
  float voMeasured  = 0;
  float calcVoltage = 0;
  float dustDensity = 0;
  
  // read the dust value
  digitalWrite(ledPower, LOW);
  delayMicroseconds(samplingTime);
  // read the dust value
  voMeasured = analogRead(measurePin);

  delayMicroseconds(deltaTime);
  // turn the LED off
  digitalWrite(ledPower, HIGH);
  delayMicroseconds(sleepTime);

  // 0 - 5.0V mapping the dust value
  calcVoltage = voMeasured * (5.0 / 1024);
  dustDensity = (0.17 * calcVoltage - 0.1) * 1000;

  /*if (dustDensity < 0) {
    if (initialized == false) {
      initialized = true;
      Serial.println(F("D2"));
      return 0;
    }
    else {
      Serial.println(F("D1"));
      return 0;
    }
  }*/

  return dustDensity;
}

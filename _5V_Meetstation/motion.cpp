#include "motion.h"
#include "Arduino.h"

// Initalising the motion pin
void initMotion() {
  pinMode(MOTIONPIN, INPUT);
}

// Returns the motion value (true/false)
boolean motionDetected() {
  return digitalRead(MOTIONPIN);
}

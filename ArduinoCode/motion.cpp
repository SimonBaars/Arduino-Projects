#include "motion.h"
#include "Arduino.h"
#include "config.h"

bool motionDetected = false;

/* Initialise motion sensor. */
void initMotion() {
  pinMode(MOTIONPIN, INPUT);
  motionDetected = digitalRead(MOTIONPIN);
  attachInterrupt(digitalPinToInterrupt(MOTIONPIN), detected, RISING);
}

/* Motion detection interrupt. */
void detected() {
  motionDetected = true;
}

/* Returns true if motion is detected in the last _INTERVAL_. */
bool readMotionDetected() {
  bool motion = motionDetected;
  motionDetected = false;
  return motion;
}

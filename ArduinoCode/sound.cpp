#include "sound.h"
#include "Arduino.h"

int noiseNumber = 0;

// Initialiseerd the sounddetector.
void initAudio() {
  pinMode(AUDIOPIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(AUDIOPIN), noiseCounter, FALLING);
}

// Counts the number of times that the sound was loud.
void noiseCounter() {
  noiseNumber ++;
}

// Returns the number of times that the sound was loud and resets the number.
int getNoiseNumber() {
  int value = noiseNumber;
  noiseNumber = 0;
  return value;
}

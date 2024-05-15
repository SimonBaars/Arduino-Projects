#include "door.h"
#include "Arduino.h"
#include "config.h"

bool openDoor = false;

// Initialising the doorpin
void initDoor() {
  pinMode(DOORPIN, INPUT);  //Start een timer wanneer de deur word geopend en eindigt deze wanneer de deur word gesloten
  attachInterrupt(digitalPinToInterrupt(DOORPIN), doorTimer, RISING);
}
// Timer keeps track of the time that the door was openend
void doorTimer() {
  openDoor = true;
}

// Returns the time that the door was open and resets the time
int getOpenDoorTime() {
  bool value = openDoor;
  openDoor = false;
  return value;
}

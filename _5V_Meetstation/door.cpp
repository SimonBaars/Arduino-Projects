#include "door.h"
#include "Arduino.h"

unsigned long int previousDoorTime = 0;
unsigned long int openDoorTime = 0;

// Initialising the doorpin
void initDoor() {
  pinMode(DOORPIN, INPUT);  //Start een timer wanneer de deur word geopend en eindigt deze wanneer de deur word gesloten
  attachInterrupt(digitalPinToInterrupt(DOORPIN), doorTimer, CHANGE);
}

// Timer keeps track of the time that the door was openend
void doorTimer() {
  int doorValue = digitalRead(DOORPIN);
  if (doorValue)   //Closed
    openDoorTime += (millis() - previousDoorTime)/1000;
   else           //Opened
    previousDoorTime = millis();
}

// Returns the time that the door was open and resets the time
int getOpenDoorTime(){
  int value = openDoorTime;
  if (digitalRead(DOORPIN)){
     value += (millis() - previousDoorTime)/1000;
     previousDoorTime = millis();
  }
  openDoorTime = 0;
  return value*(100/(INTERVAL/1000));
}

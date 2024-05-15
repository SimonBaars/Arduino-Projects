#ifndef _DOOR_H
#define _DOOR_H

extern volatile unsigned long int openDoorTime;
extern volatile unsigned long int previousDoorTime;

// Initialising the doorpin
void initDoor();

// Timer keeps track of the time that the door was openend
void doorTimer();

// Returns the time that the door was open and resets the time
int getOpenDoorTime();

#endif

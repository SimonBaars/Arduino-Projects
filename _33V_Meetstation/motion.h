#ifndef _MOTION_H
#define _MOTION_H

extern bool motionDetected;

/* Initialise motion sensor. */
void initMotion();

/* Detection interrupts. */
void detected();

/* Returns true if motion is detected in the last _INTERVAL_. */
bool readMotionDetected();

#endif

#ifndef _MOTION_H
#define _MOTION_H

#define MOTIONPIN 6

/* Initialise motion sensor. */
void initMotion();

/* Returns true if motion is detected. */
bool motionDetected();

#endif

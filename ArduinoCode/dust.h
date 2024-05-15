#ifndef _DUST_H_
#define _DUST_H_

#define ledPower 4 // Ledpin for optical dust sensor
#define measurePin A0 // Pin for dust value

#define samplingTime 280
#define deltaTime 40
#define sleepTime 9680

extern bool initialized;

// Initialising the door pin
void initDust();

// Returns the dust value
float getDustValue();

#endif

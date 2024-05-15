#ifndef _SOUND_H_
#define _SOUND_H_

#define AUDIOPIN 3

// Initialiseerd the sounddetector.
void initAudio();

// Counts the number of times that the sound was loud.
void noiseCounter();

// Returns the number of times that the sound was loud and resets the number.
int getNoiseNumber();

#endif

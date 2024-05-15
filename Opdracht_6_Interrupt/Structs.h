#pragma once
#define GROOTTE 10

typedef struct{
  int beginPos;
  int count;
  int buffersize;
  int array[GROOTTE]; 
}CirculaireBuffer;

CirculaireBuffer c;

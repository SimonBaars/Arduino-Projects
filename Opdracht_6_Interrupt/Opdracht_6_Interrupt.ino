#include "Structs.h"

long start = 0;
volatile long lastButtonPush = 0;
volatile int teller = 0;
const byte debouncetime = 1000;
long morseTeller;
byte stage=0;
boolean ledState = true;

void setup()
{
  c.buffersize = GROOTTE;
  c.count = 0;
  c.beginPos = 0;
  //start the serial
  Serial.begin(9600);

  //LED output
  pinMode(13, OUTPUT);
  //switch input
  pinMode(2, INPUT);

  //set the pull-up on the switch
  digitalWrite(2, HIGH);

  //seed the random number generator
  randomSeed(millis());

  //wait random time from 1 to 3 seconds
  delay(random(1000, 3000));

  //turn the light on


  //attach the interrupt
  attachInterrupt(0, react, CHANGE);

  //get the start time
  start = millis();

  morseTeller=millis();
}

void loop()
{
  if(morseTeller+((c.array[stage])*2)<millis()){
    if(ledState){
      morseTeller+=(c.array[stage])*2;
    } else {
      stage++;
      if(stage==GROOTTE){
        stage=0;
      }
      morseTeller=millis();
    }
    ledState=!ledState;
  }
  digitalWrite(13,ledState);
}

void react()
{
  long fin = millis();
  if (fin - lastButtonPush > 50) {
  if (digitalRead(2) == LOW) {
    teller = millis();
  }
  else {
    teller = millis() - teller;
    appendToBuffer(teller);
    for (int i = 0; i < GROOTTE; i++) {
      Serial.println(c.array[i]);
      if (i == 9) {
      Serial.println("-----------");
      }
    }
  }//}
  //laatsteTijd
  lastButtonPush = fin;
}
}

void appendToBuffer(int getal) {
  if ( c.count < c.buffersize) {
    //als de eerst volgende vrije plaats op een lagere array-positie staat
    if (c.beginPos + c.count >= c. buffersize) {
      c.array[((c.beginPos + c.count) - c.buffersize)] = getal;
      printf("if > if %d\n", getal);
      c.count++;
    }
    //anders dan ^
    else {
      c.array[c.beginPos + c.count] = getal;
      c.count++;
      printf("if > else + %d \n", getal);
    }
  }
  // als de count groter dan de buffersize is
  else {
    printf("else \n");
    c.array[c.beginPos] = getal;
    c.beginPos++;
    if (c.beginPos >= c.buffersize) {
      c.beginPos = 0;
    }
  }
}


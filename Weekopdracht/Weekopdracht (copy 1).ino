
// Simon Baars I1E-n
/*
H: heen, waarbij telkens maar één lamp brandt
 h: heen en weer, waarbij telkens maar één lamp uitgeschakeld is, de rest brandt
 S: samenvoegen, de buitenste 2 lampen branden en vervolgens branden lampen 2 en 7, daarna 3 en 6, als laatste 4 en 5
 s: samenvoegen, de buitenste 2 lampen branden; dan gaan lampen 2 en 7 ook branden, dan 3 en 6 ook, als laatste gaan 4 en 5 aan.
 R: gesloten strook naar rechts, eerst gaat LED 1 branden, dan ook 2, dan ook 3 etc.
 L: gesloten strook naar links, eerst gaat LED 8 branden, dan ook 7, dan ook 6 etc.
 K: knipperen
 A: samenvoegen en daarna weer uit elkaar
 E: stoppen
 */

const int DELAYTIME = 100;
const int NUMBEROFPINS = 8; 
const int NUMBEROFSEQUENCES = 16;
const int NUMBEROFPATTERNS = 9;
const int pinArray[NUMBEROFPINS] = {
  2, 3, 4, 5, 6, 7, 8, 9};
const byte LEDsequence[NUMBEROFPATTERNS][NUMBEROFSEQUENCES][NUMBEROFPINS] = {
  {
{ 0,0,0,0,0,0,0,0}
  },
  {
{ 1,0,0,0,0,0,0,0},
{ 0,1,0,0,0,0,0,0},
{ 0,0,1,0,0,0,0,0},
{ 0,0,0,1,0,0,0,0},
{ 0,0,0,0,1,0,0,0},
{ 0,0,0,0,0,1,0,0},
{ 0,0,0,0,0,0,1,0},
{ 0,0,0,0,0,0,0,1}
  },
  {
{ 1,0,0,0,0,0,0,1},
{ 0,1,0,0,0,0,1,0},
{ 0,0,1,0,0,1,0,0},
{ 0,0,0,1,1,0,0,0},
{ 0,0,0,1,1,0,0,0},
{ 0,0,1,0,0,1,0,0},
{ 0,1,0,0,0,0,1,0},
{ 1,0,0,0,0,0,0,1}
  },
  {
{ 1,1,1,1,1,1,1,1},
{ 0,0,0,0,0,0,0,0}
  },
  {
{ 0,1,1,1,1,1,1,1},
{ 1,0,1,1,1,1,1,1},
{ 1,1,0,1,1,1,1,1},
{ 1,1,1,0,1,1,1,1},
{ 1,1,1,1,0,1,1,1},
{ 1,1,1,1,1,0,1,1},
{ 1,1,1,1,1,1,0,1},
{ 1,1,1,1,1,1,1,0},
{ 1,1,1,1,1,1,1,0},
{ 1,1,1,1,1,1,0,1},
{ 1,1,1,1,1,0,1,1},
{ 1,1,1,1,0,1,1,1},
{ 1,1,1,0,1,1,1,1},
{ 1,1,0,1,1,1,1,1},
{ 1,0,1,1,1,1,1,1},
{ 0,1,1,1,1,1,1,1}
  },
  {
  { 1,0,0,0,0,0,0,1},
{ 0,1,0,0,0,0,1,0},
{ 0,0,1,0,0,1,0,0},
{ 0,0,0,1,1,0,0,0}
  },
  {
  { 0,1,1,1,1,1,1,0},
{ 1,0,1,1,1,1,0,1},
{ 1,1,0,1,1,0,1,1},
{ 1,1,1,0,0,1,1,1}
  },
  {
    { 1,0,0,0,0,0,0,0},
{ 1,1,0,0,0,0,0,0},
{ 1,1,1,0,0,0,0,0},
{ 1,1,1,1,0,0,0,0},
{ 1,1,1,1,1,0,0,0},
{ 1,1,1,1,1,1,0,0},
{ 1,1,1,1,1,1,1,0},
{ 1,1,1,1,1,1,1,1}
  },
  {
  { 1,1,1,1,1,1,1,1},
{ 0,1,1,1,1,1,1,1},
{ 0,0,1,1,1,1,1,1},
{ 0,0,0,1,1,1,1,1},
{ 0,0,0,0,1,1,1,1},
{ 0,0,0,0,0,1,1,1},
{ 0,0,0,0,0,0,1,1},
{ 0,0,0,0,0,0,0,1}
  }
};
int pattern = 0;
int numberofsequences = NUMBEROFSEQUENCES;
int sequence=0;
long beginTijd;

void setup(){
  for (int pin=0;pin<NUMBEROFPINS;pin++) {
    pinMode(pinArray[pin], OUTPUT);     // we make all the declarations at once 
  };
  Serial.begin(9600);
  Serial.println("hi");
  beginTijd=millis();
}

void loop() {
  //for (int sequence=0;sequence<numberofsequences;sequence++) {
    if(millis()>beginTijd+DELAYTIME){
    for (int pin=0;pin<NUMBEROFPINS;pin++) {
      digitalWrite(pinArray[pin], LEDsequence[pattern][sequence][pin]);
    }  
    //delay(DELAYTIME);
    checkMuisDruk();
    bepaalSequenceNum();  
    sequence++;
    beginTijd=millis();
    }
  //}
  if(sequence>numberofsequences){
    sequence=0;
  }
}

void bepaalSequenceNum(){
  if(pattern==1 || pattern==2 || pattern==7 || pattern==8){
    numberofsequences=8;
  } 
  else if(pattern==0){
    numberofsequences=1;
  } 
  else if(pattern==3){
    numberofsequences=2;
  } 
  else if(pattern==4){
    numberofsequences=16;
  } else if (pattern==5 || pattern==6){
    numberofsequences=4;
  }
}

void checkMuisDruk(){
  int incomingByte;
  if (Serial.available() > 0){
      incomingByte = Serial.read();
      if(incomingByte == 'E'){
        pattern=0;
      }
      else if (incomingByte == 'H'){
        pattern = 1;
      }
      else if(incomingByte == 'A'){
        pattern = 2;
      }
      else if (incomingByte == 'K'){
        pattern = 3;
      }else if (incomingByte == 'h'){
        pattern = 4;
      }else if (incomingByte == 'S'){
        pattern = 5;
      }else if (incomingByte == 's'){
        pattern = 6;
      }else if (incomingByte == 'R'){
        pattern = 7;
      }else if (incomingByte == 'L'){
        pattern = 8;
      }
  }
}

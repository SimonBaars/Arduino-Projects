#define AFSTAND afstand
#define WORDTBOOS AFSTAND<8
#define MAAKBOCHT AFSTAND<15
#define GALINKS int(random(2))==0

long afstand;
const int trigPin = 2;

const int echoPin = 4;

//We always have to include the library
#include "LedControlMS.h"

/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 7 is connected to the DataIn 
 pin 6 is connected to the CLK 
 pin 5 is connected to LOAD 
 We have only a single MAX72XX.
 */
#define NBR_MTX 2 
LedControl lc=LedControl(7,6,5, NBR_MTX);

String digits= "1234567890";
int digitCounter=0;
/* we always wait a bit between updates of the display */
unsigned long delaytime=300;


boolean isBlij = true;
long boosTimer;
long bochtTimer;

boolean bochtLinks = true;


void setup() {
  initRobot();
}

void bepaalAfstand(){
 afstand = microsecondsToCentimeters(pulseIn(echoPin, HIGH));
} 

void rijVooruit(){
  //Motor A forward @ full speed
  digitalWrite(12, HIGH); //Establishes forward direction of Channel A
  digitalWrite(9, LOW);   //Disengage the Brake for Channel A
  analogWrite(3, 150);   //Spins the motor on Channel A at full speed
  
  //Motor B forward @ full speed
  digitalWrite(13, HIGH); //Establishes forward direction of Channel B
  digitalWrite(8, LOW);   //Disengage the Brake for Channel B
  analogWrite(11, 110);   //Spins the motor on Channel B at full speed
      Serial.println("Gaat naar voren");
   
}

void bocht(boolean links){
  if(links){
    //Bocht naar links
  //Motor A forward @ full speed
  digitalWrite(12, LOW); //Establishes forward direction of Channel A
  digitalWrite(9, LOW);   //Disengage the Brake for Channel A
  analogWrite(3, 160);   //Spins the motor on Channel A at full speed
  
  //Motor B forward @ full speed
  //digitalWrite(13, HIGH); //Establishes forward direction of Channel B
  //digitalWrite(8, LOW);   //Disengage the Brake for Channel B
  //analogWrite(11, 200);   //Spins the motor on Channel B at full speed
      Serial.println("Kiest links");
 
  } else {

  
  //Motor B forward @ full speed
  digitalWrite(13, LOW); //Establishes forward direction of Channel B
  digitalWrite(8, LOW);   //Disengage the Brake for Channel B
  analogWrite(11, 70);   //Laatste getal geeft de snelheid weer, maximaal 255
      Serial.println("Kiest rechts");

  }
}

void loop()
{
  initAfstand();
  bepaalAfstand();
  
  if(millis()<bochtTimer){
    bocht(bochtLinks);
  } else {
    rijVooruit();
  }
  
   
  boolean wordtBoos = WORDTBOOS;
  Serial.println(wordtBoos);
  
  if (isBlij && wordtBoos){  
  Serial.println("trigger1");
    maakBoos();
    isBlij=false;
    boosTimer=millis()+2000;
  }
  else if(!isBlij && !wordtBoos && millis()>boosTimer){
    Serial.println("trigger2");
    maakBlij();
    isBlij=true;
  }
  
  
  if(MAAKBOCHT && millis()>bochtTimer){
    if(GALINKS){
      bochtLinks=true;
    } else {
      bochtLinks=false;
    }
    bochtTimer=millis()+1000;
  }
  
}



void maakBlij(){
   for (int i=0; i< NBR_MTX; i++){
      lc.clearDisplay(i);
   }
   

    lc.setLed(0,1,2,true);
    lc.setLed(0,2,1,true);
    lc.setLed(0,3,1,true);
    lc.setLed(0,4,1,true);
    lc.setLed(0,6,2,true);
    lc.setLed(0,5,1,true);
    lc.setLed(0,2,5,true);
    lc.setLed(0,2,6,true);
    lc.setLed(0,5,5,true);
    lc.setLed(0,5,6,true);       
}

void maakBoos(){
  for (int i=0; i< NBR_MTX; i++){
      lc.clearDisplay(i);
   }
   
    lc.setLed(0,1,1,true);
    lc.setLed(0,2,2,true);
    lc.setLed(0,3,2,true); 
    lc.setLed(0,4,2,true);
    lc.setLed(0,5,2,true);
    lc.setLed(0,6,1,true);
    lc.setLed(0,2,6,true);
    lc.setLed(0,2,5,true);
    lc.setLed(0,5,5,true); 
    lc.setLed(0,5,6,true);   
    //clearAll();
}

//long microsecondsToInches(long microseconds)

//{
//  return microseconds / 74 / 2;

//}

long microsecondsToCentimeters(long microseconds)

{
  return microseconds / 29 / 2;
}


#define AFSTAND afstand
#define WORDTBOOS AFSTAND<6
#define NAARVOREN AFSTAND>10

long afstand;

const int trigPin = 2;

const int echoPin = 4;

//We always have to include the library
#include "LedControlMS.h"

/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn 
 pin 11 is connected to the CLK 
 pin 10 is connected to LOAD 
 We have only a single MAX72XX.
 */
#define NBR_MTX 2 
LedControl lc=LedControl(12,11,10, NBR_MTX);

String digits= "1234567890";
int digitCounter=0;
/* we always wait a bit between updates of the display */
unsigned long delaytime=300;


boolean isBlij = true;
boolean nietBocht = true;
long boosTimer;
long randNumber;

void bepaalAfstand(){
  afstand = microsecondsToCentimeters(pulseIn(echoPin, HIGH));
}

void setup() {
  
  //begin code servo
  //Setup Channel A
  pinMode(12, OUTPUT); //Initiates Motor Channel A pin
  pinMode(9, OUTPUT); //Initiates Brake Channel A pin

  //Setup Channel B
  pinMode(13, OUTPUT); //Initiates Motor Channel A pin
  pinMode(8, OUTPUT);  //Initiates Brake Channel A pin
  //einde code servo
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */


  Serial.begin (9600);
  
   
  digitCounter=0;
  initLedmatrix();
  maakBlij();
  randomSeed(analogRead(0));
  randNumber = random(1, 3);


}

void loop(){
  
  long duration, cm;
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  bepaalAfstand(); 
  
  
  
if (!NAARVOREN && nietBocht) {
  nietBocht=false;
}
else {
  nietBocht=true;
} 

//code servo rustig naar voren rijden
 if (NAARVOREN && nietBocht) {
  //Motor A forward @ full speed
  digitalWrite(12, HIGH); //Establishes forward direction of Channel A
  digitalWrite(9, LOW);   //Disengage the Brake for Channel A
  analogWrite(3, 150);   //Spins the motor on Channel A at full speed
  //Motor B forward @ full speed
  digitalWrite(13, HIGH); //Establishes forward direction of Channel B
  digitalWrite(8, LOW);   //Disengage the Brake for Channel B
  analogWrite(11, 150);   //Spins the motor on Channel B at full speed
  //Motor B backward @ half speed
  //digitalWrite(13, LOW);  //Establishes backward direction of Channel B
  //digitalWrite(8, LOW);   //Disengage the Brake for Channel B
  //analogWrite(11, 123);    //Spins the motor on Channel B at half speed
  Serial.print("Gaatnaarvoren");
 }
  
  else if (!nietBocht) {  
     Serial.print("bocht");
    if (randNumber==1) {
      //bocht naar links
        //Motor A forward @ full speed
  digitalWrite(12, HIGH); //Establishes forward direction of Channel A
  digitalWrite(9, LOW);   //Disengage the Brake for Channel A
  analogWrite(3, 50);   //Spins the motor on Channel A at full speed
  //Motor B forward @ full speed
  digitalWrite(13, HIGH); //Establishes forward direction of Channel B
  digitalWrite(8, LOW);   //Disengage the Brake for Channel B
  analogWrite(11, 75);   //Spins the motor on Channel B at full speed
    }
  else if (randNumber==2) {
    //bocht naar rechts
      //Motor A forward @ full speed
  digitalWrite(12, HIGH); //Establishes forward direction of Channel A
  digitalWrite(9, LOW);   //Disengage the Brake for Channel A
  analogWrite(3, 75);   //Spins the motor on Channel A at full speed
  //Motor B forward @ full speed
  digitalWrite(13, HIGH); //Establishes forward direction of Channel B
  digitalWrite(8, LOW);   //Disengage the Brake for Channel B
  analogWrite(11, 50);   //Spins the motor on Channel B at full speed
  }
  }
  //digitalWrite(9, HIGH);  //Engage the Brake for Channel A
  //digitalWrite(9, HIGH);  //Engage the Brake for Channel B



  
  //Motor A forward @ full speed
 // digitalWrite(12, LOW);  //Establishes backward direction of Channel A
  //digitalWrite(9, LOW);   //Disengage the Brake for Channel A
  //analogWrite(3, 123);    //Spins the motor on Channel A at half speed
  
  //Motor B backward @ half speed
  //digitalWrite(13, LOW);  //Establishes backward direction of Channel B
  //digitalWrite(8, LOW);   //Disengage the Brake for Channel B
  //analogWrite(11, 123);    //Spins the motor on Channel B at half speed

  
  

  
  
  digitalWrite(9, HIGH);  //Engage the Brake for Channel A
  digitalWrite(9, HIGH);  //Engage the Brake for Channel B
  
//einde code servo rustig naar voren rijden
  

  boolean wordtBoos = WORDTBOOS;
  Serial.println(wordtBoos);
  if (isBlij && wordtBoos){  // hij begon op cm =  0 daarom kan dit niet waarschijnlijk
  Serial.println("triogger1");
    maakBoos();
    isBlij=false;
    boosTimer=millis()+2000;
  }
  else if(!isBlij && !wordtBoos && millis()>boosTimer){
    Serial.println("triogger2");
    maakBlij();
    isBlij=true;
    
  }
}
//ctrl shift m


void initLedmatrix(){
  for (int i=0; i< NBR_MTX; i++){
    lc.shutdown(i,false);
    /* Set the brightness to a medium values */
    lc.setIntensity(i,8);
    /* and clear the display */
    lc.clearDisplay(i);
  }
}

void maakBlij(){
   for (int i=0; i< NBR_MTX; i++){
      lc.clearDisplay(i);
   }
   
  //Serial.println("LED0: 1 1");
    lc.setLed(0,1,2,true);
    //Serial.println("LED0: 2 2");
    lc.setLed(0,2,1,true);
    //Serial.println("LED0: 3 2");
    lc.setLed(0,3,1,true);
    //Serial.println("LED0: 4 2");  
    lc.setLed(0,4,1,true);
    //Serial.println("LED0: 5 2");
    lc.setLed(0,6,2,true);
    //Serial.println("LED0: 6 1");
    lc.setLed(0,5,1,true);
    //Serial.println("LED0: 2 5");
    lc.setLed(0,2,5,true);
    //Serial.println("LED0: 2 6");  
    lc.setLed(0,2,6,true);
    //Serial.println("LED0: 5 5");
    lc.setLed(0,5,5,true);
    //Serial.println("LED0: 5 6");  //Getal van de positie van de led opschrijven achter LED0: (Posities zitten in het mapje)
    lc.setLed(0,5,6,true);        // Getal tussen de haakjes na de 0 zetten 
}

void maakBoos(){
  for (int i=0; i< NBR_MTX; i++){
      lc.clearDisplay(i);
   }
   
  //Serial.println("LED0: 1 2");
    lc.setLed(0,1,1,true);
    //Serial.println("LED0: 2 1");
    lc.setLed(0,2,2,true);
    //Serial.println("LED0: 3 1");
    lc.setLed(0,3,2,true);
   // Serial.println("LED0: 4 1");  
    lc.setLed(0,4,2,true);
    //Serial.println("LED0: 6 2");
    lc.setLed(0,5,2,true);
   // Serial.println("LED0: 5 1");
    lc.setLed(0,6,1,true);
   // Serial.println("LED0: 2 6");  
    lc.setLed(0,2,6,true);
    // Serial.println("LED0: 2 6");  
    lc.setLed(0,2,5,true);
   // Serial.println("LED0: 5 5");
    lc.setLed(0,5,5,true);
   // Serial.println("LED0: 5 6");  //Getal van de positie van de led opschrijven achter LED0: (Posities zitten in het mapje)
    lc.setLed(0,5,6,true);   
    //clearAll();
}

long microsecondsToInches(long microseconds)

{
  return microseconds / 74 / 2;

}

long microsecondsToCentimeters(long microseconds)

{
  return microseconds / 29 / 2;
}


/*
  Blink
 Turns on an LED on for one second, then off for one second, repeatedly.
 
 Most Arduinos have an on-board LED you can control. On the Uno and
 Leonardo, it is attached to digital pin 13. If you're unsure what
 pin the on-board LED is connected to on your Arduino model, check
 the documentation at http://arduino.cc
 
 This example code is in the public domain.
 
 modified 8 May 2014
 by Scott Fitzgerald
 */

int delaytijd = 200;
boolean heenenweer=false;
int i = 2;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.S
  for(int i = 0; i<=13; i++){
  pinMode(i, OUTPUT);
  }
}

// the loop function runs over and over again forever
void loop() {
  if(heenenweer==true) zetLampjeUit(i+1);
  if(heenenweer==false) zetLampjeUit(i-1);
  if(i==9) heenenweer=true;
  if(i==2) heenenweer=false;
  zetLampjeAan(i);
  if(heenenweer==true) i=i-1;
  if(heenenweer==false) i=i+1;
  delay(delaytijd);
  
}

void zetLampjeAan(int poort){
  digitalWrite(poort, HIGH);
}

void zetLampjeUit(int poort){
  digitalWrite(poort, LOW); 
}

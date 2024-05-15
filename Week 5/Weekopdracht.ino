/*************************************************** 
Deze praaaaaaachtige uitwerking is gemaakt door de enige echte Simon Baars (All Rights Reserved)

Speciale dank aan Oguz, Kris en Thomas om mij te kalmeren als ik mijn vuist bijna door het scherm van mijn laptop heen liet gaan.

Klas: I1E-n
Auteur: Simon Baars
****************************************************/

#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

String voerIn = "Voer iets in...";
unsigned const arrayLength=50;
char inData[arrayLength+1]; //Ik ben van plan eerst een array van characters te maken van alles wat wordt ingetypt in de Serial (ik ben er namelijk achter gekomen dat de Serial er anders hele rare dingen van maakt)
char inChar; 
byte index=0;
boolean isNietLeeggemaakt = false;
boolean moetNogPrinten = false;
int knopPins[] = {
  2,3};
boolean richting=false;

void setup() {
  Serial.begin(9600);
  Serial.println("8x8 LED Matrix Test");

  for(int i=knopPins[0]; i<=knopPins[1]; i++){
    pinMode(knopPins[i], INPUT); 
  }

  matrix.begin(0x71);  // pass in the address
}

void loop(){
  for(int i=2; i<=3;i++){
  checkLeds(i);
  }
  while(Serial.available() > 0)//Hoeveel characters er ingetypt zijn
  {
    delay(10); //Deze delay blijkt belangrijk te zijn!! Anders leest die niet alles in een keer (rare arduino).
    if(isNietLeeggemaakt){
      maakLeeg();
      isNietLeeggemaakt=false;
    }

    if(index < (arrayLength-1)) //Sorry voor alle getallen in de code: heb nog geen tijd gehad om het op te ruimen
    {
      inChar = Serial.read(); 
      inData[index] = inChar; 
      index++; 
      inData[index] = '\0'; //Als ik dit niet doe gaat het programma rare tekens aan de array toevoegen. Vandaar /0 op de index 1 na de zojuist ingevoegde!!
      moetNogPrinten=true;
    }

  }

  if(Serial.available() == 0){
    isNietLeeggemaakt=true;
    if(moetNogPrinten){
      //memcpy(voerIn, inData, 20);
      voerIn=String(inData);
      Serial.print(voerIn);
      Serial.println(" aan het printen...");
      printTekst();
      moetNogPrinten=false;
    }
  }
}

void maakLeeg(){
  for(int i = 0; i<(arrayLength+1); i++){
    inData[i]=' ';
  }
  index=0;
}

void printTekst() {
  matrix.clear(); 
  if(richting){
    matrix.setRotation(1);
  } 
  else {
    matrix.setRotation(2);
  }
  matrix.setTextSize(1);
  matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
  matrix.setTextColor(LED_ON);
  for (int8_t x=7; x>=-(8*getArrayLength(inData)); x--) {
    matrix.clear();
    matrix.setCursor(x,0);
    matrix.print(voerIn);
    matrix.writeDisplay();
    delay(50);
  }
}

int getArrayLength(char array[]){
  for(int i = 7; i<=arrayLength; i++){
    if(array[i] == ' '){
      return i;
    }
  }
  return 0;
}

/*void checkLeds(){
  for (int k =2; k<=3; k++){
    //int i = k;
    int buttonState = digitalRead(knopPins[3]);
    if (buttonState == LOW) {        
      if(k==3 && !richting){
        richting=true;
        Serial.println("De richting is nu naar rechts!!");
      }
    } 
    else if(buttonState==HIGH) {
      if(k==2 && richting){
        richting=false;
        Serial.println("De richting is nu naar boven!!");
      } 
    }
  }
}*/

void checkLeds(int poort){
  //for(int i = 0; i<8; i++){
    int buttonState = digitalRead(poort);
  if (buttonState == HIGH) {     
    
  }
  else {
   if(poort==2 && richting){
        richting=false;
        Serial.println("De richting is nu naar rechts!!");
      } else if(poort==3 && !richting){
        richting=true;
        Serial.println("De richting is nu naar boven!!");
      }
  }
  //}
}



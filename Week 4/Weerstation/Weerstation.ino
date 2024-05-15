#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

void setup() {
  // open the serial connection at 
  // 9600 BAUD
  Serial.begin(9600); 
  matrix.begin(0x70);  // pass in the address

  // initialize the LED pin as an output:
  for(int i = 2; i<=9; i++){
    pinMode(i, OUTPUT);    
  }  
  // initialize the pushbutton pin as an input:
  for(int i=10; i<=13; i++){
    pinMode(i, INPUT); 
  }
}


void loop() {
  // store the value read from pin 2
  // into a variable
  int draaiKnop = analogRead(0);
  int licht = analogRead(1);
  int temperatuur = analogRead(2);
  Serial.print("De wind waait met een kracht van ");
  Serial.print(draaiKnop);
  Serial.print(", er is een lichtintensiteit van ");
  Serial.print(licht);
  Serial.print(" en er is een warmte van ");
  Serial.print(temperatuur);
  Serial.println(" graden celcius");
  // print that variable over the serial connection
  weerstationVisuals();
  checkLeds();
}

void weerstationVisuals(){
  matrix.clear();
  matrix.setRotation(2);
  matrix.setTextSize(1);
  matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
  matrix.setTextColor(LED_ON);
  for (int8_t x=0; x>=-80; x--) {
    matrix.clear();
    matrix.setCursor(x,0);
    matrix.print("  Weerstation  ");
    matrix.writeDisplay();
    delay(50);
  }
}

void checkLeds(){
  for(int i = 0; i<8; i++){
    int ledPin=i+2;
    int buttonPin=int(i/2)+10;
    int buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {     
    // turn LED on:    
    digitalWrite(ledPin, HIGH);  
  } 
  else {
    // turn LED off:
    digitalWrite(ledPin, LOW); 
  }
  }
}


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
boolean running = tr;

#define NBR_MTX 2 
LedControl lc=LedControl(12,11,10, NBR_MTX);

String digits= "1234567890";
int digitCounter=0;
/* we always wait a bit between updates of the display */
unsigned long delaytime=300;


void setup() {
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  Serial.begin (9600);
  Serial.println("Setup");
  digitCounter=0;
  for (int i=0; i< NBR_MTX; i++){
    lc.shutdown(i,false);
  /* Set the brightness to a medium values */
    lc.setIntensity(i,8);
  /* and clear the display */
    lc.clearDisplay(i);
  }
  //clearAll();
}


void loop() { 
 if (boolean running = true){
  Serial.println("LED0: 1 2");
  lc.setLed(0,1,2,true);
  Serial.println("LED0: 2 1");
  lc.setLed(0,2,1,true);
  Serial.println("LED0: 3 1");
  lc.setLed(0,3,1,true);
  Serial.println("LED0: 4 1");  
  lc.setLed(0,4,1,true);
  Serial.println("LED0: 6 2");
  lc.setLed(0,6,2,true);
  Serial.println("LED0: 5 1");
  lc.setLed(0,5,1,true);
  Serial.println("LED0: 2 5");
  lc.setLed(0,2,5,true);
  Serial.println("LED0: 2 6");  
  lc.setLed(0,2,6,true);
  Serial.println("LED0: 5 5");
  lc.setLed(0,5,5,true);
  Serial.println("LED0: 5 6");  //Getal van de positie van de led opschrijven achter LED0: (Posities zitten in het mapje)
  lc.setLed(0,5,6,true);        // Getal tussen de haakjes na de 0 zetten 
 }
if (boolean running = false){
 Serial.println("LED0: 1 0");
  lc.setLed(0,1,0,true);
  Serial.println("LED0: 2 1");
  lc.setLed(0,2,1,true);
  Serial.println("LED0: 3 1");
  lc.setLed(0,3,1,true);
  Serial.println("LED0: 4 1");  
  lc.setLed(0,4,1,true);
  Serial.println("LED0: 6 2");
  lc.setLed(0,6,2,true);
  Serial.println("LED0: 5 1");
  lc.setLed(0,5,1,true);
  Serial.println("LED0: 2 5");
  lc.setLed(0,2,5,true);
  Serial.println("LED0: 2 6");  
  lc.setLed(0,2,6,true);
  Serial.println("LED0: 5 5");
  lc.setLed(0,5,5,true);
  Serial.println("LED0: 5 6");  //Getal van de positie van de led opschrijven achter LED0: (Posities zitten in het mapje)
  lc.setLed(0,5,6,true);    
}
}

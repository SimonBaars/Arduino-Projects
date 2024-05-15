//PAS OP: servos have three wires: power, ground, and signal. The power wire is typically red, and should be connected to the 5V pin on the Arduino board. The ground wire is typically black or brown and should be connected to a ground pin on the Arduino board. The signal pin is typically yellow, orange or white and should be connected to an output pin on the Arduino board.

//Probeer nu deze sketch uit:

#include <Servo.h>
 const int poort = 3;
const int delayTijd = 100;
boolean lampjeBrandt=false;
long beginTijd;
Servo servo;
 
void setup() {
  servo.attach(9);
   Serial.begin(9600); 
   pinMode(13, OUTPUT);
  beginTijd=millis();
  
}
 
void loop() {
 int draaiKnop = analogRead(0);
    servo.write(draaiKnop/(1023/150));
    laatLampjeKnipperen();
    Serial.print("De wind waait met een kracht van ");
  Serial.println(draaiKnop);
}

void laatLampjeKnipperen(){
  if(millis()>beginTijd+delayTijd){
    if(lampjeBrandt){
      analogWrite(poort, 20);
    }else{
        analogWrite(poort, 0);
    }
    lampjeBrandt=!lampjeBrandt;
    beginTijd=millis();
  }
}

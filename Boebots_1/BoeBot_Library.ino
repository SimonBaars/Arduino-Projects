/*
 * This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
 
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
 
    For more information of the licensing of this program, see 
    <http://www.gnu.org/licenses/>.

    This program has been written by Simon Baars from the HAN
    Hogeschool. All rights reserved.
 */
 
 #include <NewPing.h>
#include <Servo.h>
#define LEFT 0
#define RIGHT 1
Servo servoRight;
Servo servoLeft;
#define NIKS 0
#define BEWEEGNAARVOREN 1
#define DRAAILINKS 2
#define DRAAIRECHTS 3
#define BEWEEGNAARACHTEREN 4
#define STASTIL 5
#define OBJECTCLOSE 250
#define NCLOSE 20

#define TRIGGER_PIN 1
#define ECHO_PIN 4

NewPing sonar(TRIGGER_PIN, ECHO_PIN, 200);

char knop;
byte counter=1;
byte afstandTeller=0;
float distance;
float prevDistance;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  servoRight.attach(12);
  servoLeft.attach(11);
  //pinMode(trigPin, OUTPUT);
 //pinMode(echoPin, INPUT);
  pinMode(2, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), checkRise, RISING);
  attachInterrupt(digitalPinToInterrupt(2), checkFalling, FALLING);
  Serial.println("BoeBot Library door Simon Baars gestart");
  delay(100);
}

void loop(){
  //noInterrupts();
  prevDistance=distance;
  knop = getPressedButton();
  distance=sonar.ping();
  initDistance();
  Serial.println();
  //interrupts();
  voerHerhaaldelijkUit();
}

int teller(){
  return counter;
}

void telOp(){
  counter++;
}

char ingedrukteKnop(){
  return knop;
}

void controlMotor(int motorSpeed, boolean motorSide) {
  if (motorSide == LEFT) {
    servoLeft.writeMicroseconds(1500 + motorSpeed);
  } else {
    servoRight.writeMicroseconds(1500 - motorSpeed);
  }
}

void draaiRechts(int degrees) {
  controlMotor(-135, RIGHT);
  controlMotor(135, LEFT);
  delay(degrees * 11);
}

void draaiLinks(int degrees) {
  controlMotor(135, RIGHT);
  controlMotor(-135, LEFT);
  delay(degrees * 11);
}

void beweegNaarVoren(float time) {
  controlMotor(135, RIGHT);
  controlMotor(135, LEFT);
  delay(time * 1000);
}

void beweegNaarAchteren(float time) {
  controlMotor(-135, RIGHT);
  controlMotor(-135, LEFT);
  delay(time * 1000);
}

void draaiRechts(int degrees, float speed) {
  controlMotor(-(speed/100)*135, RIGHT);
  controlMotor((speed/100)*135, LEFT);
  delay(degrees * 11);
}

void draaiLinks(int degrees, float speed) {
  controlMotor((speed/100)*135, RIGHT);
  controlMotor(-(speed/100)*135, LEFT);
  delay(degrees * 11);
}

void beweegNaarVoren(float time, float speed) {
  controlMotor((speed/100)*135, RIGHT);
  controlMotor((speed/100)*135, LEFT);
  delay(time * 1000);
}

void beweegNaarAchteren(float time, float speed) {
  controlMotor(-(speed/100)*135, RIGHT);
  controlMotor(-(speed/100)*135, LEFT);
  delay(time * 1000);
}

void draaiRechts() {
  controlMotor(-135, RIGHT);
  controlMotor(135, LEFT);
}

void draaiLinks() {
  controlMotor(135, RIGHT);
  controlMotor(-135, LEFT);
}

void beweegNaarVoren() {
  controlMotor(135, RIGHT);
  controlMotor(135, LEFT);
}

void beweegNaarAchteren() {
  controlMotor(-135, RIGHT);
  controlMotor(-135, LEFT);
}

void staStil() {
  controlMotor(0, RIGHT);
  controlMotor(0, LEFT);
}

void staStil(float time) {
  controlMotor(0, RIGHT);
  controlMotor(0, LEFT);
  delay(time * 1000);
}

boolean gaatObjectRaken() {
  return afstandTeller>NCLOSE;
}

boolean gaatObjectRaken(float seconds) {
  long milli=millis();
  while(millis()<milli+(seconds*1000)){
    if(distance <= OBJECTCLOSE && distance!=0){
    return true;
    }
  }
  return false;
}

float afstand(){
  return distance;
}

float getDistance() {
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
/*  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  return microsecondsToCentimeters(pulseIn(echoPin, HIGH));*/
  return sonar.ping();
}

void initDistance(){
  if(distance <= OBJECTCLOSE && distance>0){
    afstandTeller++;
  } else {
    afstandTeller=0;
  }
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}


boolean knopGedrukt() {
  return !digitalRead(2);
}

boolean knopGedrukt(float seconds) {
  long milli=millis();
  while(millis()<milli+(seconds*1000)){
    if(digitalRead(2)){
    return true;
    }
  }
  return false;
}

boolean closeOff = false;
int positie = 0;
unsigned long currentMicros;
int pulsen[34];
bool hasPulse = false;
bool doesDoStuff = false;

const bool knopWaardes[][34] = {
  {0,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,1,1,0,0,0,1,1,1,0,0,1,1,1}, //2
  {0,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,1,0,0,0,0,1,1,1,0,1,1,1,1}, //4
  {1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,1,0,1,1,0,1,0,1,0,1,0,0,1,0,1}, //6
  {0,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,1,0,0,1,0,1,0,1,0,1,1,0,1,0,1}, //8
  {0,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,1,1,0,0,0,0,1,1,0,0,1,1,1,1}, //1
  {1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,1,1,1,1,0,1,0,1,0,0,0,0,1,0,1}, //3
  {1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,1,1,1,0,0,0,1,1,0,0,0,1,1,1}, //5
  {1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,1,0,0,0,0,1,0,1,0,1,1,1,1,0,1}, //7
  {0,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,1,0,1,0,0,1,0,1,0,1,0,1,1,0,1}, //9
  {1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,1,0,0,0,1,0,0,1,0,1,1,1,0,1}, //CH-
  {1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,1,1,0,0,0,1,0,1,0,0,1,1,1,0,1}, //CH
  {1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,0,0,0,0,1,1,1,0,1}, //CH+
  {0,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,1,0,0,0,1,0,1,1,0,1,1,1,0,1}, //PREV
  {0,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,0,1,1,1,1,1,1,0,1}, //NEXT
  {0,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,0,0,0,1,1,1,1,0,1}, //PLAY/PAUSE
  {0,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1}, //VOL-
  {0,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,1,0,1,0,0,0,0,1,0,1,0,1,1,1}, //VOL+
  {0,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,1,0,0,0,0,0,1,1,0,1,1,1,1}, //EQ
  {0,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,1,1,0,1,0,0,0,1,0,0,1,0,1,1,1}, //0
  {0,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,1,1,0,0,0,0,1,1,0,0,1,1,1}, //100+
  {0,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,1,1,0,0,0,0,0,1,0,0,1,1,1,1} //200+
};

const char knopLetters[] = {'2','4','6','8','1','3','5','7','9','A','B','C','D','E','F','G','H','I','0', 'K', 'L'};

const byte nKnoppen = 21;

void checkRise() {
  pulsen[positie] = micros() - currentMicros;
  currentMicros = micros();
  positie++;
}

void checkFalling() {
  pulsen[positie] = micros() - currentMicros;
  hasPulse = true;
  currentMicros = micros();
  positie++;
}

char wachtOpKnop(float seconds) {
  long milli=millis();
  while(millis()<milli+(seconds*1000)){
    if(ingedrukteKnop()!=' '){
      return knop;
    }
  }
  return ' ';
}

char wachtOpKnop() {
  while(true){
    if(ingedrukteKnop()!=' '){
      return knop;
    }
  }
  return ' ';
}

char getPressedButton() {
  if (hasPulse && currentMicros + 100000 < micros() && positie > 33) {
    positie = 0;
    hasPulse = false;
    boolean hasBroken;
    for (int j = 0; j < nKnoppen; j++) {
      hasBroken=false;
      for (int i = 18; i < 33; i++) {
        if (knopWaardes[j][i] != (pulsen[i] > 1500)) {
          hasBroken=true;
          break;
        }
      }
      if(hasBroken){
        continue;
      }
      return knopLetters[j];
    }
    return 'Z';
  }
  return ' ';
}


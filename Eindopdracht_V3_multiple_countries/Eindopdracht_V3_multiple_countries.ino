// ESD eindopdracht 2014-2015

//Pin verdeling
//Lampjes rechterkant
const int LedGroenRechts = 8; 
const int LedGeelRechts = 7; 
const int LedRoodRechts = 6; 
//Lampjes linkerkant
const int LedRoodLinks = 5; 
const int LedGeelLinks = 4; 
const int LedGroenLinks = 3;
//Knoppen
const int ButtonRechts = 13;
const int ButtonMidden = 12;
const int ButtonLinks = 11;
//Geluid
const int Geluid = 10;
//Hefboom
const int HefboomPin = 9;

#include <Servo.h>
#include <Wire.h>

Servo hefboom;
int Matrix_Verkeerslicht = 0x70;

//een partij per keer
boolean Ontruimen[3] = {
  false, false, false  };
boolean LichtGroenRechts = false;
boolean LichtGroenLinks = false;
boolean MatrixStart = false;

//Timers
const int IntervalEenSec = 1000;
unsigned long MatrixPreviousMillis;
unsigned long VKLPreviousMillis;
int MatrixNummer;
int VKLNummer;
int VerkeerslichtRechtsMillis;
int VerkeerslichtLinksMillis;

int ButtonStateLinks = 0;
int ButtonStateMidden = 0;
int ButtonStateRechts = 0;

boolean Buzz = true;

int Land = 3; 
/*
Nederland = 1
Duitsland = 2
Oostenrijk = 3
*/

void setup(){
  PinInstellen();

  Serial.begin(9600);

  hefboom.attach(HefboomPin);
}

void loop(){
  CheckButtons();
  StandaardSituatie();
  Verkeerslichten();
  AftelTikken();
  Buzzer(Buzz);
  MatrixKlok();
  VKLKlok();
}

void PinInstellen(){
  pinMode(LedGroenRechts, OUTPUT);
  pinMode(LedGeelRechts, OUTPUT);
  pinMode(LedRoodRechts, OUTPUT);
  pinMode(LedGroenLinks, OUTPUT);
  pinMode(LedGeelLinks, OUTPUT);
  pinMode(LedRoodLinks, OUTPUT);
  pinMode(Geluid,OUTPUT);
  pinMode(ButtonRechts, INPUT);
  pinMode(ButtonMidden, INPUT);
  pinMode(ButtonLinks, INPUT);
}

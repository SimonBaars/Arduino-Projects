// ESD eindopdracht 2014-2015

//Pin verdeling
//Lampjes rechterkant
const int LedGroenRechts = 7; 
const int LedGeelRechts = 6; 
const int LedRoodRechts = 5; 
//Lampjes linkerkant
const int LedRoodLinks = 4; 
const int LedGeelLinks = 3; 
const int LedGroenLinks = 2;
//Knoppen
const int ButtonRechts = 13;
const int ButtonMidden = 12;
const int ButtonLinks = 11;
const int ButtonAlles = 10;
//Geluid
const int Geluid = 8;
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
boolean AllesStart = false;

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
int ButtonStateAlles = 0;

boolean Buzz = true;
byte Tikker = 0;

void setup(){
  PinInstellen();

  Serial.begin(9600);

  hefboom.attach(HefboomPin);
}

void loop(){
  CheckButtons();
  StandaardSituatie();
  Verkeerslichten();
  TikStand(Tikker);
  Buzzer(Buzz);
  MatrixKlok();
  VKLKlok();
  AllesAanKnop();
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
  pinMode(ButtonAlles,INPUT);
}

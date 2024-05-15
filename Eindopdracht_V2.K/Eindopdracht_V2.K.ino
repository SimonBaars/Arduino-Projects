//Global Variables
const int LedGroenRechts = 8; 
const  int LedGeelRechts = 7; 
const int LedRoodRechts = 6; //Lampjes Rechterkant
const int LedRoodLinks = 5; 
const int LedGeelLinks = 4; 
const int LedGroenLinks = 3; //Lampjes Linkerkant
const int ButtonRechts = 13;
const int ButtonMidden = 12;
const int ButtonLinks = 11;
const int Geluid = 10;

boolean AftellenGeweest[7] = {
  false,false,false,false,false,false,false};

boolean Ontruimen[3] = {
  false, false, false  };
  
#include <Servo.h>
#include <Wire.h>
Servo hefboom;
int Matrix_Verkeerslicht = 0x70;

int VerkeerslichtRechtsMillis;
int VerkeerslichtLinksMillis;

boolean LichtGroenRechts = false;
boolean LichtGroenLinks = false;
boolean MatrixStart = false;

boolean StoplichtKleur[2][3];

const int IntervalEenSec = 1000;
unsigned long MatrixPreviousMillis;
unsigned long VKLPreviousMillis;
int MatrixNummer;
int VKLNummer;

int ButtonStateLinks = 0;
int ButtonStateMidden = 0;
int ButtonStateRechts = 0;

boolean Buzz = true;

void setup(){
  PinInstellen();

  Serial.begin(9600);

  hefboom.attach(9);
  int i;
  for (i = 0; i < 3; i = i+ 1){
    StoplichtKleur[0][i] = false;
    StoplichtKleur[1][i] = false;


  }
}

void loop(){
  CheckButtons();
  StandaardSituatie();
  Verkeerslichten();
  AftelTikken();
  Buzzer(Buzz);  //use at own risk
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





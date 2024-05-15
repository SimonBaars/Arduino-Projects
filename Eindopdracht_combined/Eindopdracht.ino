//Global Variables
 const int LedGroenRechts = 9; const  int LedGeelRechts = 8; const int LedRoodRechts = 7; //Lampjes Rechterkant
 const int LedRoodLinks = 6; const int LedGeelLinks = 5; const int LedGroenLinks = 4; //Lampjes Linkerkant
 const int ButtonRechts = 13;
 const int ButtonMidden = 12;
 const int ButtonLinks = 11;
 const int Geluid = 10;
 
 boolean AftellenGeweest[7] = {false,false,false,false,false,false,false};
 
 #include <Wire.h>
 int Matrix_Verkeerslicht = 0x70;
 
 int VerkeerslichtRechtsMillis;
 int VerkeerslichtLinksMillis;
 
 boolean LichtGroenRechts = false;
 boolean LichtGroenLinks = false;
 boolean MatrixStart = false;
 
boolean StoplichtKleur[2][3];

unsigned long PreviousMatrixMillis;
long MatrixInterval = 1000;

int ButtonStateLinks = 0;
int ButtonStateMidden = 0;
int ButtonStateRechts = 0;

unsigned long MatrixMillis = millis();

int WelkNummerMatrix;

void setup(){
PinInstellen();
 
 Serial.begin(9600);
 
 int i;
 for (i = 0; i < 3; i = i+ 1){
   StoplichtKleur[0][i] = false;
   StoplichtKleur[1][i] = false;
   
   
 }
}

void loop(){
CheckButtons();
VerkeerslichtRechts();
VerkeerslichtLinks();
//GeluidOversteek();  //use at own risk

if (MatrixStart == true){
  WelkNummerMatrix = 0;
  Aftellen();
}
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

//10% van de credits gaan naar Sebastiaan

int aantalLeds = 8;
int startGetal=2;
int eventStatus=0;
void setup(){
  setupAllLeds();
  Serial.begin(9600);
}

void loop(){
  event1();
  event2();
  checkLetter();
}

void checkLetter(){
  byte input = Serial.read();
  if(input == 'H'){
    eventStatus=1;
  } 
  else if (input== 'S'){
    eventStatus=2;
  }
}




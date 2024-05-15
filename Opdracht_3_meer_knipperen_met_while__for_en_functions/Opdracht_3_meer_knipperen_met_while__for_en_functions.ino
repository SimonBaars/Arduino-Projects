const int poort = 13;
const int duurPeriode = 5000;
const int aantalHertz1 = 10;
const int aantalHertz2 = 5;
const int beginDelay = 1000/aantalHertz1;//Berekening om Hz om te zetten in millis

int delayTijd = beginDelay;
int beginTijd;
int beginTijdPeriode;
boolean lampjeBrandt=false;

void setup() {                
  pinMode(poort, OUTPUT);
  beginTijd=millis();
  beginTijdPeriode=millis();
}


void loop() {
  laatLampjeKnipperen(duurPeriode);
  veranderKnipperTijd(aantalHertz1, aantalHertz2, beginDelay);
}

void laatLampjeKnipperen(int duur/*(millis)*/){
  if(millis()>beginTijd+delayTijd){
    if(lampjeBrandt){
      digitalWrite(poort, LOW);
    }
    else{
      digitalWrite(poort, HIGH);
    }
    lampjeBrandt=!lampjeBrandt;
    beginTijd=millis();
  }
}

void veranderKnipperTijd(int frequentie1/*(Hz)*/, int frequentie2/*(Hz)*/, int periodeDuur){
  if(millis()>beginTijdPeriode+duurPeriode){
    if(delayTijd==beginDelay){
      delayTijd=(beginDelay*frequentie1)/frequentie2;
    } else if(delayTijd==(beginDelay*frequentie1)/frequentie2){
      delayTijd=beginDelay;
    }
    beginTijdPeriode=millis();
  }
}


const int poort = 13;
const int duurPeriode1 = 2000;
const int duurPeriode2 = 3000;
const int aantalHertz1 = 1;
const int aantalHertz2 = 2;
const int dutyCycle1 = 10;
const int dutyCycle2 = 50;
const int beginDelay = 1000/aantalHertz1;//Berekening om Hz om te zetten in millis
const int baudrate = 9600;

int delayTijd = beginDelay;
int beginTijd;
int beginTijdPeriode;
boolean lampjeBrandt=false;
boolean periode = true;

void setup() {                
  ledControlSetup();
  Serial.begin(baudrate);
  beginTijd=millis();
  beginTijdPeriode=millis();
}


void loop() {
  if(periode){
    laatLampjeKnipperen(dutyCycle1);
    veranderKnipperTijd(aantalHertz2, beginDelay, duurPeriode1);
  } 
  else{
    laatLampjeKnipperen(dutyCycle2);
    veranderKnipperTijd(aantalHertz2, beginDelay, duurPeriode2);
  }
}

void laatLampjeKnipperen(int dutyCycle){
  if(millis()>beginTijd+((delayTijd/2)/100*dutyCycle) && lampjeBrandt){
    Serial.println(((delayTijd*2)/100*dutyCycle));
    ledControlSetLed(false);
    wisselLampje();
  } 
  else if(millis()>beginTijd+((delayTijd/2)/100*(100-dutyCycle)) && !lampjeBrandt){
    Serial.println(((delayTijd*2)/(100-dutyCycle)));
    ledControlSetLed(true);
    wisselLampje();
  }
}

void wisselLampje(){
  lampjeBrandt=!lampjeBrandt;
  beginTijd=millis();
}
void veranderKnipperTijd(int frequentie/*(Hz)*/, int beginDelay, int periodeDuur){
  if(millis()>beginTijdPeriode+periodeDuur){
    if(periode){
      delayTijd=1000/frequentie;
    } 
    else {
      delayTijd=beginDelay;
    }
    beginTijdPeriode=millis();
    periode=!periode;
  }
}





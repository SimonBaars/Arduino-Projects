const int poort = 13;
const int aantalHertz1 = 50;
int dutyCycle1 = 5;
const int duurPeriode1 = 2000;
const int beginDelay = 1000/aantalHertz1;//Berekening om Hz om te zetten in millis
const int baudrate = 9600;

int delayTijd = beginDelay;
int beginTijd;
boolean lampjeBrandt=false;
int beginTijdPeriode;
boolean periode = true;

void setup() {                
  ledControlSetup();
  Serial.begin(baudrate);
  beginTijd=millis();
  beginTijdPeriode=millis();
}


void loop() {
  laatLampjeKnipperen(dutyCycle1);
   veranderKnipperTijd(beginDelay, duurPeriode1);
}

void laatLampjeKnipperen(int dutyCycle){
  if(millis()>beginTijd+((delayTijd/2)/100*dutyCycle) && lampjeBrandt){
    ledControlSetLed(false);
    wisselLampje();
    Serial.println(1);
  } 
  else if(millis()>beginTijd+((delayTijd/2)/100*(100-dutyCycle)) && !lampjeBrandt){
    ledControlSetLed(true);
    wisselLampje();
    Serial.println(2);
  }
}

void wisselLampje(){
  lampjeBrandt=!lampjeBrandt;
  beginTijd=millis();
}

void veranderKnipperTijd(int beginDelay, int periodeDuur){
  if(millis()>beginTijdPeriode+periodeDuur){
    delayTijd=beginDelay;
    dutyCycle1+=5;
    if(dutyCycle1>100){
      dutyCycle1=5;
    }
    Serial.println(dutyCycle1);
    beginTijdPeriode=millis();
    periode=!periode;
  }
}





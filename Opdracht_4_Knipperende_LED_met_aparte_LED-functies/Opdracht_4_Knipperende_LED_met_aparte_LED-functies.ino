const int poort = 13;
const int delayTijd = 1000;
boolean lampjeBrandt=false;
int beginTijd;

void setup() {                
  ledControlSetup();
  beginTijd=millis();
}


void loop() {
  laatLampjeKnipperen();
}

void laatLampjeKnipperen(){
  if(millis()>beginTijd+delayTijd){
    if(lampjeBrandt){
      ledControlSetLed(false);
    }else{
      ledControlSetLed(true);
    }
    lampjeBrandt=!lampjeBrandt;
    beginTijd=millis();
  }
}

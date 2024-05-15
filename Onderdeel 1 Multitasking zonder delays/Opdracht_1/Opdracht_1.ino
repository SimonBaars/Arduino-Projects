const int poort = 13;
const int aantalHertz1= 2;
const int aantalHertz2= 5;
boolean lampjeBrandt=false;
int beginTijd;

void setup() {                
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  beginTijd=millis();
}


void loop() {
  laatLampjeKnipperen();
}

void laatLampjeKnipperen(){
  knipperLampje(1000/aantalHertz1, 12);
   knipperLampje(1000/aantalHertz1, 13);
}

void knipperLampje(poort, delayTijd){
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

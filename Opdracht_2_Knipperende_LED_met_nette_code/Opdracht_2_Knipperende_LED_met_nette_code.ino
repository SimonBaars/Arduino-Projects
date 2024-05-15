const int poort = 13;
const int delayTijd = 1000;
boolean lampjeBrandt=false;
int beginTijd;

void setup() {                
  pinMode(poort, OUTPUT);
  beginTijd=millis();
}


void loop() {
  laatLampjeKnipperen();
}

void laatLampjeKnipperen(){
  if(millis()>beginTijd+delayTijd){
    if(lampjeBrandt){
      digitalWrite(poort, LOW);
    }else{
      digitalWrite(poort, HIGH);
    }
    lampjeBrandt=!lampjeBrandt;
    beginTijd=millis();
  }
}

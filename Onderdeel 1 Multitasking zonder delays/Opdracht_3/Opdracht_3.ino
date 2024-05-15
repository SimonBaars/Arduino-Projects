const int aantalLampjes = 9;
const int beginPoort = 2;
boolean lampjeBrandt=false;
long beginTijd[aantalLampjes] = {millis(),millis(),millis(),millis(),millis(),millis(),millis(),millis(),millis()};

void setup() { 
  Serial.begin(9600);  
   for(int i = beginPoort; i<beginPoort+aantalLampjes; i++){  
   ledControlSetup(i);
   }
}

void loop() {
  laatLampjeKnipperen();
}

void laatLampjeKnipperen(){
  for(int i = beginPoort; i<beginPoort+aantalLampjes; i++){  
    knipperLampje(i, 1000/i-1);
  }
}

void knipperLampje(int poort, int delayTijd){
  if(millis()>beginTijd[poort-2]+delayTijd){
    if(lampjeBrandt){
      ledControlSetLed(poort, false);
    }
    else{
      ledControlSetLed(poort, true);
      Serial.println(poort);
    }
    lampjeBrandt=!lampjeBrandt;
    beginTijd[poort-2]=millis();
  }
}





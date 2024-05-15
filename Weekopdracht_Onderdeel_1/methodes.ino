void ledControlSetup(int poort){
  pinMode(poort, OUTPUT);
}

void ledControlSetLed(int poort, boolean onOrOff){
  if(onOrOff){
    digitalWrite(poort, HIGH);
  } else {
    digitalWrite(poort, LOW);
  }
}

void setupAllLeds(){
  for(int i = startGetal; i<aantalLeds+startGetal; i++){ 
    ledControlSetup(i);
  }
}

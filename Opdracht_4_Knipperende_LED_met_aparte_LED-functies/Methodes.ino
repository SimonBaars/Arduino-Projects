void ledControlSetup(){
  pinMode(poort, OUTPUT);
}

void ledControlSetLed(boolean onOrOff){
  if(onOrOff){
    digitalWrite(poort, HIGH);
  } else {
    digitalWrite(poort, LOW);
  }
}

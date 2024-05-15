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

void ledControlSetup(){
  pinMode(poort, OUTPUT);
}

void ledControlSetLed(boolean onOrOff){
  if(onOrOff){
    digitalWrite(poort, HIGH);
    Serial.println("HIGH");
  } else {
    digitalWrite(poort, LOW);
    Serial.println("LOW");
  }
}

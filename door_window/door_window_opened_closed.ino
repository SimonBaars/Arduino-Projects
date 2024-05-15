#define doorpin 2
#define doorindicator 8

void initDoor() {
  pinMode(doorpin, INPUT);
  attachInterrupt(2, doorTrigger, CHANGE);
}
  
  
void doorTrigger() {
  doorOpened = !doorOpened;
  if (doorOpened) {
    digitalWrite(doorindicator, HIGH);
  }
  else {
    digitalWrite(doorindicator, LOW);
  }
}



bool doorOpened = 0;

void setup() {
  initDoor();
}

void loop() {
  if (doorOpened) {
    Serial.println("Door is opened!");
  }
  else {
    Serial.println("Door is closed!");
  }
}

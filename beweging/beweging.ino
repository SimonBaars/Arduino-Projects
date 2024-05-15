
void setup() {
  initMotion();
  Serial.begin(9600);
}

void loop() {
  Serial.println(motionDetected());
}

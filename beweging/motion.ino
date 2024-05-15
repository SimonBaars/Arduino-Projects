#define MOTIONPIN 3

void initMotion() {
  pinMode(MOTIONPIN, INPUT);
}

boolean motionDetected() {
  return digitalRead(MOTIONPIN);
}

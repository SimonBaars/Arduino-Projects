#define lightpin 1

int readLightRAW() {
  return analogRead(lightpin);
}

int readLight() {
  return map(readLightRAW(), 950, 200, 0, 575);
}

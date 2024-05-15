int testNummer=1;
unsigned long loopTeller=0;
long vorigeMillis;

void setup(){
  Serial.begin(9600);
  vorigeMillis=millis();
  loopTeller=0;
}

void loop(){
  loopTeller++;
  if(millis()>vorigeMillis+1000){
    Serial.print("Test ");
    Serial.print(testNummer);
    Serial.print(": ");
    Serial.print(loopTeller);
    Serial.println("x geloopt in 1 seconde");
    loopTeller=0;
    testNummer++;
    vorigeMillis=millis();
  }
}

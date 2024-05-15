void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(2,INPUT);
  attachInterrupt(0,doorChange, CHANGE);
}

void loop() {
  // put your main code here, to run repeatedly:
  
}

void doorChange(){
  if(digitalRead(2)){
    Serial.println("Deurtje dicht");
  } else {
    Serial.println("Deurtje open");
  }
}

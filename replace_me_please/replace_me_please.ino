void setup(){
  Serial.begin(9600);
  for (int i =0; i<100; i++){
    /* BIN, OCT, DEC, HEX)*/
    Serial.print("Binair = ");
    Serial.print(i,BIN);
    Serial.print(", Octaal = ");
    Serial.print(i,OCT);
    Serial.print(", Decimaal = ");
    Serial.print(i,DEC);
    Serial.print(", Hexadecimaal = ");
    Serial.print(i,HEX);
    Serial.print(" en ASCII = ");
    Serial.write(i);
    Serial.println(".");
  }
  Serial.flush();
}

void loop(){
  
}

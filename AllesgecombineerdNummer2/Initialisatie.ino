void initAfstand(){
  long duration, cm;
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
}

void initRobot(){
  //begin code servo
  //Setup Channel A
  pinMode(12, OUTPUT); //Initiates Motor Channel A pin
  pinMode(9, OUTPUT); //Initiates Brake Channel A pin

  //Setup Channel B
  pinMode(13, OUTPUT); //Initiates Motor Channel A pin
  pinMode(8, OUTPUT);  //Initiates Brake Channel A pin
  //einde code servo
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */


  Serial.begin (9600);
  
   
  digitCounter=0;
  initLedmatrix();
  maakBlij();
}

void initLedmatrix(){
  for (int i=0; i< NBR_MTX; i++){
    lc.shutdown(i,false);
    /* Set the brightness to a medium values */
    lc.setIntensity(i,8);
    /* and clear the display */
    lc.clearDisplay(i);
  }
}

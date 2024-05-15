byte resetOfOphogen (byte minimum, byte maximum, byte getal) {
  if( getal == maximum) {
    getal == minimum;
  }
  else
  {
    getal++;
  }
  return getal;
}

char verkrijgTeken(byte getal){
  if(getal>0 && getal<27){
    return getal+64;
  } 
  else if(getal==27){
    return 32;
  } 
  else if(getal>27 && getal<38){
    return getal+20;
  } 
  else if(getal==38){
    return 61;
  } 
  else {
    Serial.println("So sollte es nicht sein. Bitte noch einmal!");
    return 0;
  }
}



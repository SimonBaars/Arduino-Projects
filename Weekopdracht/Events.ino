//Event 1: heen
void event1(){
  if(eventStatus==1){
    for(int i = startGetal; i<=aantalLeds+startGetal; i++){
      if(i==startGetal){
        ledControlSetLed(aantalLeds+1, false);
      } 
      else {
        ledControlSetLed(i-1, false);
      }
      ledControlSetLed(i, true);
      delay(100);
    }
  }
}

//Event 2: samenvoegen
void event2(){
  if(eventStatus==2){
    for(int i = startGetal; i<=(aantalLeds+startGetal)/2; i++){
      if(i==startGetal){
        ledControlSetLed(aantalLeds/2+startGetal, false);
        ledControlSetLed(aantalLeds/2+startGetal-1, false);
      } 
      else {
        ledControlSetLed(i-1, false);
        ledControlSetLed(aantalLeds-i+startGetal+2, false);
      }
      ledControlSetLed(i, true);
      ledControlSetLed(aantalLeds-i+startGetal+1, true);
      delay(100);
    }
  }
}



  boolean EnterRechts = true;
  boolean EnterLinks = true;
  
void VerkeerslichtRechts(){
  if (EnterRechts == true) {
    VKLNummer = 0;
    EnterRechts = false;
  }
  if (LichtGroenRechts == true){
    LampenRechtsUit();
    digitalWrite(LedGroenRechts,HIGH);
    if (VKLNummer == 4) {
      LampenRechtsUit();
      digitalWrite(LedGeelRechts,HIGH);
    }
    else if (VKLNummer == 5) {
      LampenRechtsUit();
      LichtGroenRechts = false;
      Ontruimen[2] = false;
      EnterRechts = true;
    }
  }
}

void VerkeerslichtLinks(){
  if (EnterLinks == true) {
    VKLNummer = 0;
    EnterLinks = false;
  }
  if (LichtGroenLinks == true){
    LampenLinksUit();
    digitalWrite(LedGroenLinks,HIGH);
    if (VKLNummer == 4) {
      LampenLinksUit();
      digitalWrite(LedGeelLinks,HIGH);
    }
    else if (VKLNummer == 5) {
      LampenLinksUit();
      LichtGroenLinks = false;
      Ontruimen[1] = false;
      EnterRechts = true;
    }
  }

}

void LampenRechtsUit(){
  digitalWrite(LedGroenRechts,LOW);
  digitalWrite(LedGeelRechts,LOW);
  digitalWrite(LedRoodRechts,LOW);
}

void LampenLinksUit(){
  digitalWrite(LedGroenLinks,LOW);
  digitalWrite(LedGeelLinks,LOW);
  digitalWrite(LedRoodLinks,LOW);
}

void VKLKlok(){
  unsigned long  VKLCurrentMillis = millis();
  if (VKLCurrentMillis - VKLPreviousMillis > IntervalEenSec) {
    VKLPreviousMillis = VKLCurrentMillis; 
    if (VKLNummer >= 0 && VKLNummer <= 9){
      VKLNummer = VKLNummer++;
      //Serial.print(VKLNummer);
    }
    else { 
      VKLNummer = 0; 
      //Serial.print("VKL reset");
    }
  }
}


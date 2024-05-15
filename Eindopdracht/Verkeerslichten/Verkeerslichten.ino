void VerkeerslichtRechts(){
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
  }
  }
  else if (LichtGroenRechts == false){
digitalWrite(LedRoodRechts,HIGH);
  }
  }
 void VerkeerslichtLinks(){
   if (LichtGroenLinks == true){
    LampenLinksUit();
  digitalWrite(LedGroenLinks,HIGH);
  digitalWrite(LedGroenRechts,HIGH);
   if (VKLNummer == 4) {
  LampenLinksUit();
  digitalWrite(LedGeelLinks,HIGH);
   }
   else if (VKLNummer == 5) {
  LampenLinksUit();
  LichtGroenLinks = false;
  }
   }
  else if (LichtGroenLinks == false){
digitalWrite(LedRoodLinks,HIGH);
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
      Serial.print(VKLNummer);
    }
    else { 
      VKLNummer = 0; 
      Serial.print("VKL reset");
    }
  }
}

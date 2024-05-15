void VerkeerslichtRechts(){
  if (LichtGroenRechts == true){
    LampenRechtsUit();
  digitalWrite(LedGroenRechts,HIGH);
  delay(3000);
  LampenRechtsUit();
  digitalWrite(LedGeelRechts,HIGH);
  delay(1000);
  LampenRechtsUit();
  LichtGroenRechts = false;
  }
  else if (LichtGroenRechts == false){
digitalWrite(LedRoodRechts,HIGH);
  }
  }
 void VerkeerslichtLinks(){
   if (LichtGroenLinks == true){
    LampenLinksUit();
  digitalWrite(LedGroenLinks,HIGH);
  delay(3000);
  LampenLinksUit();
  digitalWrite(LedGeelLinks,HIGH);
  delay(1000);
  LampenLinksUit();
  LichtGroenLinks = false;
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

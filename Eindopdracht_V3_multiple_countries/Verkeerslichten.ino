  boolean EnterRechts = true;
  boolean EnterLinks = true;
  
void VerkeerslichtRechts(){
  if (EnterRechts == true) {
    VKLNummer = 0;
    EnterRechts = false;
  }
  //Nederland
  if (LichtGroenRechts == true && Land == 1){
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
  //Duitsland
    if (LichtGroenRechts == true && Land == 2){
    if (VKLNummer == 0){
      LampenRechtsUit();
    digitalWrite(LedGeelRechts,HIGH);
    digitalWrite(LedRoodRechts,HIGH);
    }
    else if (VKLNummer == 2) {
      LampenRechtsUit();
      digitalWrite(LedGroenRechts,HIGH);
    }
      else if (VKLNummer == 6) {
      LampenRechtsUit();
      digitalWrite(LedGeelRechts,HIGH);
      }
    else if (VKLNummer == 7) {
      LampenRechtsUit();
      LichtGroenRechts = false;
      Ontruimen[2] = false;
      EnterRechts = true;
    }
  }

  //Oostenrijk
    if (LichtGroenRechts == true & Land == 3){
      if (VKLNummer == 0){
      LampenRechtsUit();
    digitalWrite(LedGeelRechts,HIGH);
    digitalWrite(LedRoodRechts,HIGH);
    }
    else if (VKLNummer == 2) {
      LampenRechtsUit();
      digitalWrite(LedGroenRechts,HIGH);
    }
    else if(VKLNummer == 3){
      LampenRechtsUit();
    }
    else if (VKLNummer == 4) {
      LampenRechtsUit();
      digitalWrite(LedGroenRechts,HIGH);
    }
    else if(VKLNummer == 5){
      LampenRechtsUit();
    }
      else if (VKLNummer == 6) {
      LampenRechtsUit();
      digitalWrite(LedGeelRechts,HIGH);
      }
    else if (VKLNummer == 8) {
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
  //Nederland
  if (LichtGroenLinks == true && Land == 1){
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
      EnterLinks = true;
    }
  }
  //Duitsland
    if (LichtGroenLinks == true && Land == 2){
    if (VKLNummer == 0){
      LampenLinksUit();
    digitalWrite(LedGeelLinks,HIGH);
    digitalWrite(LedRoodLinks,HIGH);
    }
    else if (VKLNummer == 2) {
      LampenLinksUit();
      digitalWrite(LedGroenLinks,HIGH);
    }
      else if (VKLNummer == 6) {
      LampenLinksUit();
      digitalWrite(LedGeelLinks,HIGH);
      }
    else if (VKLNummer == 7) {
      LampenLinksUit();
      LichtGroenLinks = false;
      Ontruimen[2] = false;
      EnterLinks = true;
    }
  }
//Oostenrijk
    if (LichtGroenLinks == true & Land == 3){
      if (VKLNummer == 0){
      LampenLinksUit();
    digitalWrite(LedGeelLinks,HIGH);
    digitalWrite(LedRoodLinks,HIGH);
    }
    else if (VKLNummer == 2) {
      LampenLinksUit();
      digitalWrite(LedGroenLinks,HIGH);
    }
    else if(VKLNummer == 3){
      LampenLinksUit();
    }
    else if (VKLNummer == 4) {
      LampenLinksUit();
      digitalWrite(LedGroenLinks,HIGH);
    }
    else if(VKLNummer == 5){
      LampenLinksUit();
    }
      else if (VKLNummer == 6) {
      LampenRechtsUit();
      digitalWrite(LedGeelLinks,HIGH);
      }
    else if (VKLNummer == 8) {
      LampenLinksUit();
      LichtGroenLinks = false;
      Ontruimen[2] = false;
      EnterLinks = true;
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
    if (VKLNummer >= 0 && VKLNummer <= 19){
      VKLNummer = VKLNummer++;
    }
    else { 
      VKLNummer = 0; 
    }
  }
}


void CheckButtons(){
  ButtonStateLinks = digitalRead(ButtonLinks);
  ButtonStateMidden = digitalRead(ButtonMidden);
  ButtonStateRechts = digitalRead(ButtonRechts);
  ButtonStateAlles = digitalRead(ButtonAlles);

  if (ButtonStateLinks == LOW) {
    LichtGroenLinks = true;
  }
  else if (ButtonStateRechts == LOW){ 
    LichtGroenRechts = true;
  }
  else if(ButtonStateMidden == LOW){
    MatrixStart = true;
  }
  else if(ButtonStateAlles == LOW){
    AllesStart = true;
  }
}


void Verkeerslichten() {

  if (Ontruimen[0] == false && Ontruimen[1] == false && LichtGroenRechts == true) {
    Ontruimen[2] = true;
    VerkeerslichtRechts();
  }
  else if (Ontruimen[0] == false && Ontruimen[2] == false && LichtGroenLinks == true) {
    Ontruimen[1] = true;
    VerkeerslichtLinks();

  }
  else if (Ontruimen[1] == false && Ontruimen[2] == false && MatrixStart == true) {
    Ontruimen[0] = true;
    Aftellen();

  }
}

void StandaardSituatie() {
  if (Ontruimen[2] == true) {
    digitalWrite(LedRoodLinks,HIGH);
    Kruis();
  } 
  else if (Ontruimen[1] == true) {
    digitalWrite(LedRoodRechts,HIGH);
    Kruis();
  } 
  else if (Ontruimen[2] == true) {
    digitalWrite(LedRoodRechts,HIGH);
    digitalWrite(LedRoodLinks,HIGH);
  }
  else if (Ontruimen[0] == false && Ontruimen[1] == false && Ontruimen[2] == false) {
    digitalWrite(LedRoodRechts,HIGH);
    digitalWrite(LedRoodLinks,HIGH);
    Kruis();
  }
}


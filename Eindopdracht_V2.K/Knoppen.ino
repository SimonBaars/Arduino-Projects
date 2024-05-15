void CheckButtons(){
  ButtonStateLinks = digitalRead(ButtonLinks);
  ButtonStateMidden = digitalRead(ButtonMidden);
  ButtonStateRechts = digitalRead(ButtonRechts);

  if (ButtonStateLinks == LOW) {
    LichtGroenLinks = true;
  }
  else if (ButtonStateRechts == LOW){ 
    LichtGroenRechts = true;
  }
  else if(ButtonStateMidden == LOW){
    MatrixStart = true;
  }
}


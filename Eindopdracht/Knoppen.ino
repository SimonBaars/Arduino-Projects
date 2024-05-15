void CheckButtons(){
  ButtonStateLinks = digitalRead(ButtonLinks);
  ButtonStateMidden = digitalRead(ButtonMidden);
  ButtonStateRechts = digitalRead(ButtonRechts);
  
  if (ButtonStateLinks == LOW) {
    LichtGroenLinks = true;
    VKLNummer = 0;
  }
  if (ButtonStateRechts == LOW){ 
    LichtGroenRechts = true;
    VKLNummer = 0;
  }
if(ButtonStateMidden == LOW){
  MatrixStart = true;
  MatrixNummer = 0;
}
}

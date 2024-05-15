void CheckButtons(){
  ButtonStateLinks = digitalRead(ButtonLinks);
  ButtonStateMidden = digitalRead(ButtonMidden);
  ButtonStateRechts = digitalRead(ButtonRechts);
  
  if (ButtonStateLinks == LOW) {
    LichtGroenLinks = true;
  }
  if (ButtonStateRechts == LOW){ 
    LichtGroenRechts = true;
  }
if(ButtonStateMidden == LOW){
  MatrixStart = true;
}
}

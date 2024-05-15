unsigned long PrevSnelTikMil = 0;
unsigned long PrevLangTikMil = 0;
unsigned long PrevAftelTikMil = 0;
unsigned long PrevBreakMil = 0;

boolean SmileyTikken() {

  int SnelTikInt = 60;

  if (millis() - PrevSnelTikMil > SnelTikInt) {
    PrevSnelTikMil = millis();
    Buzz = !Buzz;
  }
}

boolean KruisTikken() {

  int LangTikIntOn = 940;
  int LangTikIntOff = 60;

  if (Buzz == false) {
    if (millis() - PrevLangTikMil > LangTikIntOn) {
      PrevLangTikMil = millis();
      return Buzz = true;
    }
  } 
  else {
    if (millis() - PrevLangTikMil > LangTikIntOff) {
      PrevLangTikMil = millis();
      return Buzz = false;
    }
  }
}

boolean AftelTikken() {
// INSERT BREAK HERE
  int tik = 0;
  int AftelTikSnelInt = 60;
  int AftelTikBreakInt = 1000;
  boolean Break = false;


  if (Break = false) {
    for(tik = 0; tik < 7; tik++) {
      if (millis() - PrevAftelTikMil > AftelTikSnelInt) {
        PrevAftelTikMil = millis();
        PrevBreakMil = millis();
        Buzz = !Buzz;
      }
    }
    Break = true;
  }

  else if (Break == true) {
    if (millis() - PrevBreakMil > AftelTikBreakInt) {
      Buzz = false;
      PrevBreakMil = millis();
      tik = 0;
      Break = false;
    }
  }
}


void Buzzer(boolean Buzz) {
  if (Buzz == true) {
    tone(Geluid, 580);
  } 
  else {
    noTone(Geluid);
  }
}

















unsigned long PrevSnelTikMil = 0;
unsigned long PrevLangTikMil = 0;
unsigned long PrevAftelTikMil = 0;
unsigned long PrevBreakMil = 0;
boolean Break = false;
byte stage = 0;
int wachttijd = 60;


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
  int AftelTikSnelInt = 60;
  int AftelTikBreakInt = 750;

  if (millis() - PrevAftelTikMil > wachttijd) {
    PrevAftelTikMil = millis();
    Buzz = !Buzz;
    stage++;
    if(stage==5){
      wachttijd = AftelTikBreakInt;
      Buzz = false;
    } 
    else if(stage==6){
      wachttijd = AftelTikSnelInt;
      Buzz = true;
      stage = 0;
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

void TikStand(byte TikMethode) {
  if (TikMethode == 0) {
    KruisTikken();
  } 
  else if (TikMethode == 1) {
    SmileyTikken();
  } 
  else if (TikMethode == 2) {
    AftelTikken();
  }
}





















byte modus = 0;
boolean knopGedrukt = false;
boolean lampjeAan = false;
long teller;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(7,INPUT);
  pinMode(8,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  boolean knopAan = !digitalRead(7);
  if(knopAan && !knopGedrukt){
    modus++;
    if(modus==3){
      modus=0;
    }
    if(modus==1){
      teller=millis();
    }
    knopGedrukt=true;
  }  else {
    knopGedrukt=false;
  }

  if(modus==0){
    digitalWrite(8, HIGH);
  } else if(modus==1){
    if(lampjeAan){
    digitalWrite(8, HIGH);
    } else {
      digitalWrite(8, LOW);
    }
    if(millis()>teller+300){
      teller=millis();
      lampjeAan=!lampjeAan;
    }
  } else if(modus==2){
    digitalWrite(8, HIGH);
  }
}

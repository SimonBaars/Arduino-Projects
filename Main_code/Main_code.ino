byte aantalRotors = 5;
byte aantalTekens = 38;
char inGetypteLetter; 
byte rotorLocatie[] = {
  0,0,0};              // locatie van de rotor op dat moment. (kan dus 0 tot en met 37 zijn), [2] draait met elke ingetypte letter, die links ernaast 1 op de 38 keer daarna zelfde geld voor [0]
unsigned long rotorsInGebruik[] = {
  0,0,0};         
byte draaiPositieRotor[] = {
  11, 3, 34, 22, 18}; // positie van de rotor waarop hij een slag draait.
byte digitalPins[] = {
  0,1,2,3,4,5};
byte geselecteerdeRotorPlaats =0;
byte machtsverheffing = 0;
byte huidigGetalWaarde = 0;
char geencrypteLetter;
unsigned long previousMillis;      // voor de timer.


void setup(){  
  previousMillis=millis();
  Serial.println("Morse-Code & Enigma initialisiert, sendebereit, Mein Fuehrer");
  Serial.begin(9600);
  maakRotors();
}
void maakRotors() {
  randomSeed(aantalTekens);
  for(int j = 0; j<aantalRotors; j++){
    for(int i = 0; i<aantalTekens; i++){
      rotorWeb[j][i] = verkrijgTeken(random(0,aantalTekens));
      Serial.println(verkrijgTeken(random(0,aantalTekens)));
    }
  }
}


void loop(){
  //charArrayToMorse(geencrypteLetter);
  selecteerRotor();
  while(Serial.available() > 0) {
    inGetypteLetter = Serial.read();
    draaiRotor();
  }
}

void selecteerRotor(){
  if(digitalRead(digitalPins[0]==HIGH)){// veranderen van machtsverheffing. Met deze knop verhoog je ook automatisch de geselecteerde rotorNummer. Soort van bevestiging dus. 
    rotorsInGebruik[geselecteerdeRotorPlaats]= huidigGetalWaarde * pow(10, float(machtsverheffing))+ rotorsInGebruik[geselecteerdeRotorPlaats];
    machtsverheffing = resetOfOphogen(0, 24 , machtsverheffing);
  }
  if(digitalRead(digitalPins[1]==HIGH)){ // ophogen van huidig getal
    huidigGetalWaarde = resetOfOphogen(0, 9 , huidigGetalWaarde);
  }
  if (digitalRead(digitalPins[2]==HIGH)){ // selecteren van een andere rotor.
    geselecteerdeRotorPlaats = resetOfOphogen(0,2,geselecteerdeRotorPlaats);
  }
}






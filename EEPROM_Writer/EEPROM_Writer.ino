/*
Maak een sketch met de volgende functionaliteiten:

De waarde van een aangesloten potmeter wordt continu uitgelezen en naar de seriële poort gestuurd
Iedere 5 seconden wordt de waarde van een EEPROM-adres gelezen en naar de seriële poort gestuurd
Als er op een knop wordt gedrukt, wordt de actuele waarde van de potmeter in het EEPROM-adres bewaard. Een melding hiervan wordt naar de seriële poort gestuurd.
Let op dat een EEPROM-locatie slechts 1 byte groot is. Terwijl de waarde van de potmeter tot 1023 kan gaan. Verzin hiervoor een oplossing.
*/

void setup(){
  
}

void loop(){
   int draaiKnop = analogRead(0);
   Serial.println(draaiKnop);
}

char rotorWeb[aantalRotors][aantalTekens];

void draaiRotor (){
  rotorLocatie[2]++; 
  for(int i =1; i>=0; i==i-1){
    if (rotorLocatie[i+1] == draaiPositieRotor[rotorsInGebruik[i+1]]) {
      rotorLocatie[i]++;
    }
  }
}


char willekeurigeArray[] (unsigned long gebruikteRotor){
  byte huidigeParen[aantalTekens/2];
  char gekozenArray[aantalTekens];
  gekozenArray = standaardCharArray();
  
    return gekozenArray;
  }
}

char standaardCharArray[]() {
  char standaard[aantalTekens];
  for(int i = 0; i<aantalTekens; i++) {
    standaard[i] = verkijgTeken(i+1);
  }
  return standaard;
}










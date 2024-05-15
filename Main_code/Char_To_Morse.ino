char morseSleutel[][18] = { // Sleutel 
  {
    'A', 'E', 'F', 'H', 'I', 'J', 'L', 'P', 'R', 'S', 'U', 'V', 'W', '1', '2', '3', '4', '5'        // puntje positie 1
  }
  , {
    'B', 'C', 'D', 'G', 'K', 'M', 'N', 'O', 'Q', 'T', 'X', 'Y', 'Z', '0', '6', '7', '8', '9'       // streepje positie 1
  }
  , {
    'B', 'C', 'D', 'F', 'H', 'I', 'K', 'N', 'S', 'U', 'V', 'X', 'Y', '2', '3', '4', '5', '6'    // puntje positie 2
  }
  , {
    'A', 'G', 'J', 'L', 'M', 'O', 'P', 'Q', 'R', 'W', 'Z', '0', '1', '7', '8', '9'              // streepje positie 2
  }
  , {
    'B', 'D', 'G', 'H', 'L', 'Q', 'R', 'S', 'V', 'X', 'Z', '3', '4', '5', '6', '7'             // puntje positie 3
  }
  , {
    'C', 'F', 'J', 'K', 'O', 'P', 'U', 'W', 'Y', '0', '1', '2', '8', '9'                      // streepje positie 3
  }
  , {
    'B', 'C', 'F', 'H', 'L', 'P', 'Z', '4', '5', '6', '7', '8'                   // puntje positie 4
  }
  , {
    'J', 'Q', 'V', 'X', 'Y', '0', '1', '2', '3', '9'                            // streepje positie 4
  }
  , {
    '5', '6', '7', '8', '9'                                                     // puntje positie 5
  }
  , {
    '0', '1', '2', '3', '4'                                                    // streepje positie 5
  }
};
char woord[] = {
  'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'X', 'V', 'X', 'W', 'X', 'Y', 'Z'
};                                                                          
int huidigechar=0;        // char is letter of letterspatie in woord. Dus even is letter en oneven is letterspatie. HOI = H =0 , O = 2 en I =4 de letterspaties zijn dus 1,3,5.    GAAT OVER WOORD
int huidigefase=0;        // Fase is puntje of streepje in morsecode. Morsetekenspatie = onevennummer. Morseteken (. of - ) is even. A = .- waarbij . = 0 en - = 2. Dus morsetekenspatie tussen . & - = 1 en spatie van - = 3. 
const int wachttijd=20;   //lengte morseteken in milliseconden. 
int huidigeWachtTijd=20; // berekende wachttijd. Kan ook 20 * 3 zijn of 20 *7 ligt er dus aan wat voor teken het is of het een letterspatie is of een morsetekenspatie. 
boolean timeSet=false;    // voert alleen loop uit als het nodig is. Om herhaling te voorkomen. 
boolean charWissel[]= {
  false, false, false
};  // Als charWissel[0] == true wordt van char gewisseld. CharWissel[1] er zijn geen puntjes meer nodig == true en charwissel[2] voor streepjes. Als 1 en 2 zijn true dan wordt 0 true. 
boolean morseCodeSent=false;              // Als morseCodeSent = true dan is het einde van het bericht. Anders telt hij eindeloos en zinloos door. 

void charArrayToMorse(char charArray[]) {
  if (!morseCodeSent) {
    if (!timeSet) { // als timeset is false mag hij wel dit doen als hij true is niet ga dan maar iets anders doen. --- o==3
      if (checkEven(huidigechar) && checkEven(huidigefase)) {
        charToMorse(charArray[int(huidigechar/2)], huidigechar/2, huidigefase/2); // /2 omdat compensatie van lengte van de char vanwege de spaties. 
      } 
      else if (!checkEven(huidigechar)) {      // letterspatie.
        wachtEven(wachttijd*3);
        charWissel[0]=true;
      } 
      else if (!checkEven(huidigefase)) {      // morse teken spatie. 
        wachtEven(wachttijd);
      }
    }
    if ((millis()>previousMillis + huidigeWachtTijd) && !charWissel[0]) { // faseWissel. 
      huidigefase=huidigefase+1;
      timeSet=false;
      if (huidigefase>10) { // spaties en morsecode. Om te voorkomen dat hij uit de lengte van de Char schiet. Alleen bij getallen. 
        charWissel[0]=true;
      }
      previousMillis=millis();
    }
    if ((millis()>previousMillis + huidigeWachtTijd) && charWissel[0]) { // Hoogt charwissel op met 1.
      huidigechar=huidigechar+1;
      Serial.println(" ");
      timeSet=false;      // tijd voor een nieuwe char
      charWissel[0]=false;  // hij is net gewisseld.
      huidigefase=0;
      previousMillis=millis();
    }
    if (huidigechar/2>sizeof(charArray)/sizeof(char)-1) { // als dit true is dan betekent dat dat alle letters zijn verstuurd. Dus huidigechar/2 vanwege oneven spaties en lengt-1 vanwegen compensatie van de 0 positie die de length niet kent.
      Serial.println("Morse-Code ist abgeschickt!");
      morseCodeSent=true;
    }
  }
}


void charToMorse(char morseChar, int character, int fase) {
  for (int i =0; i<sizeof(morseSleutel[(fase*2)])/sizeof(char)+1; i++) {
    if (i==sizeof(morseSleutel[(fase*2)])/sizeof(char)) {
      charWissel[1]=true;
    } 
    else if (morseChar==morseSleutel[(fase*2)][i]) {
      Serial.print(".");
      previousMillis=millis();
      huidigeWachtTijd=wachttijd;
      i+=sizeof(morseSleutel[(fase*2)])/sizeof(char)+1; // springt uit de for loop. 
    }
  }
  for (int i =0; i<sizeof(morseSleutel[(fase*2)+1])/sizeof(char); i++) {
    if (i==sizeof(morseSleutel[(fase*2)+1])/sizeof(char)) {
      charWissel[2]=true;
    } 
    else if (morseChar==morseSleutel[(fase*2)+1][i]) {
      Serial.print("-");
      previousMillis=millis();
      huidigeWachtTijd=wachttijd*3;
      i+=sizeof(morseSleutel[(fase*2)])/sizeof(char);
    }
  }
  if (morseChar==' ') {
    wachtEven(wachttijd*7);
    Serial.println("Raum");
    charWissel[0]=true;
  }
  if (charWissel[1] && charWissel[2]) { // zegt eigenlijk dat er van char gewisseld mag worden.
    charWissel[0]=true;
  } 
  charWissel[1]=false;
  charWissel[2]=false;

  timeSet=true;
}

  boolean checkEven(int x) {
  if (x % 2==1) { 
    return false;
  }
  return true;
}
void wachtEven(int wachttijd) {
  //println("Geluidpin laag");
  previousMillis=millis();
  huidigeWachtTijd=wachttijd*3;
  timeSet=true;
}

/*
void stuurMorse(boolean geluid, boolean lengte){
 byte signaal = LOW;
 if(geluid){
 signaal = HIGH;
 }
 if(millis() >= previousMillis + lengteMorseTeken*+lengteMorseTeken){
 pinMode(geluidPin, signaal);
 }
 }
 */


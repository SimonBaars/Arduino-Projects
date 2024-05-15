char inData[20]; //Ik ben van plan eerst een array van characters te maken van alles wat wordt ingetypt in de Serial (ik ben er namelijk achter gekomen dat de Serial er anders hele rare dingen van maakt)
char inChar; 
byte index = 0;
boolean isNietLeeggemaakt = false;
boolean moetNogPrinten = false;

void setup(){
  Serial.begin(9600);
  
  for(int i = 2; i<=10; i++){
    pinMode(i, OUTPUT);
  }
  
  maakLeeg();
}

void loop()
{

  while(Serial.available() > 0)//Hoeveel characters er ingetypt zijn
  {
    delay(10); //Deze delay blijkt belangrijk te zijn!! Anders leest die niet alles in een keer (rare arduino).
    if(isNietLeeggemaakt){
      maakLeeg();
      isNietLeeggemaakt=false;
    }

    if(index < 19) //Sorry voor alle getallen in de code: heb nog geen tijd gehad om het op te ruimen
    {
      inChar = Serial.read(); 
      inData[index] = inChar; 
      index++; 
      inData[index] = '\0'; //Als ik dit niet doe gaat het programma rare tekens aan de array toevoegen. Vandaar /0 op de index 1 na de zojuist ingevoegde!!
      moetNogPrinten=true;
    }

  }

  if(Serial.available() == 0){
    isNietLeeggemaakt=true;
    if(moetNogPrinten){
      Serial.print("De input is: ");
      Serial.println(inData);
      allesLaag();
      checkBinair();//Alle datatypen checken
      checkDecimaal();
      checkOctaal();
      checkHexadecimaal();
      checkHallo();//We moeten wel beleefd blijven
      moetNogPrinten=false;
    }
  }
}

void maakLeeg(){
  for(int i = 0; i<20; i++){
    inData[i]=' ';
  }
  index=0;
}

void checkBinair(){
  if(inData[0]=='B'){
    Serial.println("De input is binair");
    long totaal=0;
    int teller=0;
    int index;

    for(int i =1; i<20; i++){
      if(inData[int(i)]=='0' || inData[int(i)]=='1'){
      } 
      else {
        index=i-1;
        i+=20;
      }
    }

    for(int i = index; i>=1; i=i-1){
      if(inData[i]=='1'){
        totaal=round(totaal+werkendepow(2,teller));
      }
      teller++;
    }
    
    visualize(totaal);
    
    Serial.print("Decimaal= ");
    Serial.print(totaal);
    Serial.print(", Hexadecimaal= ");
    Serial.print(totaal,HEX);
    Serial.print(", Octaal= ");
    Serial.println(totaal,OCT);
  }
}

void checkDecimaal(){
  if(inData[0]!='0' && inData[0]!='B' && inData[0]!='h'){
    Serial.println("De input is decimaal");

    int totaal = verkrijgDecimaal();

    visualize(totaal);

    Serial.print("Binair= ");
    Serial.print(totaal, BIN);
    Serial.print(", Hexadecimaal= ");
    Serial.print(totaal, HEX);
    Serial.print(", Octaal= ");
    Serial.println(totaal, OCT);
  }
}

void checkOctaal(){
  if(inData[0]=='0' && inData[1]!='x'){
    Serial.println("De input is octaal");

    int totaal = verkrijgDecimaal();

    int decimaal=0;
    int i=0;
    int bereken;
    while (totaal!=0)
    {
      bereken = totaal%10;
      totaal/=10;
      decimaal += bereken*werkendepow(8,i);
      i++;
    }
    
    visualize(decimaal);

    Serial.print("Binair= ");
    Serial.print(decimaal, BIN);
    Serial.print(", Hexadecimaal= ");
    Serial.print(decimaal, HEX);
    Serial.print(", Decimaal= ");
    Serial.println(decimaal);
  }
}

int verkrijgDecimaal(){
  int totaal=0;
  int teller=0;
  int index;

  for(int i =0; i<20; i++){
    if(inData[int(i)]!=' '){
    } 
    else {
      index=i-2;
      i+=20;
    }
  }

  for(int i = index; i>=0; i=i-1){
    int data = inData[i]-'0';
    totaal=totaal+data*round(werkendepow(10,teller));
    teller++;
  }
  return totaal;
}

void checkHexadecimaal(){
  if(inData[0]=='0' && inData[1]=='x'){
    Serial.println("De input is hexadecimaal");
    int charStringLengte;
    int totaal=0;
    for(charStringLengte=0; inData[charStringLengte]!='\0'; ++charStringLengte);
    for(int i=0; inData[i]!='\0'; ++i, --charStringLengte)
    {
      if(inData[i]>='0' && inData[i]<='9'){
        totaal+=(inData[i]-'0')*werkendepow(16,charStringLengte-1);
      }
      if(inData[i]>='A' && inData[i]<='F'){
        totaal+=(inData[i]-55)*werkendepow(16,charStringLengte-1);
      }
      if(inData[i]>='a' && inData[i]<='f'){
        totaal+=(inData[i]-87)*werkendepow(16,charStringLengte-1);
      }
    }
    
    visualize(totaal);
    
    Serial.print("Binair= ");
    Serial.print(totaal, BIN);
    Serial.print(", Octaal= ");
    Serial.print(totaal, OCT);
    Serial.print(", Decimaal= ");
    Serial.println(totaal);
  }
}

void checkHallo(){
  if(inData[0]=='h' && inData[1]=='o' && inData[2]=='i'){
    Serial.println("Goedendag :)");
    delay(500);
    Serial.println("Hoe gaat die ermee?");
  }
}

void visualize(int nummer){
  long totaal=0;
  int index=8;
  unsigned int bin=0;
  
  for(int i = 8; i>=0; i=i-1){
    if((nummer-werkendepow(2,i))>=0){
      digitalWrite(i+2,HIGH);
      nummer=nummer-werkendepow(2,i);
        //bin=bin+werkendepow(10,i);
      //Serial.println(bin);
    }
  }
  //Serial.println(bin);
}

int werkendepow(int grondtal, int exponent){
  int resultaat =1;
  for(int i = 1; i <=exponent; i++){
    resultaat= resultaat*grondtal;
  }
  return resultaat;
}

void allesLaag(){
  for(int i = 2; i<10; i++){
    digitalWrite(i,LOW);
  }
}

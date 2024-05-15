const int matrixsize=8;
boolean matrix[matrixsize][matrixsize];
int rij[matrixsize];
int positionTracker[]={
  0,0};
boolean notPressed[4]={true,true,true,true};

#include <Wire.h>
int i2c_LEDMatrix = 0x71;

// the setup routine runs once when you press reset:
void setup() {                
  Wire.begin(); // join i2c bus

  Wire.beginTransmission(i2c_LEDMatrix);  // initiate
  Wire.write(0x21); // turn on oscillator
  Wire.endTransmission();  

  Wire.beginTransmission(i2c_LEDMatrix);  // blinking
  Wire.write(0x81); // display on, 81 = blink OFF
  //             83 = blink 2   Hz
  //             85 = blink 1   Hz
  //             87 = blink 0.5 Hz
  Wire.endTransmission();  

  Wire.beginTransmission(i2c_LEDMatrix);  // brightness
  Wire.write(0xE0); // E0 =  1/16
  // E1 =  2/16
  // E2 =  3/16 ..
  // EF = 16/16
  Wire.endTransmission();   

  Serial.begin(9600);
  vulMatrixArray();
  vulRijArray();
}

// the loop routine runs over and over again forever:
void loop() {
  for(int i =2; i<=5; i++){
    checkKnopDruk(i);
  }
  vulRijArray();
  rij[positionTracker[0]]=bepaalSchrijfWaarde(positionTracker[1]);
  Wire.beginTransmission(i2c_LEDMatrix); 
  Wire.write(0x00);  //start of display
  Wire.write(rij[0]);               
  Wire.write(0x00);               
  Wire.write(rij[1]);               
  Wire.write(0x00);               
  Wire.write(rij[2]);               
  Wire.write(0x00);               
  Wire.write(rij[3]);               
  Wire.write(0x00); 
  Wire.write(rij[4]);               
  Wire.write(0x00);               
  Wire.write(rij[5]);               
  Wire.write(0x00);               
  Wire.write(rij[6]);               
  Wire.write(0x00);               
  Wire.write(rij[7]);               
  Wire.write(0x00); 
  Wire.endTransmission(); 
}

int bepaalSchrijfWaarde(int input){
  int binair;
  if(input==1){
    binair=B10000000;
  } 
  else if(input==2){
    binair=B01000000;
  } 
  else if(input==3){
    binair=B00100000;
  } 
  else if(input==4){
    binair=B00010000;
  } 
  else if(input==5){
    binair=B00001000;
  } 
  else if(input==6){
    binair=B00000100;
  } 
  else if(input==7){
    binair=B00000010;
  } 
  else if(input==8){
    binair=B00000001;
  } 
  else {
    binair=B00000000;
  }
  return binair;
}

void vulMatrixArray(){
  for(int i = 0; i<8; i++){
    for(int j = 0; j<8; j++){
      matrix[i][j]=false;
    }
  }
}

void vulRijArray(){
  for(int i = 0; i<8; i++){
    rij[i]=bepaalSchrijfWaarde(0);
  }
}

void checkKnopDruk(int poort){
  int buttonState = digitalRead(poort);
  if (buttonState == HIGH) {     
notPressed[poort]=true;
  }
  else {
    if(poort==2 && notPressed){
      positionTracker[0]=positionTracker[0]+1;
    } 
    else if(poort==3 && notPressed){
      positionTracker[1]=positionTracker[1]+1;
    } else if(poort==3 && notPressed){
      positionTracker[0]=positionTracker[1]-1;
    }else if(poort==4 && notPressed){
      positionTracker[1]=positionTracker[1]-1;
    }
    notPressed[poort]=false;
  }
}


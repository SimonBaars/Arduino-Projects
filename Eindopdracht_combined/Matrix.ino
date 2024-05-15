void Aftellen(){

  Wire.begin();
  Wire.beginTransmission(Matrix_Verkeerslicht);
  Wire.write(0x21);
  Wire.endTransmission();  

  Wire.beginTransmission(Matrix_Verkeerslicht);
  Wire.write(0x81);
  Wire.endTransmission();  

  Wire.beginTransmission(Matrix_Verkeerslicht);
  Wire.write(0xE0);
  Wire.endTransmission();  

MillisMatrixCheck();

if (WelkNummerMatrix == 0){
  Smiley();
  PreviousMatrixMillis = MatrixMillis;
 unsigned long MatrixMillis = millis();
}
if (WelkNummerMatrix == 1){
  Zes();
   PreviousMatrixMillis = MatrixMillis;
}
if (WelkNummerMatrix == 2){
  Vijf();
   PreviousMatrixMillis = MatrixMillis;
}
if (WelkNummerMatrix == 3){
  Vier();
   PreviousMatrixMillis = MatrixMillis;
}
if (WelkNummerMatrix == 4){
  Drie();
   PreviousMatrixMillis = MatrixMillis;
}
if (WelkNummerMatrix == 5){
  Twee();
   PreviousMatrixMillis = MatrixMillis;
 }
if (WelkNummerMatrix == 6){
  Een();
   PreviousMatrixMillis = MatrixMillis;
}
if (WelkNummerMatrix == 7){
  Kruis();
  PreviousMatrixMillis = MatrixMillis;
  MatrixStart = false; 
}
}

void MillisMatrixCheck(){
 if (MatrixMillis - PreviousMatrixMillis > MatrixInterval) {
 WelkNummerMatrix = WelkNummerMatrix+1;
 }
}
 
void Smiley(){
  byte smiley[] = {
    0x1e, 0x21, 0xcc, 0xd2 , 0xc0 , 0xd2 , 0x21, 0x1e     };
  Wire.beginTransmission(Matrix_Verkeerslicht); 
  Wire.write(0x00);
  Wire.write(smiley[0]);
  Wire.write(0x00);
  Wire.write(smiley[1]);
  Wire.write(0x00);
  Wire.write(smiley[2]);
  Wire.write(0x00);
  Wire.write(smiley[3]);
  Wire.write(0x00);
  Wire.write(smiley[4]);
  Wire.write(0x00);
  Wire.write(smiley[5]);
  Wire.write(0x00);
  Wire.write(smiley[6]);
  Wire.write(0x00);
  Wire.write(smiley[7]);
  Wire.write(0x00);
  Wire.endTransmission();
}

void Kruis(){
  byte kruis[] = {
    0xc0, 0x21, 0x12, 0x0c , 0x0c , 0x12 , 0x21, 0xc0     };
  Wire.beginTransmission(Matrix_Verkeerslicht); 
  Wire.write(0x00);
  Wire.write(kruis[0]);
  Wire.write(0x00);
  Wire.write(kruis[1]);
  Wire.write(0x00);
  Wire.write(kruis[2]);
  Wire.write(0x00);
  Wire.write(kruis[3]);
  Wire.write(0x00);
  Wire.write(kruis[4]);
  Wire.write(0x00);
  Wire.write(kruis[5]);
  Wire.write(0x00);
  Wire.write(kruis[6]);
  Wire.write(0x00);
  Wire.write(kruis[7]);
  Wire.write(0x00);
  Wire.endTransmission();
}
void Een(){
  byte een[] = {
    0x3f, 0x3f, 0x0c, 0x0c , 0x0c , 0x3c , 0x1c, 0x0c     };
  Wire.beginTransmission(Matrix_Verkeerslicht); 
  Wire.write(0x00);
  Wire.write(een[0]);
  Wire.write(0x00);
  Wire.write(een[1]);
  Wire.write(0x00);
  Wire.write(een[2]);
  Wire.write(0x00);
  Wire.write(een[3]);
  Wire.write(0x00);
  Wire.write(een[4]);
  Wire.write(0x00);
  Wire.write(een[5]);
  Wire.write(0x00);
  Wire.write(een[6]);
  Wire.write(0x00);
  Wire.write(een[7]);
  Wire.write(0x00);
  Wire.endTransmission();
}
void Twee(){
  byte twee[] = {
    0x3f, 0x3f, 0x30, 0x3F, 0x3F,0x03, 0x3f, 0x3f       };
  Wire.beginTransmission(Matrix_Verkeerslicht); 
  Wire.write(0x00);
  Wire.write(twee[0]);
  Wire.write(0x00);
  Wire.write(twee[1]);
  Wire.write(0x00);
  Wire.write(twee[2]);
  Wire.write(0x00);
  Wire.write(twee[3]);
  Wire.write(0x00);
  Wire.write(twee[4]);
  Wire.write(0x00);
  Wire.write(twee[5]);
  Wire.write(0x00);
  Wire.write(twee[6]);
  Wire.write(0x00);
  Wire.write(twee[7]);
  Wire.write(0x00);
  Wire.endTransmission();
}

void Drie(){
  byte drie[] = {
    0x1F, 0x1F, 0x03, 0x1F , 0x1F , 0x03 , 0x1F, 0x1F      };
  Wire.beginTransmission(Matrix_Verkeerslicht); 
  Wire.write(0x00);
  Wire.write(drie[0]);
  Wire.write(0x00);
  Wire.write(drie[1]);
  Wire.write(0x00);
  Wire.write(drie[2]);
  Wire.write(0x00);
  Wire.write(drie[3]);
  Wire.write(0x00);
  Wire.write(drie[4]);
  Wire.write(0x00);
  Wire.write(drie[5]);
  Wire.write(0x00);
  Wire.write(drie[6]);
  Wire.write(0x00);
  Wire.write(drie[7]);
  Wire.write(0x00);
  Wire.endTransmission();
}

void Vier(){
  byte vier[] = {
    0x03, 0x03, 0x03, 0x3F, 0x3F,0x33, 0x33, 0x33      };
  Wire.beginTransmission(Matrix_Verkeerslicht); 
  Wire.write(0x00);
  Wire.write(vier[0]);
  Wire.write(0x00);
  Wire.write(vier[1]);
  Wire.write(0x00);
  Wire.write(vier[2]);
  Wire.write(0x00);
  Wire.write(vier[3]);
  Wire.write(0x00);
  Wire.write(vier[4]);
  Wire.write(0x00);
  Wire.write(vier[5]);
  Wire.write(0x00);
  Wire.write(vier[6]);
  Wire.write(0x00);
  Wire.write(vier[7]);
  Wire.write(0x00);
  Wire.endTransmission();
}

void Vijf(){
  byte vijf[] = {
    0x3f, 0x3f, 0x03, 0x3F, 0x3F,0x30, 0x3f, 0x3f      };
  Wire.beginTransmission(Matrix_Verkeerslicht); 
  Wire.write(0x00);
  Wire.write(vijf[0]);
  Wire.write(0x00);
  Wire.write(vijf[1]);
  Wire.write(0x00);
  Wire.write(vijf[2]);
  Wire.write(0x00);
  Wire.write(vijf[3]);
  Wire.write(0x00);
  Wire.write(vijf[4]);
  Wire.write(0x00);
  Wire.write(vijf[5]);
  Wire.write(0x00);
  Wire.write(vijf[6]);
  Wire.write(0x00);
  Wire.write(vijf[7]);
  Wire.write(0x00);
  Wire.endTransmission();
}

void Zes(){
  byte zes[] = {
    0x3f, 0x3f, 0x33, 0x3f, 0x3F,0x30, 0x3f, 0x3f      };
  Wire.beginTransmission(Matrix_Verkeerslicht); 
  Wire.write(0x00);
  Wire.write(zes[0]);
  Wire.write(0x00);
  Wire.write(zes[1]);
  Wire.write(0x00);
  Wire.write(zes[2]);
  Wire.write(0x00);
  Wire.write(zes[3]);
  Wire.write(0x00);
  Wire.write(zes[4]);
  Wire.write(0x00);
  Wire.write(zes[5]);
  Wire.write(0x00);
  Wire.write(zes[6]);
  Wire.write(0x00);
  Wire.write(zes[7]);
  Wire.write(0x00);
  Wire.endTransmission();
}


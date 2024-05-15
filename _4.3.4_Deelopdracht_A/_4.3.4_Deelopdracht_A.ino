#define RED 4
#define YELLOW 3
#define GREEN 2
#define aantalPinnetjes 3
#define TEMP 0
#define LICHT 1
#define DRUKKNOP 5
#define MIN_TEMP 0
#define MAX_TEMP 100

int pinnenLeds[] ={GREEN,YELLOW,RED};
const int interval = 2000;
long previousMillis = 0;
bool ledstate = 1;
float temperatuur;
float lux;

void setup() {
  Serial.begin(9600);
  for(int i =0 ; i < aantalPinnetjes;i++){
  pinMode(pinnenLeds[i], OUTPUT);
  pinMode(DRUKKNOP, INPUT);
  }
 


}

void loop() {
temperatuur = (22.8/698.0) * (float)analogRead(0);
lux = (482/893) * (float)analogRead(1);
 unsigned long currentMillis = millis();
 if(currentMillis-previousMillis > interval){
  previousMillis = currentMillis;
  Serial.print("TEMP : ");
 Serial.println(temperatuur);
 Serial.print("LUX : ");
 Serial.println(analogRead(LICHT));
 Serial.print("Knopje : ");
 Serial.println(digitalRead(DRUKKNOP));
 }

 digitalWrite(bepaalWelkeLed(temperatuur),HIGH);
}

int bepaalWelkeLed(float temperatuur){
if(temperatuur> MIN_TEMP && temperatuur < MAX_TEMP){
  return GREEN;
}
else if(temperatuur < MIN_TEMP){
  return YELLOW;
}
else if(temperatuur > MAX_TEMP){
  return RED;
}
}


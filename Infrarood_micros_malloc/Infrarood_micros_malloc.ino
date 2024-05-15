int *test;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(250);
  Serial.println("1:  ");
  Serial.println(micros());
  test = (int*)malloc(sizeof(int));
  Serial.println(micros());
  Serial.println(" --> 1");
  free(test);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void setup()
{
  Serial.begin(9600);
  int a;
  char b='1';             
 
  a=b-'0';
  Serial.print("Value of a is \t");
  Serial.println(a);
  
  char c = char(a)+'0';
  Serial.print("Value of c is \t");
  Serial.println(c);
}
void loop()
{

}

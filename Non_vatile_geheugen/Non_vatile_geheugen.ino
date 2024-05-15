#include <EEPROM.h>
void setup()
{
  Serial.begin(9600);
   for (int i = 0; i < 26; i++){
     EEPROM.write(i, i+65);
     Serial.print(char(EEPROM.read(i)));
   }
}
void loop()
{
}

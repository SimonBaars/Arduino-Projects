/*
  LED matrix
  I2C address is 70
  A4 SDA
  A5 CLK
 */
 
#include <Wire.h>
int i2c_LEDMatrix = 0x70;

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
}

// the loop routine runs over and over again forever:
void loop() {
  Wire.beginTransmission(i2c_LEDMatrix); 
  Wire.write(0x00);  //start of display
    Wire.write(B00011110);               
  Wire.write(0x00);               
  Wire.write(B00100001);               
  Wire.write(0x00);               
  Wire.write(B11001100);               
  Wire.write(0x00);               
  Wire.write(B11010010);               
  Wire.write(0x00); 
  Wire.write(B11000000);               
  Wire.write(0x00);               
  Wire.write(B11010010);               
  Wire.write(0x00);               
  Wire.write(B00100001);               
  Wire.write(0x00);               
  Wire.write(B00011110);               
  Wire.write(0x00); 
  delay(1000);
  Wire.endTransmission();    
  
  Wire.beginTransmission(i2c_LEDMatrix); 
  Wire.write(0x00);  //start of display
  Wire.write(B00011110);               
  Wire.write(0x00);               
  Wire.write(B00100001);               
  Wire.write(0x00);  
Wire.write(B11000000);               
  Wire.write(0x00);       
  Wire.write(B11010010);               
  Wire.write(0x00);               
  Wire.write(B11001100);               
  Wire.write(0x00);           
  Wire.write(B11010010);               
  Wire.write(0x00);               
  Wire.write(B00100001);               
  Wire.write(0x00);               
  Wire.write(B00011110);               
  Wire.write(0x00); 
  delay(1000);
  Wire.endTransmission();    
}

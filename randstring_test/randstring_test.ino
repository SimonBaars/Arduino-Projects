/*************************************************** 
 * This is a library for our I2C LED Backpacks
 * 
 * Designed specifically to work with the Ad+afruit LED Matrix backpacks 
 * ----> http://www.adafruit.com/products/872
 * ----> http://www.adafruit.com/products/871
 * ----> http://www.adafruit.com/products/870
 * 
 * These displays use I2C to communicate, 2 pins are required to 
 * interface. There are multiple selectable I2C addresses. For backpacks
 * with 2 Address Select pins: 0x70, 0x71, 0x72 or 0x73. For backpacks
 * with 3 Address Select pins: 0x70 thru 0x77
 * 
 * Adafruit invests time and resources providing this open source code, 
 * please support Adafruit and open-source hardware by purchasing 
 * products from Adafruit!
 * 
 * Written by Limor Fried/Ladyada for Adafruit Industries.  
 * BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_8x8matrix matrix[2] = {Adafruit_8x8matrix(),Adafruit_8x8matrix()};

String tePrintenText("  Ha Kris  ");

void setup() {

  Serial.begin(9600);
  Serial.println("8x8 LED Matrix Test");
  for(int i = 0; i<2; i++){
    //matrix[i] =Adafruit_8x8matrix();
    matrix[i].begin(0x70+i);  // pass in the address
  }
}


void loop() {
  ledMatrix1();
  //ledMatrix2();
}

void ledMatrix1(){
  for(int i = 0; i<2; i++){
    matrix[i].clear();
    matrix[i].setRotation(2);
    matrix[i].setTextSize(1);
    matrix[i].setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
    matrix[i].setTextColor(LED_ON);
  }
  for (int8_t x=0; x>=-80; x--) {
    for(int i = 0; i<2; i++){
      matrix[i].clear();
      matrix[i].setCursor(x,0);
      if(i==0){
      matrix[i].print(randstring(10));
      } else {
        matrix[i].print(randstring(10));
        delay(random(100));
      }
      matrix[i].writeDisplay();
      if(i==0){
      }
    }
    delay(0);
  }
}

char randstring(size_t length) {

    static char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.-#'?!";        
    char randomString = NULL;

    if (length) {
        randomString = malloc(sizeof(char) * (length +1));

        if (randomString) {            
            for (int n = 0;n < length;n++) {            
                int key = rand() % (int)(sizeof(charset) -1);
                randomString[n] = charset[key];
            }

            randomString[length] = '\0';
        }
    }

    return randomString;
}

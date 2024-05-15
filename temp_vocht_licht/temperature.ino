#include <OneWire.h>
#define temppin 6

OneWire ds(temppin);  // on pin 10

float readTemperature() {
  int HighByte, LowByte, TReading, SignBit, Tc_100, Whole, Fract;
  byte i;
  byte present = 0;
  byte data[12];
  byte addr[8];

  ds.reset_search();
  if ( !ds.search(addr)) {
    Serial.println("No more addresses for the temperature sensor!");
    ds.reset_search();
    delay(100);
    return 0;
  }

  if ( OneWire::crc8( addr, 7) != addr[7]) {
    Serial.println("Temperature sensor is not recognized!");
    //return;
  }

  ds.reset();
  ds.select(addr);
  ds.write(0x44,1);         // start conversion, with parasite power on at the end

  // we might do a ds.depower() here, but the reset will take care of it.

  present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE);         // Read Scratchpad

  for ( i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = ds.read();
  }
  OneWire::crc8( data, 8);
  LowByte = data[0];
  HighByte = data[1];
  TReading = (HighByte << 8) + LowByte;
  SignBit = TReading & 0x8000;  // test most sig bit

  Tc_100 = (6 * TReading) + TReading / 4;    // multiply by (100 * 0.0625) or 6.25
  
  return Tc_100 / 100.0;
}


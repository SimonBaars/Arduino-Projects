#include "temperature.h"
#include "humidity.h"
#include "misc.h"
#include "config.h"

OneWire * ds = new OneWire(TEMPPIN);

float readTemperature() {
  int HighByte, LowByte, TReading, SignBit, Whole, Fract;
  float temp;
  byte i;
  byte present = 0;
  byte data[12];
  byte addr[8];

  ds->reset_search();
  ds->search(addr);

  OneWire::crc8( addr, 7);

  ds->reset();
  ds->select(addr);
  ds->write(0x44, 1);        // start conversion, with parasite power on at the end

  present = ds->reset();
  ds->select(addr);
  ds->write(0xBE);                      // Read Scratchpad

  for ( i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = ds->read();
  }
  
  OneWire::crc8( data, 8);
  LowByte = data[0];
  HighByte = data[1];
  TReading = (HighByte << 8) + LowByte;
  SignBit = TReading & 0x8000;  // test most sig bit

  temp = ((6 * TReading) + TReading / 4) / 100.0;    // multiply by (100 * 0.0625) or 6.25 and dividy it by 100

  if (temp > float(readDHTtemperature()) + tempmargindegrees || temp < float(readDHTtemperature()) - tempmargindegrees) 
    return TEMP_OUT_OF_BOUND;
  else if (temp <= 0) 
    return INVALID_TEMP_LM35;
  
  return roundAt(temp, 0.5);
}

#ifndef _CRC16_H
#define _CRC16_H

#define CRC_INIT 0xFFFF

/*
 * Derived from CRC algorithm for JTAG ICE mkII, published in Atmel
 * Appnote AVR067.  Converted from C++ to C.
 */
extern unsigned short crcsum(const unsigned char* message,
                             unsigned long length,
                             unsigned short crc);
/*
 * Verify that the last two bytes is a (LSB first) valid CRC of the
 * message.
 */
extern int crcverify(const unsigned char* message,
                     unsigned long length);

#endif

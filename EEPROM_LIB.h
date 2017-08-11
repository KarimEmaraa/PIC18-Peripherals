/* 
 * File:   EEPROM_LIB.h
 * Author: karim
 *
 * Created on January 19, 2017, 1:36 PM
 */

#ifndef EELIB
#define  EELIB
#include <xc.h>

void write_EEPROM(int address,unsigned char data);
char read_EEPROM(int address);
#endif

/* 
 * File:   ROM_LIB.h
 * Author: karim
 *
 * Created on January 19, 2017, 7:31 PM
 */

#ifndef ROMLIB

#define ROMLIB
#include <xc.h>

void write_ROM(unsigned short long address, char * data,unsigned char size);
void erase_ROM(unsigned short long address);
char read_ROM(unsigned short long address);
#endif
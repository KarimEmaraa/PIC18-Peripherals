/* 
 * File:   SPI_LIB.h
 * Author: karim
 *
 * Created on January 31, 2017, 2:19 AM
 */

#ifndef SPILIB
#define SPILIB
#include <xc.h>

#endif

//Master parameters
#define CE      LATC0                    //Chip enable bit "negative logic
#define TMR2    0x03                     //use TMR2 output/2 for SCK   
#define FOSC64  0x02                     //uses Fosc/64 for SCK
#define FOSC16  0x01                     //uses Fosc/16 for SCK
#define FOSC4   0x00                     //uses Fosc/4 for SCK  

//Clock phase
#define ACTtoIdle   0x40                 //active to idle transsmission   
#define IdletoACT   0x00                 //idle to active transmission

//Master and slave Parameters
#define CPOLH   0x10                     //Clock polarity is high
#define CPOLL   0x00                     //Clock polarity is low

//Slave Parameters
#define SSPIN   0x04                     //SS pin is used.
#define NSSPIN  0x05                     //SS pin is used as I/O "not used"


void SPI_Minit(unsigned char SCK,unsigned char CKPOL,unsigned char CKPHA);                //Master initialize
void SPI_Sinit(unsigned char SSpin,unsigned char CKPolarity);           //Slave initialize  
unsigned char SPI_sendSB(unsigned char address,unsigned char data);     //single byte transmit/receive
unsigned char SPI_sendMB(unsigned char address,unsigned char * data, unsigned char noBytes);//Multibyte transmit "counts from 1"
void SPI_recMB(unsigned char address,unsigned char * data,unsigned char noBytes);    //Mitlibyte receiving 

#endif
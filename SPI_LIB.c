
#include "SPI_LIB.h"

void SPI_Minit(unsigned char SCK,unsigned char CKPOL,unsigned char CKPHA)
{
    TRISC &= 0xD6;               //CE ,SCK and SDO are outputs rest is inputs
    SSPCON1 = 0x20|SCK|CKPOL;          //Enable SSP,clock polarity idle state = CKPOL and SCK
    SSPSTAT |= CKPHA;            //CLK Phase is CKPHE
}
void SPI_Sinit(unsigned char SSpin,unsigned char CKPolarity)
{
    TRISC &= 0xDE;              //CE, SDO outputs and SDI AND SCK as inputs
    SSPCON1 = 0x20|CKPolarity|SSpin;    //enable SSP and set slave and polarity as paramters
}
unsigned char SPI_sendSB(unsigned char address,unsigned char data)
{   
    CE = 0;                                //enable slave
    SSPBUF = address;                      //load buffer with address
    while(!SSPSTATbits.BF);                //wait to finish transmitting
    SSPBUF = data;                         //load buffer with data
    while(!SSPSTATbits.BF);
    CE = 1;                                //disable slave
    return SSPBUF;
}
unsigned char SPI_sendMB(unsigned char address,unsigned char * data, unsigned char noBytes)
{
    CE = 0;                                //enable slave
    SSPBUF = address;                      //load buffer with address
    while(!SSPSTATbits.BF);                //wait to finish transmitting
    for(char i = 0; i < noBytes; i++)
    {
        SSPBUF = data[i];               
        while(!SSPSTATbits.BF); 
    }
    CE = 1;
    return SSPBUF;
}
void SPI_recMB(unsigned char address,unsigned char * data,unsigned char noBytes)
{
    CE = 0;
    SSPBUF = address;                      //load buffer with address
    while(!SSPSTATbits.BF);                //wait to finish transmitting
    for (char i = 0; i < noBytes;i++)
    {
        SSPBUF = address;
        while(!SSPSTATbits.BF);
        data[i] = SSPBUF;
    }
    CE = 1;
}
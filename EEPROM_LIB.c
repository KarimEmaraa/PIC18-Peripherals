
#include "EEPROM_LIB.h"
void write_EEPROM(int address,unsigned char data)
{
    if(address <= 0x3FF)
    {
        while(EECON1bits.WR);                       //stay here if there is a write operation.
        EEADR = address & 0x0FF;                    //load lower byte in EEADR 
        EEADRH = (address>>8) & 0x3;                   //load higher 2 bits in EEADRH
        EEDATA = data;                              //load data in EEDATA register
        EECON1 = 0x04;                              //EEPGD = 0(access EEPROM),CFGS=0,(access ROM/EEPROM),WREN = 1  
        INTCONbits.GIE = 0;                         //Disable all interrupts for sure.
        EECON2 = 0x55;
        EECON2 = 0xAA;                              //this is a MUST sequence
        EECON1bits.WR = 1;                          //start long write cycle
        NOP();                                      //for proper writing operation.
        EECON1bits.WREN = 0;                        //Disable writing  
    }
}

char read_EEPROM(int address)
{
    while(EECON1bits.WR);                           //Stay here if there a write cycle is operation
    if(address <= 0x3FF)
    {
        EEADR = address & 0x0ff;                    //Load lower address
        EEADRH = (address>>8) & 0x3;                   //load higher 2 bits.
        EECON1 = 0x01;                              //EEPGD = 0, CFGS = 0 (access eeprom), Enable RD = 1 (READ)
    }
    return EEDATA;
}

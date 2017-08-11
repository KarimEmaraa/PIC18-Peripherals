
#include "ROM_LIB.h"
void write_ROM(unsigned short long address, char * data,unsigned char size)
{
    while(EECON1bits.WR);                                     //Stay here if there is a write opertation.
    if(size <= 64 && address <= 0xFFC0)                       //this is the 64KB-64 for 18f4620
    {                                                         //because writing is done in 64bytes blocks
        TBLPTRL = address & 0x00FF;                           //LOAD TBLPTR Register
        TBLPTRH = (address>>8) & 0xFF;
        TBLPTRU = (address>>16)& 0xFF;
        for(unsigned char i = 0; i<size; i++)                 //iterate through array
        {
            TABLAT = data[i];
            if(TBLPTRL != (address)& 0x00FF)                  //TABLAT when loaded it resets the pointer.
            {                                                 //BUG^    
                TBLPTRL = address & 0x00FF;
                TBLPTRL += i;
                TBLPTRH = (address>>8) & 0xFF;
                TBLPTRU = (address>>16)& 0xFF;
            }
            asm("TBLWT*+");                                  //Write to hidden registers an hit increment.
        }
        TBLPTRL = address & 0x0000FF;                        //reload TBLPTR bec it's modified
        TBLPTRH = (address>>8) & 0xFF;
        TBLPTRU = (address>>16)& 0xFF;
        EECON1 = 0x84;                                       //EEPGD = 1 CFGS = 1(access ROM)
        INTCONbits.GIE = 0;                                  //WREN = 1 (enable write cycle)
        EECON2 = 0x55;                                       //disable interrupts.
        EECON2 = 0xAA;                                       //THIS SEQUENCE IS A MUST.
        EECON1bits.WR = 1;                                   //start of write cycle
        NOP();
        EECON1bits.WREN = 0;                              
    }
}

void erase_ROM(unsigned short long address)
{
    while(EECON1bits.WR);                           //stay here if there is a write operation.                         
    if(address <= 0xFFC0)                           //64KB-64
    {
        TBLPTRL = address & 0x0000FF;               //load TBLPTR with start address of 64 byte block
        TBLPTRH = (address>>8) & 0xFF;
        TBLPTRU = (address>>16)& 0xFF;
        EECON1 = 0x94;                              //EEPGD and CFGS (ROM ACCESS),WREN = 1, FREE = 1(ERASE BIT))
        INTCONbits.GIE = 0;                         //disable interrupts and apply the sequence.
        EECON2 = 0x55;
        EECON2 = 0xAA;
        EECON1bits.WR = 1;                          //start of write cycle
        NOP();
        EECON1bits.WREN = 0;                        //disable write cycle after erase.
    }
}
char read_ROM(unsigned short long address)
{
   while(EECON1bits.WR);
    if(address <= 0xFFC0)
    {   
        TABLAT = 0x00;
        TBLPTRL = address & 0x0000FF;               //LOAD TBLPTR
        TBLPTRH = (address>>8) & 0xFF;
        TBLPTRU = (address>>16)& 0xFF;
        asm("TBLRD*");                              //READ instruction.    
    }
    return TABLAT;                                  //return the data read.     
}
#include "ADC Library.h"
void ADC_init()                                             //USER MUST DEFINE ANALOG PINS IN CODE. (ADCON1)
{
     ADC_PORT_DIR = 0xFF;                                   //set adc port as input
     ADCON2 = 0x91;                                         //Right justified. Tad = 1us > 0.7us(min),Acquisition Time (4*Tad) = 4us > 2.4us (min).
                                                            //FOR 8MHZ ONLY. SEE TABLE 19-1 in Datasheet.
     ADCON0bits.ADON = 1;                                   //Turn ON ADC.
}
unsigned int ADC_Read(unsigned int channel)
{
     if (channel > 13) return 0;
     ADCON0 &= 0x01;                                        //Clear all except LSB (ADON)
     ADCON0 |= channel<<2;                                  //Select desired channel.
     ADCON0bits.GODONE= 1;                                  //Start conversion.
     while(ADCON0bits.GODONE == 1);                         //wait untill conversion is done.
     return ADRES;                                          //return converted value.
}

#include "KeyPad Library.h"


short keynum;                                                                           //hold the pressed key number.

void KP_init()
{
     KEYPAD_PORT_DIR = 0x0F;                                                            //Coloumns (LSB) as inputs, Rows (MSB) as outputs.
     KEYPAD_PORT = 0x00;                                                                //All set to zero.
}

int KP_scan()
{
     short row,press = 0;                                                               //row is for number of iterations , press is flag for pressedkey
     keynum = 0;                                                                        //set keynum = 0
     for(row = 0; row < NUMROW; row++)
     {
         KEYPAD_PORT = (0x10<<row);                                                     //Set ROW1 and then shift on next iteration.
        
         if(COL1 == PRESSED){ __delay_us(800); while(COL1 == PRESSED); return keynum+=1; press = 1;}
         if(COL2 == PRESSED){ __delay_us(800); while(COL2 == PRESSED); return keynum+=2; press = 1;}
         if(COL3 == PRESSED){ __delay_us(800); while(COL3 == PRESSED); return keynum+=3; press = 1;}
         if(COL4 == PRESSED){ __delay_us(800); while(COL4 == PRESSED); return keynum+=4; press = 1;}
                                                                                       //returns the pressed key number.
         keynum +=4;
     }
     if(press == 0) keynum = 0;                                                        //because keynum is always incremented by 4 even if nothing happened
}

char KP_Readbutton()                                                                   //Translates the keynum to valid chars
{
     char key = ',';                                                                   //Translates keynum to valid char.
     while(!((key = KP_scan()) == ','))
     {
        if(keynum == 1) { return key = KEY1; }
        if(keynum == 2) { return key = KEY2; }
        if(keynum == 3) { return key = KEY3; }
        if(keynum == 4) { return key = KEY4; }
        if(keynum == 5) { return key = KEY5; }
        if(keynum == 6) { return key = KEY6; }
        if(keynum == 7) { return key = KEY7; }
        if(keynum == 8) { return key = KEY8; }
        if(keynum == 9) { return key = KEY9; }
        if(keynum == 10){ return key = KEY10;}
        if(keynum == 11){ return key = KEY11;}
        if(keynum == 12){ return key = KEY12;}
        if(keynum == 13){ return key = KEY13;}
        if(keynum == 14){ return key = KEY14;}
        if(keynum == 15){ return key = KEY15;}
        if(keynum == 16){ return key = KEY16;}
     }
     return key;
}
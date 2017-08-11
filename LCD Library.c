#include "LCD Library.h"


 
 void enable_pulse(void)
 {
     LCD_EN = 0;
     __delay_ms(1);
     LCD_EN = 1;
     __delay_ms(1);
 }
 void LCD_WriteCMD(unsigned char command)
 {
     LCD_RS = 0;                                        //Set to command mode
     LCD_PORT &= 0x0F;                                  //Reset high nibble of LCD_Port.     'LCD_Port = LCD_Port & 0000 1111'
     LCD_PORT |= (command&0xF0);                        //send command high nibble to LCD.   'LCD_Port = LCD_Port | (command & 11110000)'
     enable_pulse();                                    //Enable.
     LCD_PORT &= 0x0F;                                  //Reset high nibble of LCD_PORT.
     LCD_PORT |= ((command<<4)&0xF0);                   //send command low nibble to LCD.    'LCD_Port = LCD_Port | (command << 4 & 11110000)'
     enable_pulse();                                    //Enable.
 }
 
 void LCD_WriteChar(unsigned char Data)
 {
     LCD_RS = 1;                                        //Set to Data mode.
     LCD_PORT &= 0x0F;                                  //Reset high nibble of LCD_Port.   'LCD_Port = LCD_Port & 0000 1111'
     LCD_PORT |= (Data&0xF0);                           //send data high nibble to LCD.    'LCD_Port = LCD_Port | (data & 11110000)'
     enable_pulse();                                    //Enable.
     LCD_PORT &= 0x0F;                                  //Reset high nibble of LCD_Port.
     LCD_PORT |= ((Data<<4)&0xF0);                      //send data low nibble to LCD.     'LCD_Port = LCD_Port | (data << 4 & 11110000);
     enable_pulse();                                    //Enable.
 }
 
 void LCD_WriteString(char *s)
 {
     while(*s)
     {
        LCD_WriteChar(*s++);
     }
 }
 
 void LCD_Init(void)
 {
      LCD_PORT_DIR = 0x00;
      __delay_ms(50);                                   //Delay for at least  15ms after power on.

      LCD_PORT = 0x30;                                  //Send function set instruction.    (8 bit mode)
      enable_pulse();
      __delay_ms(5);                                      //Delay for at least 4.1ms.
      
      LCD_PORT = 0x30;                                  //Send function set instruction.    (8 bit mode)
      enable_pulse();
      __delay_us(150);                                  //Delay for at least 100us.
      
      LCD_PORT = 0x30;                                  //Send function set instruction.    (8 bit mode)
      enable_pulse();
      __delay_us(150);                                  //Delay for at least 100us.

      LCD_PORT = 0x28;                                  //Send Function set instruction. 4 bit mode and 2 rows and 5x8 pixels.
      enable_pulse();
      __delay_us(60);                                   //Delay for at least 40uS.

      LCD_WriteCMD(0x01);                               //Screen Clear instrcution.
      __delay_ms(2);                                      //Delay for at least 1.5mS

      LCD_WriteCMD(0x02);                               //Screen Clear instruction.
      __delay_ms(2);                                    //Delay for at least 1.64ms.

      LCD_WriteCMD(0x0C);                               //Send Display switch instruction. D = 1 , C = B = 0.
      __delay_us(100);
      
      LCD_WriteCMD(0x06);                               //Input set instruction. Increment mode and disable shifting.
      __delay_us(60);                                   //Delay for at least 40us.
      
      LCD_WriteCMD(0x02);                               //Screen Clear instruction.
      __delay_ms(2);                                    //Delay for at least 1.64ms.
 }
 
void LCD_SetCursor(unsigned char row,unsigned char coloumn)
{
     LCD_WriteCMD(0x80 | (((row -1) * 0x40) + coloumn - 1 ));
}


void LCD_WriteStringAt(unsigned char row,unsigned char coloumn,char  *S)
{
     LCD_SetCursor(row,coloumn);
     LCD_WriteString(S);
}

void LCD_WriteCharAt(unsigned char row,unsigned char coloumn,char Data)
{
     LCD_SetCursor(row,coloumn);
     LCD_WriteChar(Data);
}
void LCD_CustomChar(unsigned char row, unsigned char coloumn,char const *character,unsigned char location)
{     
      unsigned int count;
      if(location < 8)
      {
         LCD_WriteCMD(0x40 + location * 8);             //Write in 'location' of CGRAM
         for(count = 0; count < 8; count++)
            LCD_WriteChar(character[count]);            //Fill data byte by byte
         LCD_WriteCharAt(row,coloumn,0x00 + location);  //Print
      }
 }
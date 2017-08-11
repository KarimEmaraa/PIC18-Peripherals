
#ifndef LCDLIB
#define LCDLIB
#include <xc.h>


#define LCD_RS                LATCbits.LATC0
#define LCD_EN                LATCbits.LATC1                              //RW PIN SHOULD BE CONNECTED TO GROUND
#define LCD_RS_DIR            TRISCbits.RB0
#define LCD_EN_DIR            TRISCbits.RB1

#define LCD_PORT              LATC
#define LCD_PORT_DIR          TRISC


//Instructions

#define DISPLAY_SHIFT_RIGHT           0x1C
#define DISPLAY_SHIFT_LEFT            0x18
#define CURSOR_SHIFT_RIGHT            0x14
#define CURSOR_SHIFT_LEFT             0x10
#define DISPLAY_OFF                   0x08
#define DISPLAY_ON                    0x0C
#define CURSOR_ON_BLINK               0x0D
#define CURSOR_OFF                    0x0E
#define CURSOR_HOME                   0x02
#define CLEAR_ALL                     0x01                                      //INCLUDING CGRAM.



void enable_pulse(void);
void LCD_Init(void);
void LCD_WriteCMD(unsigned char command);
void LCD_WriteChar(unsigned char Data);
void LCD_WriteString(char  *s);
void LCD_SetCursor(unsigned char row,unsigned char coloumn);
void LCD_WriteStringAt(unsigned char row,unsigned char coloumn,char *S);
void LCD_WriteCharAt(unsigned char row,unsigned char coloumn,char Data);
void LCD_CustomChar(unsigned char row, unsigned char coloumn, char const *character,unsigned char location);

#endif
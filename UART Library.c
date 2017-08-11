#include "UART Library.h"

void UART_init(int baudrate,short mode,short speed)               //refer to datasheet to check the baudrate is compitable with Fosc.
{
   int var;
   if((!mode) && (!speed))
   {
          TXSTAbits.BRGH = LOW_SPEED;                             //Slow speed baud rate.
          BAUDCONbits.BRG16 = mode_8bit;                          //SPBRG only is used. SPBRGH value ignored.
          SPBRG = ((FOSC/baudrate)/64) - 1;
   }
   else if((!mode) && speed)
   {
          TXSTAbits.BRGH = HIGH_SPEED;                            //High speed baud rate.
          BAUDCONbits.BRG16 = mode_8bit;                          //SPBRG only is used. SPBRGH value ignored.
          SPBRG = ((FOSC/baudrate)/16) - 1;
   }
   else if(mode && (!speed))
   {
         TXSTAbits.BRGH = LOW_SPEED;                              //LOW speed baud rate.
         BAUDCONbits.BRG16 = mode_16bit;                          //SPBRG and SPBRGH is used.
         var = ((FOSC/baudrate)/16) - 1;
         SPBRG = var;                                             //low byte in SPBRG.
         SPBRGH = var>>8;                                         //high byte in SPBRGH.
   }
   else
   {
         TXSTAbits.BRGH = HIGH_SPEED;                             //High speed baud rate.
         BAUDCONbits.BRG16 = mode_16bit;                           //SPBRG and SPBRGH is used.
         var =  ((FOSC/baudrate)/4) - 1;
         SPBRG = var;                                             //low byte in SPBRG.
         SPBRGH =var>>8;                                          //high byte in SPBRGH.
   }

   TXSTAbits.SYNC = 0;                                            //Asynchronous mode.
   RCSTAbits.SPEN = 1;                                            //enable serial port.
   TXSTAbits.TXEN = 1;                                                  //Enable transmission.
   RCSTAbits.CREN = 1;                                                  //Enable continous receive.
}

void UART_WriteChar(char msg)
{
   while(!TRMT);                                                  //Wait for TSR to be empty.
   __delay_us(850);                                               //Delay before loading TXREG.
   TXREG = msg;                                                   //LOAD TXREG with the next data;
}

void UART_WriteStr(char const *msg)
{
   int counter;
   for(counter = 0; msg[counter] != '\0';counter++)
   {
          UART_WriteChar(msg[counter]);                           //Send string charachter by charachter.
   }
}

char UART_ReadChar()
{
   while(!RCIF);                                                  //Wait for RSR to be empty.
   return RCREG;                                                  //return recieved data.
}

void UART_ReadStr(char *output,short length)
{
   int counter;
   for(counter = 0; counter < length; counter++)
   {
      output[counter] = UART_ReadChar();                          //read charachter by charachter
   }
}

void UART_Reset()
{
   RCSTAbits.CREN = 0;                                                  //Resets CREN when error occurs.             //Framing Error (FERR = 1), Overrun Error(OERR = 1)
   __delay_us(500);                                               //Framing Error (FERR = 1) OR Overrun Error(OERR = 1)
   RCSTAbits.CREN = 1;
}
int UART_DataReady()
{
   return !(RCSTAbits.FERR);                                            //Check if data is received correctly.
}
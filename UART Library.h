/* 
 * File:   SPI_LIB.h
 * Author: karim
 *
 * Created on January 25, 2017, 2:19 AM
 */

#ifndef UARTLIB

#define UARTLIB
#include <xc.h>


#define mode_16bit              1
#define mode_8bit               0
#define HIGH_SPEED              1
#define LOW_SPEED               0
#define FOSC                    8000000
#define _XTAL_FREQ              8000000

void UART_init(int baudrate,short mode,short speed);
void UART_WriteChar(char msg);
void UART_WriteStr(char const *msg);
char UART_ReadChar();
void UART_ReadStr(char *output , short length);
void UART_Reset();
int UART_DataReady();

#endif
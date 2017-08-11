

#ifndef KEYLIB
#define KEYLIB

#include <xc.h>


#define KEYPAD_PORT            LATD
#define KEYPAD_PORT_DIR        TRISD

#define COL1                   PORTDbits.RD0
#define COL2                   PORTDbits.RD1
#define COL3                   PORTDbits.RD2
#define COL4                   PORTDbits.RD3

#define PRESSED                1
#define NUMROW                 4

#define KEY1                   '7'
#define KEY2                   '8'
#define KEY3                   '9'
#define KEY4                   '/'
#define KEY5                   '4'
#define KEY6                   '5'
#define KEY7                   '6'
#define KEY8                   '*'
#define KEY9                   '1'
#define KEY10                  '2'
#define KEY11                  '3'
#define KEY12                  '-'
#define KEY13                  'd'
#define KEY14                  '0'
#define KEY15                  '='
#define KEY16                  '+'


void KP_init();
int KP_scan();
char KP_Readbutton();

#endif

#ifndef ADCLIB
#define ADCLIB
#include <xc.h>

#define ADC_PORT_DIR            TRISA


void ADC_init();
unsigned int ADC_Read(unsigned int channel);
#endif
#include <msp430.h>
#include "tempSensor.h"

void adc_init(void)
{
    P1SEL0 |= BIT4;
    P1SEL1 |= BIT4;
    ADCCTL0 |= ADCSHT_2 | ADCON;
    ADCCTL1 |= ADCSHP;
    ADCCTL2 &= ~ADCRES; ADCCTL2 |= ADCRES_1;
    ADCMCTL0 |= ADCINCH_4;
}

unsigned int adc_read(void)
{
    ADCCTL0 |= ADCENC | ADCSC;
    while (!(ADCIFG));
    return ADCMEM0;
}

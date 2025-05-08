#include "flameSensor.h"
#include <msp430.h>

void tc_init(void)
{
    P1SEL0 |= BIT3; P1SEL1 |= BIT3;
    ADCCTL0 |= ADCSHT_2 | ADCON;
    ADCCTL1 |= ADCSHP;
    ADCCTL2 &= ~ADCRES; ADCCTL2 |= ADCRES_3;
    ADCMCTL0 |= ADCINCH_3;
}

unsigned int tc_read(void)
{
    ADCCTL0 |= ADCENC | ADCSC;
    while (ADCCTL1 & ADCBUSY);
    return ADCMEM0;
}

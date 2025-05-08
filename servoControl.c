#include "msp430fr2355.h"
#include "servoControl.h"

unsigned int deg2us(unsigned int deg){
    return 500 + deg * (2000 / 180);
}

void setupServo(unsigned int degrees)
{
    unsigned int width_us = deg2us(degrees);
    P5DIR |= BIT0;
    P5SEL0 |= BIT0; P5SEL1 &= ~BIT0;
    TB2CCR0 = 20000 - 1;
    TB2CCTL1 = OUTMOD_7;
    TB2CCR1 = width_us;
    TB2CTL = TBSSEL__SMCLK | MC__UP | TBCLR;
}

#include "msp430fr2355.h"
#include <msp430.h>
#include "servoControl.h"
#include "heatControl.h"
#include "flameSensor.h"
#include "tempSensor.h"
#include "statusLED.h"
#include <stdbool.h>

void gpio_init(void)
{
    P1DIR &= ~BIT2; P1REN |= BIT2; P1OUT |= BIT2;
    P1DIR &= ~BIT3;
    P2DIR |= BIT0 | BIT5; P2OUT &= ~(BIT0 | BIT5);
    P6DIR |= (BIT0 | BIT1 | BIT2); P6OUT |= (BIT0 | BIT1 | BIT2);
}

void system_idle(void)
{
    while (!(P1IN & BIT2)) {
        setStatusLED(7); // white
        setupServo(90);
        __delay_cycles(1000000);
        setStatusLED(0);
        setupServo(0);
        __delay_cycles(1000000);
    }
}

bool system_startup(void)
{
    tc_init();
    unsigned int attempts = 0;

    while(attempts < 3){
        setStatusLED(4); // blue
        P2OUT |= BIT0 | BIT5;
        __delay_cycles(2000000);

        if (tc_read() > 10){
            setupServo(180);
            __delay_cycles(2000000);
            P2OUT &= ~(BIT0 | BIT5);
            return true;
        }

        setStatusLED(6); // cyan
        P2OUT &= ~(BIT0 | BIT5);
        __delay_cycles(10000000);
        attempts++;
    }

    return false;
}

bool system_run(void)
{
    adc_init();
    setStatusLED(2); // green

    while (P1IN & BIT2)
    {
        if (tc_read() < 5) {
            setStatusLED(1); // red
            P2OUT &= ~(BIT0 | BIT5);
            return false;
        }

        unsigned int temp = adc_read();
        setupServo(temp < 500 ? 45 : 90);
        __delay_cycles(1000000);
    }

    return true;
}

void handle_error(void)
{
    setStatusLED(1); // red
    while(1); // lock or implement recovery
}

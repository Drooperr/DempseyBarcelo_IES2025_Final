#include "msp430fr2355.h"
#include <msp430.h>
#include "heatControl.h"
#include "statusLED.h"

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD; // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;     // Unlock GPIO pins

    gpio_init();
    SystemState system_state = STATE_IDLE;

    while (1)
    {
        switch (system_state)
        {
            case STATE_IDLE:
                system_idle();
                system_state = STATE_STARTUP;
                break;

            case STATE_STARTUP:
                if (system_startup())
                    system_state = STATE_RUN;
                else
                    system_state = STATE_ERROR;
                break;

            case STATE_RUN:
                if (!system_run())
                    system_state = STATE_IDLE;
                break;

            case STATE_ERROR:
                handle_error();
                break;
        }
    }
}

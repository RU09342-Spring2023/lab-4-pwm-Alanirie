/*
 * HardwarePWMExample.c
 *
 *  Created on: Feb 18, 2023
 *      Author: Russell Trafford
 *
 *      This example configures P6.0 as a PWM output as controlled by TimerB3.
 *
 *      You will need to connect an external LED or use a scope to see the effect of the Duty Cycle.
 *
 *      You can control the DutyCycle by changing the values in the TB3CCR1 register
 */

#include <msp430.h>

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;                 // Stop WDT

    P6DIR |= BIT0;                     // P6.0 output
    P6SEL0 |= BIT0;
    P6SEL1 &= ~BIT0;                    // P6.0 options select

    // Disable the GPIO power-on default high-impedance mode to activate
    // previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;

    TB3CCR0 = 1000-1;                         // PWM Period
    TB3CCTL1 = OUTMOD_7;                      // CCR1 reset/set
    TB3CCR1 = 300;                            // CCR1 PWM duty cycle
    TB3CTL = TBSSEL__SMCLK | MC__UP | TBCLR;  // SMCLK, up mode, clear TBR

    __bis_SR_register(LPM0_bits);             // Enter LPM0
    __no_operation();                         // For debugger
}






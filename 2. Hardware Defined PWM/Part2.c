/*
 * Part2.c
 *
 *  Created on: Feb 21, 2023
 *      Author: Ayo Overton
 *
 *      This example controls the LED connected to Pin 1.0 by PWM. You can change the DutyCycle Global variable to change the brightness of the LED. You should vary this to see how the brightness can change.
 *      You can also change this in the Variables/Expressions tab in the debugger to experiment with it as well.
 */




#include <msp430.h>

// Global variable to control the duty cycle and hence the brightness
unsigned int dutyCycle = 500;

void main(void)
{
    // Stop watchdog timer
    WDTCTL = WDTPW | WDTHOLD;

    // Set Pin 1.0 as output
    P1DIR |= BIT0;

    // Configure Timer A0 for PWM
    TA0CCR0 = 1000 - 1;         // PWM Period
    TA0CCTL1 = OUTMOD_7;        // Reset/Set output mode
    TA0CCR1 = dutyCycle;        // Initial duty cycle
    TA0CTL = TASSEL_2 + MC_1;   // SMCLK, Up mode

    while (1)
    {
        // Delay for the brightness change to be visible
        __delay_cycles(10000);

        // Increase duty cycle by 100
        dutyCycle += 100;

        // Check for maximum duty cycle value
        if (dutyCycle > 1000)
            dutyCycle = 0;

        // Update the duty cycle
        TA0CCR1 = dutyCycle;
    }
}

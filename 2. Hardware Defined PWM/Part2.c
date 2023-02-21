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



int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;                    // Stop WDT

    gpioInit();                 // Initialize all GPIO Pins for the project

    // Disable the GPIO power-on default high-impedance mode to activate
    // previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;


}


void gpioInit()
{
   // Setting Directions of Pins

       P6DIR |= BIT0;              // Configure P6.0 to an Output
       P6DIR |= BIT1;              // Configure P6.1 to an Output
       P6DIR |= BIT2;              // Configure P6.2 to an Output
}



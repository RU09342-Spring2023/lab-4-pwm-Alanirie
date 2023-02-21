/*
 * Part1.c
 *
 *  Created on: Feb 21, 2023
 *      Author: Ayo Overton
 *
 *      This example controls the LED connected to Pin 1.0 by PWM. You can change the DutyCycle Global variable to change the brightness of the LED. You should vary this to see how the brightness can change.
 *      You can also change this in the Variables/Expressions tab in the debugger to experiment with it as well.
 */




#include <msp430.h>

unsigned short DutyCycle = 12000;


int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;                    // Stop WDT

    gpioInit();                 // Initialize all GPIO Pins for the project

    // Disable the GPIO power-on default high-impedance mode to activate
    // previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;

    while(1)
    {
        if (!(P2IN & BIT3))            // If S2 (P2.3) is pressed, switch to NAND so that it changes on 1
            P6OUT ^= BIT6;          // Toggle P6.6
        if (!(P4IN & BIT1))            // If S1 (P4.1) is pressed
            P1OUT ^= BIT0;          // Toggle P1.0
        __delay_cycles(100000);             // Delay for 100000*(1/MCLK)=0.1s
    }

    // Configure Timer_B
    TB0CTL = TBSSEL_2 | MC_1 | TBCLR | TBIE;      // SMCLK, up mode, clear TBR, enable interrupt

    TB0CCTL1 |= CCIE;                             // Enable TB0 CCR1 Interrupt

    TB0CCR0 = DutyCycle;                          // Set CCR1 to the value to set the duty cycle

    __bis_SR_register(LPM3_bits | GIE);           // Enter LPM3, enable interrupts
    __no_operation();                             // For debugger
}

// Timer0_B3 Interrupt Vector (TBIV) handler
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMER0_B1_VECTOR
__interrupt void TIMER0_B1_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMER0_B1_VECTOR))) TIMER0_B1_ISR (void)
#else
#error Compiler not supported!
#endif
{
    switch(__even_in_range(TB0IV,TB0IV_TBIFG))
    {
        case TB0IV_NONE:
            break;                               // No interrupt
        case TB0IV_TBCCR1:
            P1OUT &= ~BIT0;
            break;                               // CCR1 Set the pin to a 0
        case TB0IV_TBCCR2:
            break;                               // CCR2 not used
        case TB0IV_TBIFG:
            P1OUT |= BIT0;                       // overflow Set the pin to a 1
            break;
        default:
            break;
    }
}


void gpioInit()
{
   // Setting Directions of Pins

       P1DIR |= BIT0;              // Configure P1.0 to an Output
       P6DIR |= BIT6;              // Configure P6.6 to an Output
       P2DIR &= ~BIT3;             // Configure P2.3 to an Input
       P4DIR &= ~BIT1;             // Configure P4.1 to an Input



   // Configuring Pullup Resistors per MSP430FR2355 Family User Guide
   /*
    *   PXDIR | PXREN | PXOUT | I/O Configuration
    *     0       0       X     Input
    *     0       1       0     Input with Pull Down Resistor
    *     0       1       1     Input With Pull Up Resistor
    *     1       X       X     Output
    */

       P2REN |= BIT3;               // Enable Resistor on P2.3
       P2OUT |= BIT3;               // Configures the Resistor on P2.3 to be Pullup

       P4REN |= BIT1;               // Enable Resistor on P4.1
       P4OUT |= BIT1;               // Configures the Resistor on P4.1 to be Pullup

}

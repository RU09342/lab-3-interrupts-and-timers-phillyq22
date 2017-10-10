#include <msp430.h>


/**
 * main.c
 */


int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;       // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;           // Disable the GPIO power-on default high-impedance mode
    P1DIR |= 0x01;                  // configure P1.0 as output
    P5REN |= BIT6;                  // Enabling connect of a resistor to P5.6
    P5OUT |= BIT6;                  // Initializes LED to on, sets the P5.6 Resistor to a pull up resistor


    P5IE |= BIT6;//interrupt enable
    P5IES |= BIT6;//interrupt enable select

    __bis_SR_register(LPM4_bits + GIE);//Low power mode

}
#pragma vector=PORT5_VECTOR
__interrupt void Port_5(void) {
    P1OUT ^= BIT0;//flip LED
    P5IFG &= ~BIT6;// turn off interrupt flag
}

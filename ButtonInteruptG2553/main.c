#include <msp430.h> 


/**
 * main.c
 */
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void) {
    P1OUT ^= BIT0;//flip LED
    P1IFG &= ~BIT3;//Turn off interrupt flag
}

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;       // stop watchdog timer
    P1DIR |= 0x01;                  // configure P1.1 as output
    P1REN |= BIT3;                  // Enabling connect of a resistor to P1.3
    P1OUT |= BIT3;                  // Initializes LED to on, sets the P1.3 Resistor to a pull up resistor

    P1IE |= BIT3;//interrupt enable
    P1IES |= BIT3;//interrupt enable select

    __bis_SR_register(LPM4_bits + GIE);//Low power mode

}

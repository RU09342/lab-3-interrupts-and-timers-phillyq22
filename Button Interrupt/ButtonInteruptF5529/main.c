#include <msp430.h> 


/**
 * main.c
 */


int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;       // stop watchdog timer
    P1DIR |= 0x01;                  // configure P1.0 as output
    P2REN |= BIT1;                  // Enabling connect of a resistor to P5.5
    P2OUT |= BIT1;                  // Initializes LED to on, sets the P1.3 Resistor to a pull up resistor

    P2IE |= BIT1;//interrupt enable
    P2IES |= BIT1;//interrupt enable select

    __bis_SR_register(LPM4_bits + GIE);//Low power mode

}


#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void) {
    P1OUT ^= BIT0;//flip LED
    P2IFG &= ~BIT1;//turn off interrupt flag
}

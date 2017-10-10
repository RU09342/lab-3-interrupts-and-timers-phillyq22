#include <msp430.h> 


/**
 * main.c
 */
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void) {
    P1OUT ^= BIT0;//Flip LED
    P1IFG &= ~BIT1;//Turn off interrupt flag
}

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;       // stop watchdog timer

    PM5CTL0 &= ~LOCKLPM5;           // Disable the GPIO power-on default high-impedance mode
    P1DIR |= 0x01;                  // configure P1.1 as output
    P1REN |= BIT1;                  // Enabling connect of a resistor to P5.5
    P1OUT |= BIT1;                  // Initializes LED to on, sets the P1.3 Resistor to a pull up resistor

    P1IE |= BIT1;//interrupt enable
    P1IES |= BIT1;//interrupt enable select

    __bis_SR_register(LPM4_bits + GIE);//Low power mode

}

#include <msp430.h> 


/**
 * main.c
 */
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void) {
    P1OUT ^= BIT0;//flip LED
    P1IFG &= ~BIT1;//turn off interrupt flag
}

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;       // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;           // Disable the GPIO power-on default high-impedance mode
    P1DIR |= 0x01;                  // configure P1.0 as output
    P1REN |= 0x02;                  // Enabling connect of a resistor to P1.2
    P1OUT |= 0X02;                  // Initializes LED to on, sets the P1.2 Resistor to a pull up resistor

    P1IE |= BIT1;//interrupt enable
    P1IES |= BIT1;//interrupt enable select

    __bis_SR_register(LPM4_bits + GIE);//Low power mode

}

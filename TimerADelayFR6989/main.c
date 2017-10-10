
#include <msp430.h>

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;                     // Stop WDT

    // Configure GPIO
    P1DIR |= BIT0;                                // Set P1.0 as output
    P1OUT |= BIT0;                                // Set P1.0 as output

    P9DIR |= BIT7;                                // Set P9.7 as output
    P9OUT |= BIT7;                                // Set P9.7 as output

    // Disable the GPIO power-on default high-impedance mode to activate
    // previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;

    // Timer1_B3 setup
    TA0CCTL0 = CCIE;                              // TBCCR0 interrupt enabled
    TA0CCR0 = 25000;                              // Set timer0 frequency
    TA0CTL = TASSEL_1 | MC_1;                     // ACLK, up mode
    // Timer1_B3 setup
       TA1CCTL0 = CCIE;                              // TBCCR0 interrupt enabled
       TA1CCR0 = 50000;                              // Set timer1 frequency
       TA1CTL = TBSSEL_1 | MC_1;                     // ACLK, up mode

    __bis_SR_register(LPM0_bits | GIE);           // Enter LPM0 w/ interrupt
}

// Timer B1 interrupt service routine
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer0_A0_ISR(void)

{
        P9OUT ^= BIT7;// Flip LED on Timer0
}
// Timer B1 interrupt service routine
#pragma vector = TIMER1_A0_VECTOR
__interrupt void Timer1_A0_ISR(void)

{
        P1OUT ^= BIT0;//Flip LED on Timer1
}

#include <msp430.h>
unsigned int hz;
int start;
int end;
int flag = 0;

int main(void)
{

    WDTCTL = WDTPW | WDTHOLD;                     // Stop WDT

    // Configure GPIO
    P1DIR |= BIT0;                                // Set Port 1 bit 0 as direction of output
    P1OUT |= BIT1;                                // Set button at port 1 bit 1 as output

    P1REN |= BIT1; // enable register
    P1IE |= BIT1; // interrupt enable
    P1IES |= BIT1; //falling edge
    P1OUT |= BIT1; //turn on Bit 1 of Port 1
    P1IFG &= ~BIT1; // Turn off interrupt flags

    PM5CTL0 &= ~LOCKLPM5;

    // Disable the GPIO power-on default high-impedance mode to activate
    // previously configured port settings

    // Timer1_B3 setup
    TB0CCTL0 = CCIE;                              // TBCCR0 interrupt enabled
    TB0CCR0 = 205;// set to 20Hz
    hz = 205;// increment value for CCR0
    TB0CTL = TBSSEL_1 + MC_2 + ID_3;                     // ACLK, continuous mode, 32768/8 = 4096 Hz


    __bis_SR_register(GIE);   // Enable interrupt, not LPM
    while(1)
    {
        if(flag)
        {
            flag = 0;
            if(end <= start)// account for overflow
            {
                TB0CCR0 = 65535 - start + end + TB0R; // account for current timer value to start immediately
                hz = 65535 - start + end;             // update the increment value
            }
            else
            {
                TB0CCR0 = end-start+TB0R;
                hz = end - start;
            }
        }

    }
}

//button interrupt
#pragma vector = PORT1_VECTOR
__interrupt void Port1(void)
{
    if(P1IES & BIT1)
    {
        start = TB0R;//Time that the button was pressed
    }
    else
    {
        end = TB0R;//time that the button was released
        flag = 1;//turn off flag
    }
    P1IES ^= BIT1;//checking for falling edge and rising edge of button press

    P1IFG &= ~BIT1;                 //clear flag

}
// Timer B1 interrupt service routine
#pragma vector = TIMER0_B0_VECTOR
__interrupt void Timer0_B0_ISR(void)

{
        P1OUT ^= BIT0;
        TB0CCR0 += hz;//increment CCR0
}

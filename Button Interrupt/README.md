# Button Interrupt

##Explanation

Philip Quinn: Interrupts were used to toggle LEDs instead of checking the changing bits out of buttons. Forcing the processor to continuosuly check to see if something has changed is an easy way to waist power and energy of a processor. Using interrupts, we can eliminate the need for our processors to continuously do repetitive checks. Using PxIE, an interrupt enable was placed onto any button we expected an interrupt from. PxIES designated which bit to watch a change in. As an example, for the MSP430G2553 P1IES was set to BIT3, which indicated that BIT3 would be high normally, and would cause an interrupt when ~BIT3 occurred, i.e., when the button was pressed. Within the pragma port vector, logic for toggling the LEDs is used. Additionally, clearing the interrupt flag PxIFG was essential after each entrance into the pragma vector; otherwise, the code would execute infinitely.

##Extra Work

Similar to the normal assignment for this portion of the lab, interrupts were used to toggle LEDs; however, this was implemented on 2 buttons and LEDs for the MSP430FR6989. The same idea was implemented a second time for this to be possible, although extra logic needed to be added into the pragma vector to get the proper LED to toggle. By checking which interrupt was on, the proper LED was toggled.
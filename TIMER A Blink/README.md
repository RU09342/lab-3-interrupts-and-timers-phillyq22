# TIMER A Blink
Philip Quinn: Within this lab, timers are used to designate when to toggle an LED as opposed to checking the bits switching from the button. Note: MSP430FR2311 does not have a TimerA, so TimerB was used.

## Explanation
Similar to Lab2 MultiBlink, this project aims at getting two LEDs to blink at different rates; however, this time around Timers are utilized. Within these specific implementations, two timers were used to make the different rates easier to attain. TA1CCR0 and TA0CCR0 were set to two different frequencies in order to attain the two different blinking rates for the green and red LEDs. Both timers were put into up mode, and had their interrupts enabled. Interrupt service routines were used for both timers to blink the LEDs.

#include <avr/io.h>
#include <avr/interrupt.h>

/*
TASK: Blink LED 1 at a rate of 1Hz using the normal mode of Timer0
Calcuation:
16MHz --> 62,5e-9s = 62,5 nanoseconds per Takt
Prescaler = 256 --> 62,5*256 = 16 microseconds per count
Requested Frequency = 1Hz --> Time period = 1s
1s/16microseconds = 62500 counts needed
Timer0 --> 8 Bit timer --> Maximal value is 256 --> So 62500 needs to be factorized in whole numbers smaller than 256
--> 62500 = 250*250
  - In Normal Mode (WGM Bits in TCCR0A/B = 0) initialize timer counter TCNT0 value to 6 and count until default
TOP Value (0xFF = 256) --> i.e. 250 counts. 
  - At overflow, activate interrupt (TOIE0 in TIMSK0 and TOV0 in TIFR0 Bits activated)
  - Within interrupt, intialize a second 'counter' to 0 and increment it by 1. 
  - if counter == 250 --> then reinitialize counter
  - within interrupt, reinitialize TCNT0 to 6, so that we ensure TCNT counts 250 times, and 'counter' also 
  counts 250 times. Together, we get 250*250 = 62500 
*/

void init_LED() {
  DDRB |= (1<<PB5);               //Set Bit5 to Output
  PORTB |= (1<<PB5);              //Set PB5 to High --> Turn off LED1
}

void init_Timer0() {
  TCCR0A = 0b00000000;        //normal mode
  TCCR0B = 0b00000100;        // Prescaler 256
  TCNT0 = 6;                  // Initialize at 6, to have 250 counts until 256
  TIMSK0 |= 0b00000001;       // Interrupt at Overflow --> TOIE0 activated
  TIFR0 |= 0b00000001;        // TOV0 activated
}

int main() {
  init_LED();
  init_Timer0();
  sei();
  while(1) {
    
  }
  return 0;
}


ISR(TIMER0_OVF_vect){         // Timer Interrupt Overflow Vector
  static int counter = 0;
  counter = counter + 1;
  if(counter == 250) {
    PORTB ^=(1<<PB5);         // Toggle LED
    counter = 0;
  }
  TCNT0 = 6;                  // After each overflow, the timer counter should be reset to 6, not to its default 0 valie to ensure we get 250x250=62500 counts, which at 16MHz and Prescaler of 256 give exactly 1s Time period, or 1Hz frequency
  
}

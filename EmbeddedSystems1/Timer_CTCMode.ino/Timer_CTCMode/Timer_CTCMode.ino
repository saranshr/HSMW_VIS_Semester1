#include <avr/io.h>
#include <avr/interrupt.h>

/*
TASK: Blink LED1 at a rate of 4Hz using the CTC mode of Timer0
Calculation:
16MHz --> 62,5e-9s = 62,5 nanoseconds per Takt
Prescaler = 256 --> 62,5*256 = 16 microseconds per count
Requested Frequency = 4Hz --> Time period = 0,25s
0,25s/16microseconds = 15625 counts needed
Timer0 --> 8 Bit timer --> Maximal value is 256 --> So 15625 needs to be factorized in whole numbers smaller than 256
--> 62500 = 125*125
  - in CTC Mode (WGM01 Bit in TCCR0A activated) initialize timer counter TCNT0 value to 0 and count until OCR0A
value instead of default TOP Value (0xFF = 256) --> i.e. OCR0A counts.
  - At Compare Match, activate interrupt (OCIE0A in TIMSK0 and OCF0A in TIFR0 Bits activated)
  - Within interrupt, intialize a second 'counter' to 0 and increment it by 1. 
  - if counter == 125 --> then reinitialize counter
  - within interrupt, reinitialize TCNT0 to 0, so that we ensure TCNT counts 125 times, and 'counter' also 
  counts 125 times. Together, we get 125*125 = 15625 
*/

void init_LED() {
  DDRB |= (1<<PB5);               //Set Bit5 to Output
  PORTB |= (1<<PB5);              //Set PB5 to High --> Turn off LED1
}

void init_Timer0() {
  TCCR0A = 0b00000010;        // CTC mode --> TCNT0 counts until OCR0A and not 0xFF (Default Top in normal mode)
  TCCR0B = 0b00000100;        // Prescaler 256
  TCNT0 = 0;                  // Initialize at 0 --> redundant, not needed?
  OCR0A = 125;                // TCNT0 should count until 125 (to realise 4 Hz --> Time period = 0.25s)
  TIMSK0 |= 0b00000010;       // Interrupt at Compare Match --> OCIE0A activated
  TIFR0 |= 0b00000010;        // OCF0A activated
}

int main() {
  init_LED();
  init_Timer0();
  sei();
  while(1) {
    
  }
  return 0;
}


ISR(TIMER0_COMPA_vect){         // Timer Interrupt Compare Match Vector
  static int counter = 0;
  counter = counter + 1;
  if(counter == 125) {
    PORTB ^=  (1<<PB5);         // Toggle LED
    counter = 0;
  }
  TCNT0 = 0;                  // Redundant?
}

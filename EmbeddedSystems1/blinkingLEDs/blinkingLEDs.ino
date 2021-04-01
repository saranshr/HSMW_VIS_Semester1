#include <avr/io.h>


// Optimierung des Codes anhand macros
#define SET(x,y) (x |= y)
#define CLEAR(x,y) (x &=~ y)
#define INVERT(x,y) (x ^= y)
#define BIT(b) (1<<b)

#define LED1 BIT(5)
#define LED2 BIT(4)
#define LED4 BIT(2)

// Declaration of functions
void Init();
void Blink_LED1();
void Toggle_LED4();
void PauseAn();
void PauseAus();


int main() {
  Init();
  while(1) {           // forever
    Blink_LED1();
    Toggle_LED4();
  }
}

// Definition of functions used in main()

void Init() {
  CLEAR(DDRB, B00111100);
  CLEAR(PORTB, B00111100);
  SET(DDRB, 0x24);      // DDRB |= 0x24;        // setze Bit 2 und 5 im Port B auf Ausgang (LED 1 und 4) --> LEDs 1 and 4 are turned on --> ??1001??
  CLEAR(PORTB, 0x24);     // PORTB &=~ 0x24;      // gib an PortB Pin2 (LED4) und 5 (LED1) 0-Pegel aus --> LED an --> LEDs 1 and 4 remain on --> ??0000?? (? is 1 or 0)
}

void Blink_LED1() {
  SET(PORTB, LED1);    // SET(PORTB, BIT(5));   // SET(PORTB, 0x20); //PORTB |= 0x20;     // setze Bit 5 am PORTB --> Ausgabe 1-Pegel, LED1 aus PORTB = ??1000??
  PauseAus();
  CLEAR(PORTB,LED1);  // CLEAR(PORTB,BIT(5));    // CLEAR(PORTB,0x20); //PORTB &=~ 0x20;     /* lösche Bit 5 --> Ausgabe 0, LED1 aber noch nicht an, weil ohne nächste Anweisung 'Pause()' kommt die Anweisung 'SET() nochmals, der das Bit direkt löscht
  PauseAus(); // --> LED This is needed to turn on the LED1 again

  SET(PORTB, LED1);    // SET(PORTB, BIT(5));   // SET(PORTB, 0x20); //PORTB |= 0x20;     // setze Bit 5 am PORTB --> Ausgabe 1-Pegel, LED1 aus PORTB = ??1000??
  PauseAus();
  CLEAR(PORTB,LED1);  // CLEAR(PORTB,BIT(5));    // CLEAR(PORTB,0x20); //PORTB &=~ 0x20;     /* lösche Bit 5 --> Ausgabe 0, LED1 aber noch nicht an, weil ohne nächste Anweisung 'Pause()' kommt die Anweisung 'SET() nochmals, der das Bit direkt löscht
  PauseAus(); // --> LED This is needed to turn on the LED1 again
}

void Toggle_LED4() {
  INVERT(PORTB, LED4); // PORTB ^= LED4 // PORTB ^= BIT(2);       // PORTB ^= 0x4;       // invertiere Bit 2 in Port B --> LED4 umschalten --> ??000(1)??
//  PauseAus();
/*  SET(PORTB, LED4);    
  Pause();
  CLEAR(PORTB,LED4);  
  Pause(); */
}

void PauseAus() {
  //for (volatile unsigned long i = 0; i < 4000000; i++)  // kurze Pause // 4000000 corresponds to 8 seconds --> 500000 calculations per second --> 0.5MHz --> why 0.5 MHz and not 4MHz?
  for (volatile unsigned long i = 0; i < 200000; i++) 
  
  ;
}

void PauseAn() {
  for (volatile unsigned long i = 0; i < 100000; i++)  // kurze Pause
  ;
}

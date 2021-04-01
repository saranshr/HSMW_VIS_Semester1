#include <avr/io.h>

void initialisierung(){
  /*LEDs (PD2, PD1) als Ausgang*/
  DDRD |= (1<<PD2)|(1<<PD1);

  /*Schalter (PD3) als Eingang mit Pullup Widerstand */
  DDRD &=~ (1<<PD3);
  PORTD |= (1<<PD3);

  /*externer Interrupt INT1 (fuer Schalter) initialisieren
   * steigende Flanke -> ISC11 = 1 und ISC10 = 1*/
  EICRA = ((1<<ISC10) | (1<<ISC11));
  EIMSK = (1<<INT1);  /*INT1 freischalten*/
  EIFR = (1<< INTF1); /* Lösche weitere Interrupts */
  
  /*LEDs ausschalten -> High anlegen, da hierdurch keine Spannungsdifferenz -> kein Stromfluss*/
  PORTD |= (1<<PD2);
  PORTD |= (1<<PD1);

  /*Interrupt freischalten*/
  sei();
}
/*Globale Variable Anzahl, die in ISR veraendert wird*/
volatile unsigned char Anzahl = 0;

int main(){
  initialisierung();

  while(1){
    PORTD ^= (1<<PD1);  /*gruene LED aller 500ms Toggeln lassen -> 1Hz Blinken */
    delay_ms(500);  
  }
  return 1;
}

ISR(INT1_vect){
  Anzahl++;
  if(Anzahl % 10 == 0){
    PORTD ^= (1<<PD2);  /*Rote LED Toggeln, wenn Schalter 10 Mal betaetigt*/
    Anzahl = 0;         /*Anzahl auf Null setzen -> Vermeidung eines Overflows*/
  }  
}

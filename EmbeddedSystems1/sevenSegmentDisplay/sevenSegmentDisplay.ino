#include <avr/io.h>

/*
    Data        Port B.0
    Shiftclock  Port D.7
    Latch       Port D.4
*/

int Muster;
int Stelle;
int Tabelle[11][2];

void InitPorts() {
  DDRB |= (1 << 0);         /* |= 0x01 */
  DDRD |= ((1 << 7) | (1 << 4)); /* |= 0x90 */
  PORTB &= ~ (1 << 0);
  PORTD &= ~ ((1 << 7) | (1 << 4)); /* Anfangswert = Low */
}

void Transformation() {
  /* Transformation Ziffer --> Muster */
  
  /* Erste Spalte mit 0 bis 10 ausfüllen */
  for (int i = 0; i < 11; i++) {
    Tabelle[i][0] = i;
  }
  /* Zweite Spalte mit Muster für jeweilige Ziffer ausfüllen */
  //                hgfedcba
  Tabelle[0][1] = 0b00111111;      /*Display 0*/
  Tabelle[1][1] = 0b00000110;       /*Display 1*/
  Tabelle[2][1] = 0b01011011;       /*Display 2*/
  Tabelle[3][1] = 0b01001111;       /*Display 3*/
  Tabelle[4][1] = 0b01100110;       /*Display 4*/
  Tabelle[5][1] = 0b01101101;       /*Display 5*/
  Tabelle[6][1] = 0b01111101;       /*Display 6*/
  Tabelle[7][1] = 0b00000111;       /*Display 7*/
  Tabelle[8][1] = 0b01111111;       /*Display 8*/
  Tabelle[9][1] = 0b01101111;       /*Display 9*/
  Tabelle[10][1] = 0b10000000;      /*Display '.'*/
}

void shiftBit(int a) {
  /*a hinausschieben, MSB first*/
  /* 8 mal, höchstwertiges Bit ausgeben, Schiebetakt erzeugen,
     'muster' 1 links schieben */
  for (int i = 0; i < 8; i++) {
    if (a & (1 <<   7)) {
      /* Ausgabe 1 an Data */
      PORTB |= (1 << 0);
    } else {
      /* Ausgabe 0 an Data */
      PORTB &= ~(1 << 0);
    }

    /* Schiebetakt */
    PORTD |= (1 << 7);
    PORTD &= ~ (1 << 7);

    /* muster/stelle links schieben */
    a <<= 1;
  }
}


void Anzeige(int x, int pos) {
  /* Angegebenen Ziffer in zugehörigen Muster transformieren */
  Transformation();
  
  /*Damit LEDs anleuchten, müssen die transformierte Werte invertiert werden*/
  for (int i = 0; i < 11; i++) {
    if (i == x) {
      Muster = ~(Tabelle[i][1]);
    }
  }

  /* Die Stelle ist geregelt durch 0bXXXX3210 --> die erste vier Bits definieren die Stelle. D.h. die Einträge 1, 2, 4 und 8 aus der erste Spalte der Tabelle können verwendet werden */
  if (pos == 0) {
    Stelle = Tabelle[1][0];         /* entspricht wert 1 --> 0b0000 0001*/
  } else if (pos == 1) {
    Stelle = Tabelle[2][0];         /* entspricht wert 2 --> 0b0000 0010*/
  } else if (pos == 2) {
    Stelle = Tabelle[4][0];         /* entspricht wert 4 --> 0b0000 0100*/
  } else if (pos == 3) {
    Stelle = Tabelle[8][0];         /* entspricht wert 8 --> 0b0000 1000*/
  }

  /* Muster hinausschieben, MSB first */
  int muster = Muster;              // redundant? Direkt Muster in shiftBit() 
  shiftBit(muster);
  
  /* Stellewahl hinausschieben, MSB first */
  int stelle = Stelle;
  shiftBit(stelle);

  /* Übernahmetakt (LATCH) erzeugen */
  PORTD |= (1 << 4);        // an
  PORTD &= ~ (1 << 4);      // aus
}


int main() {
  InitPorts();
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 11; j++) {
        Anzeige(j, i);
        //for (volatile unsigned long k = 0; k < 500000; k++) 
        for (volatile unsigned long k = 0; k < 100000; k++)
          ;
      }
    } 
//  while (1) {
//    for (int i = 0; i < 4; i++) {
//      for (int j = 0; j < 11; j++) {
//        Anzeige(j, i);
//        //for (volatile unsigned long k = 0; k < 500000; k++) 
//        for (volatile unsigned long k = 0; k < 100000; k++)
//          ;
//      }
//    }
//  }
}

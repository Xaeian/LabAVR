#define __AVR_ATmega328P__
#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>
#include "lib/portx.h"

int main(void)
{
  char x = 2;
  // init()
  DDRD |= 0xFF;

  while (1)
  {
    // loop();
    _delay_ms(100);
    PORTY[0] = 1;
    _delay_ms(100);
    PORTD &= ~(1 << 0);
  }
}
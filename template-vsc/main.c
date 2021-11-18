#define __AVR_ATmega328P__
#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>
#include "lib/portx.h"

#define LED_ON PORTD &= ~(1 << 0)
#define LED_OFF PORTD |= (1 << 0)

char x = 0;

int main(void)
{
  // init();
  PORT_Init();

    PORTY_Sign(0, '1', true);
    PORTY_Sign(1, '0', false);
    PORTY_Sign(2, '1', true);
    PORTY_Sign(3, '1', false);

  while (1)
  {
    PORTX = x++;
    _delay_ms(10);
  }
}
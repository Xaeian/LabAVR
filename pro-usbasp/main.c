#include "main.h"
#include <avr/io.h>
#include <util/delay.h>
#include "lib/uart.h"
#include "lib/port.h"
#include "lib/adc.h"

int main(void)
{
  // init();
  DDRD |= (1 << 3);

  while (1)
  {
    // loop();
    _delay_ms(200);
    PORTD |= (1 << 3);
    _delay_ms(200);
    PORTD &= ~(1 << 3);
  }
}
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
  // init();
  DDRD |= 0xFF;

  while (1) {
    // loop();
    _delay_ms(200);
    PORTD |= (1 << 0);
    _delay_ms(200);
    PORTD &= ~(1 << 0);
  }
}
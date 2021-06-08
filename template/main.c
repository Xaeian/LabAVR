#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
  // initialization
  DDRD |= (1 << 0);
    
  while(1) {
    // main loop
    _delay_ms(200);
    PORTD |= (1 << 0);
    _delay_ms(200);
    PORTD &= ~(1 << 0);
  }
}


#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
  uint8_t value = 1;
  DDRD = 0xFF;
  PORTD = ~value;
  
  while (1) {
    value <<= 1;
    if(!value) {
       value = 1;
    }
    PORTD = ~value;
  }
}
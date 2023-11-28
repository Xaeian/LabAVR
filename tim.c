#include "main.h"
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
  TCCR0B |= (1 << CS02) | (1 << CS01);
  TIMSK0 |= 1<<TOIE0;
  sei();
  TCNT0 = 4;
  
  while (1)
  {
    //value = ADC_Run(A3);
    //SEG7_Int(SEG7_Int);
  }
}


uint8_t timer_aux;

ISR(TIMER0_OVF_vect)
{
  if(timer_aux++ >= 62) {
    // zmiana stanu diody
    timer_aux = 0;
  }
  TCNT0 = 4;
}
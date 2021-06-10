#include <avr/io.h>
#include <avr/interrupt.h>

#define ECR_LEFT 1 // 01
#define ECR_RIGHT 2 // 10

uint8_t ecr_left_right;

int main(void)
{
  uint8_t value = 0;
  
  PORTD = 0x0C;
  PORTB = ~value; DDRB = 0xFF;
  
  EIMSK |= (1 << INT0); // External interrupt 0
  EICRA |= (1 << ISC01) || ( 1 << ISC00 ); // Falling & rising edge
  sei();
  
  while (1)
  {    
    if((ecr_left_right == ECR_LEFT) && (value != 0)) {
      value--;
      ecr_left_right = 0;
    } else if((ecr_left_right == ECR_RIGHT) && (value != 255)) {
      value++;
      ecr_left_right = 0;
    }
    PORTB = ~value;
  }
}

ISR(INT0_vect)
{
  uint8_t state = (~PIND >> 2) & 3;
  if((state == 1)||(state == 2)) { ecr_left_right = ECR_RIGHT; }
  else if ((state == 0)||(state == 3)) { ecr_left_right = ECR_LEFT; }
}
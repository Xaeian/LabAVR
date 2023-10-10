#include "main.h"
#include <avr/io.h>
#include "pwm.h"

//-------------------------------------------------------------------------------------------------

void PWM_Init(uint32_t autoreload)
{
  ICR1 = autoreload;
  DDRB |= (PWM_ENABLE_B << 2) |(PWM_ENABLE_A << 1);
  TCCR1A = (PWM_ENABLE_A << 7)|
           ((PWM_ENABLE_A & PWM_NEGATION_A) << 6)|
           (PWM_ENABLE_B << 5)|
           ((PWM_ENABLE_B & PWM_NEGATION_B) << 4);

  if(PWM_ENABLE_A) {
    if(PWM_NEGATION_A) OCR1A = autoreload;
    else OCR1A = 0;
  }

  if(PWM_ENABLE_B) {
    if(PWM_NEGATION_B) OCR1B = autoreload;
    else OCR1B = 0;
  }

  switch(PWM_MODE) {
    case PWM_Mode_PhaseAndFrequencyCorrect: TCCR1B = (1 << WGM13); break;
    case PWM_Mode_PhaseCorrect: TCCR1B = (1 << WGM13); TCCR1A |= (1 << WGM11); break;
    case PWM_Mode_Fast: TCCR1B = (1 << WGM13) | (1 << WGM12); TCCR1A |= (1 << WGM11); break;
  }

  switch(PWM_PRESCALER) {
    case 1: TCCR1B |= 1; break;
    case 8: TCCR1B |= 2; break;
    case 64: TCCR1B |= 3; break;
    case 256: TCCR1B |= 4; break;
    case 1024: TCCR1B |= 5; break;
  }
}

__inline void PWM_SetA(uint32_t value)
{
  OCR1A = value;
}

__inline void PWM_SetB(uint32_t value)
{
  OCR1B = value;
}

//-------------------------------------------------------------------------------------------------
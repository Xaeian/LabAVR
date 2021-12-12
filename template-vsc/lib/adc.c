#include "main.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "adc.h"

//---------------------------------------------------------------------------------------------------------------------

void ADC_Init()
{
  if (F_CPU / 2 < 200000) ADCSRA |= (1 << ADPS0);
  else if (F_CPU / 4 < 200000) ADCSRA |= (1 << ADPS1);
  else if (F_CPU / 8 < 200000) ADCSRA |= (1 << ADPS1) | (1 << ADPS0);
  else if (F_CPU / 16 < 200000) ADCSRA |= (1 << ADPS2);
  else if (F_CPU / 32 < 200000) ADCSRA |= (1 << ADPS2) | (1 << ADPS0);
  else if (F_CPU / 64 < 200000) ADCSRA |= (1 << ADPS2) | (1 << ADPS1);
  else ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
  ADMUX |= (ADC_VREF << 6);
  ADCSRA |= (1 << ADEN) | (ADC_FREERUN << ADSC) | (ADC_FREERUN << ADATE) | (ADC_FREERUN << ADIE);
}

//---------------------------------------------------------------------------------------------------------------------

void ADC_Mux(uint8_t channel)
{
  ADMUX = (ADMUX & 0xE0) | channel;
}

uint16_t ADC_Run(uint8_t channel)
{
  ADC_Mux(channel);
  ADCSRA |= (1 << ADSC);
  while(ADCSRA & (1 << ADSC));
  return ADC;
}

uint32_t ADC_RunOversample(uint8_t channel, uint16_t count)
{
  uint32_t value = 0;
  int i;
  for(i = 0; i < count; i++) 
    value += (uint32_t)ADC_Run(channel);
  return value;
}

//---------------------------------------------------------------------------------------------------------------------
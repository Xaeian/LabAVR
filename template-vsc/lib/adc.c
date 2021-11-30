#include <avr/io.h>
#include <avr/interrupt.h>
#include "adc.h"

//---------------------------------------------------------------------------------------------------------------------

void ADC_Init()
{
	if (F_CPU / 2 < 200000) ADCSRA |= (1<<ADPS0);
	else if (F_CPU / 4 < 200000) ADCSRA |= (1<<ADPS1);
	else if (F_CPU / 8 < 200000) ADCSRA |= (1<<ADPS1) | (1<<ADPS0);
	else if (F_CPU / 16 < 200000) ADCSRA |= (1<<ADPS2);
	else if (F_CPU / 32 < 200000) ADCSRA |= (1<<ADPS2) | (1<<ADPS0);
	else if (F_CPU / 64 < 200000) ADCSRA |= (1<<ADPS2) | (1<<ADPS1);
	else ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
	ADMUX |= (ADC_VREF << 6);
	ADCSRA |= (1 << ADEN) | (ADC_FREERUN << ADSC) | (ADC_FREERUN << ADATE) | (ADC_FREERUN << ADIE);
}

//---------------------------------------------------------------------------------------------------------------------

void ADC_Mux(char channel)
{
  ADMUX &= 0xE0;
  ADMUX |= channel;
}

uint16_t ADC_Run(char channel)
{
	ADC_Mux(channel);
	ADCSRA |= (1<<ADSC);
	while(ADCSRA & (1<<ADSC));
	return ADC;
}

float ADC_RunFilter(char channel, char filter)
{
	float value = 0;
	for(int i = 0; i < filter; i++) 
		value += (float)ADC_Run(channel);
	return value / filter;
}

//---------------------------------------------------------------------------------------------------------------------
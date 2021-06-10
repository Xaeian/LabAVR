#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>

#include "portx.h"
volatile uint8_t PORTX, PINX, PORTY[4];

//-------------------------------------------------------------------------------------------------

void PORT_Init()
{
	PORTX = 0; PORTY[0] = 0; PORTY[1] = 0; PORTY[2] = 0; PORTY[3] = 0;
	
	PORTB |= (1 << SPI_CS);
	DDRB |= (1 << SPI_SCK) | (1 << SPI_MOSI) | (1 << SPI_CS);
	DDRB &= ~(1 << SPI_MISO);
	SPCR = (1 << SPIE) | (1 << SPE) | (1 << MSTR) | (1 << SPR1) | (1 << SPR0); // Prescaler: 128
	
	PORTB &= ~(1 << SPI_CS);
	SPDR = PORTX;
  sei();
}

__inline void PORT_Stop() { SPCR &= ~(1<<SPIE); }
__inline void PORT_Start() { SPCR |= (1<<SPIE); }
  
void PORTY_Sign(uint8_t position, uint8_t sign, bool dot)
{
	switch(sign) {
		case 0: case '0': PORTY[position] = 0x3F; break;
		case 1: case '1': PORTY[position] = 0x06; break;
		case 2: case '2': PORTY[position] = 0x5B; break;
		case 3: case '3': PORTY[position] = 0x4F; break;
		case 4: case '4': PORTY[position] = 0x66; break;
		case 5: case '5': PORTY[position] = 0x6D; break;
		case 6: case '6': PORTY[position] = 0x7D; break;
		case 7: case '7': PORTY[position] = 0x07; break;
		case 8: case '8': PORTY[position] = 0x7F; break;
		case 9: case '9': PORTY[position] = 0x6F; break;
		case 10: case 'A': PORTY[position] = 0x77; break;
		case 11: case 'B': PORTY[position] = 0x7C; break;
		case 12: case 'C': PORTY[position] = 0x39; break;
		case 13: case 'D': PORTY[position] = 0x5E; break;
		case 14: case 'E': PORTY[position] = 0x79; break;
		case 15: case 'F': PORTY[position] = 0x71; break;
		case '-': PORTY[position] = 0x40; break;
		default: PORTY[position] = 0x00; break;
	}
	PORTY[position] |= (dot << 7);
}

void PORTY_Int(int16_t value)
{
	bool negative = false;
	if(value < 0) {
    value = -value;
    negative = true;
  }
	int box = value;
  
	if(box >= 1000) {
    PORTY_Sign(0, value / 1000, 0);
    value %= 1000; 
  }
	else if((box >= 100) && negative) PORTY_Sign(0, '-', 0);
  else { PORTY_Sign(0, ' ', 0); }
    
	if(box >= 100) {
    PORTY_Sign(1, value / 100, 0); value %= 100;
  }
	else if((box >= 10) && negative) PORTY_Sign(1, '-', 0);
  else PORTY_Sign(1, ' ', 0);
  
	if(box >= 10) {
    PORTY_Sign(2, value / 10, 0);
    value %= 10;
  }
  
	else if(negative) PORTY_Sign(2, '-', 0);
  else { PORTY_Sign(2, ' ', 0); }
	PORTY_Sign(3, value, 0);
}

//---------------------------------------------------------------------------------------------------------------------

uint8_t portx_state;

ISR(SPI_STC_vect)
{
	switch(portx_state)
	{
		case 0: PINX = SPDR;
		case 1: case 2: case 3: SPDR = PORTY[portx_state]; break;
		case 4: PORTB |= (1 << SPI_CS); _delay_us(1); PORTB &= ~(1 << SPI_CS); SPDR = PORTX;
	}
	
	portx_state++;
	if(portx_state > 4) { portx_state = 0; }
}

//---------------------------------------------------------------------------------------------------------------------
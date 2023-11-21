#include "main.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>
#include "port.h"

volatile uint8_t PORTX, PINX, PORTY[4];

//-------------------------------------------------------------------------------------------------

void MYSPI_Init()
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

__inline void MYSPI_Stop() { SPCR &= ~(1<<SPIE); }
__inline void MYSPI_Start() { SPCR |= (1<<SPIE); }
  
void SEG7_Sign(uint8_t position, uint8_t sign, bool dot)
{

}

void SEG7_Error(void)
{
  
}

const uint16_t SEG7_DIV[] = {1000, 100, 10, 1};

void SEG7_Int(int16_t value)
{

}

//-------------------------------------------------------------------------------------------------

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

//-------------------------------------------------------------------------------------------------
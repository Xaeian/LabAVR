#include "main.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "uart.h"

//---------------------------------------------------------------------------------------------------------------------

void UART_Init(uint32_t frequency_bps, uint8_t bits, uint8_t parity, uint8_t stop)
{
  uint32_t ubrr = F_CPU / 16 / frequency_bps - 0.5;
  UBRR0L = ubrr;
  ubrr >>= 8; UBRR0H = ubrr & 0x0F;
  
  if ( bits == 5 );
  else if ( bits == 6 ) UCSR0C |= (1 << UCSZ00);
  else if ( bits == 7 ) UCSR0C |= (1 << UCSZ01);
  else UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
  if ( bits == 9 ) UCSR0B |= (1 << UCSZ02);
  
  if (parity == 0);
  else if (parity == 1) parity |= (1 << UPM01) | (1 << UPM00);
  else parity |= (1 << UPM01);

  if (stop == 2) UCSR0C |= (1 << USBS0);

  UCSR0B |= (1 << RXEN0) | (1 << TXEN0) | ( 1 << RXCIE0);
}

//---------------------------------------------------------------------------------------------------------------------

void UART_Send(char dana)
{
  while (!( UCSR0A & (1<<UDRE0)));
  UDR0 = dana;
}

char UART_Read()
{
  while (!(UCSR0A & (1 << RXC0)));
  return UDR0;
}

void UART_String(char *tekst)
{
  char buffer = *(tekst++);
  while(buffer) {
    UART_Send(buffer);
    buffer = *(tekst++);
  }    
}

void UART_Dec(int value)
{
  char buffer[16];
  UART_String(itoa(value, buffer, 10));
}

void UART_Hex(int value)
{
  char buffer[16];
  UART_String(itoa(value, buffer, 16));
}

void UART_Bin(uint8_t value)
{
  uint8_t bit; int8_t i;
  UART_Send('0'); UART_Send('b');
  for(i = 7; i >= 0; i--) {
    bit = (value >> i) & 1;
    UART_Send(bit + 48);
  }
  UART_Send(' ');
}

//---------------------------------------------------------------------------------------------------------------------
#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"

//---------------------------------------------------------------------------------------------------------------------

void UART_Init(uint32_t frequency_bps, uint8_t bits, uint8_t parity, uint8_t stop)
{
	char cfg = (1 << UMSEL00);
	
	unsigned long int ubrr = (F_CPU / 16 / 300 / frequency_bps) - 0.5;
	UBRR0L = ubrr;
  ubrr >>= 8; UBRR0H = ubrr & 0x0F;
	
	if ( bits == 5 );
	else if ( bits == 6 ) cfg |= (1 << UCSZ00);
	else if ( bits == 7 ) cfg |= (1 << UCSZ01);
	else cfg |= (1 << UCSZ01) | (1 << UCSZ00);
	if ( bits == 9 ) UCSR0B |= (1 << UCSZ02);
	
	if ( parity == 0 );
	else if ( parity == 1 ) parity |= (1<<UPM01)|(1<<UPM00);
	else parity |= (1 << UPM01);
	
	if ( stop == 2) cfg |= (1 << USBS0);
	
	UCSR0C |= cfg;
	UCSR0B |= (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0); // Enable transmitter, receiver and receive interrupt 
}

//---------------------------------------------------------------------------------------------------------------------

void UART_Send(char dana)
{
	while (!( UCSR0A & (1<<UDRE0)));
	UDR0 = dana;
}

char UART_Read()
{
	while (!(UCSR0A & (1<<RXC0)));
	return UDR0;
}

void UART_String(char *tekst)
{
	char bufor;
	while (bufor = *(tekst++)) { UART_Send(bufor); }
}

void UART_Dec(int val)
{
	char bufor[16];
	UART_String(itoa(val, bufor, 10));
}

void UART_Hex(int val)
{
	char bufor[16];
	UART_String(itoa(val, bufor, 16));
}

void UART_Bin(uint8_t bin )
{
	char value;
	UART_Send('0'); UART_Send('b');
	for(int8_t i = 7; i >= 0; i--) {
		value = (bin >> i) & 1;
    UART_Send(value + 48);
	}
	UART_Send(' ');
}

//---------------------------------------------------------------------------------------------------------------------
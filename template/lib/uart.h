#ifndef UART_H_
#define UART_H_

//---------------------------------------------------------------------------------------------------------------------

void UART_Init(uint32_t frequency_bps, uint8_t bits, uint8_t parity, uint8_t stop);
void UART_Send(char dana);
char UART_Read();
void UART_String(char *tekst);
void UART_Dec(int value);
void UART_Hex(int value);
void UART_Bin(uint8_t value);

//---------------------------------------------------------------------------------------------------------------------
#endif

// ISR ( USART_RXC_vect )
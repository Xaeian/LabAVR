#ifndef MYSPI_H_
#define MYSPI_H_
#include <stdbool.h>
#include <stdint.h>

//---------------------------------------------------------------------------------------------------------------------

#define	SPI_CS 2
#define SPI_MOSI 3
#define SPI_MISO 4
#define	SPI_SCK 5

//---------------------------------------------------------------------------------------------------------------------

void MYSPI_Init();
void MYSPI_Stop();
void MYSPI_Start();
void SEG7_Sign(uint8_t position, uint8_t sign, bool dot);
void SEG7_Int(int16_t value);

//---------------------------------------------------------------------------------------------------------------------

extern volatile uint8_t PORTX, PINX, PORTY[4];

//---------------------------------------------------------------------------------------------------------------------
#endif
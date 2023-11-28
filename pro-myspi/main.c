#include "main.h"
#include <avr/io.h>
#include <util/delay.h>
#include "myspi.h"

int main(void)
{
  MYSPI_Init();
  PORTX = 12;
  PORTY[2] = 0x06;
  SEG7_Sign(2, 1, false);
  while (1);
}
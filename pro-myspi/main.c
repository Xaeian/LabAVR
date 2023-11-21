#include "main.h"
#include <avr/io.h>
#include <util/delay.h>
#include "myspi.h"

int main(void)
{
  MYSPI_Init();

  PORTX = 12;
  PORTY[0] = 1;
  PORTY[1] = 2;
  PORTY[2] = 3;
  PORTY[3] = 4;
  while (1);
}
#include "main.h"
#include "myspi.h"
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
  MYSPI_Init();
  
  while (1)
  {
    PORTX = (1 << 3);
  }
}
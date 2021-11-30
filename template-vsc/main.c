#define __AVR_ATmega328P__
#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>
#include "lib/gpio.h"
#include "lib/port.h"

GPIO_t led = { .pin = 2, .mode = GPIO_MODE_Output };

int main(void)
{

  //GPIO_Init(&led);
  PORT_Init();
  SEG7_Int(123);
  
  while (1)
  {
    // PORTX = x++;
    //GPIO_Set(&led);
    //_delay_ms(300);
    //GPIO_Rst(&led);
    //_delay_ms(300);
  }
}
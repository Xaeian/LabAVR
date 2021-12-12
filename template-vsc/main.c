#include "main.h"
#include <avr/io.h>
#include <util/delay.h>
#include "lib/adc.h"
#include "lib/port.h"
#include "lib/pwm.h"
#include "lib/uart.h"

//GPIO_t led = { .pin = 2, .mode = GPIO_MODE_Output };


typedef enum {
  A0 = 0, A1 = 1, A2 = 2, A3 = 3, A4 = 4, A5 = 5
} ADC_Channel_e;

int main(void)
{
  PWM_Init(1000);
  ADC_Init();
  PORT_Init();
  UART_Init(9600, 8, 0, 1);
  //SEG7_Int(123);
  //SEG7_Sign(1, 'A', true);
  uint16_t value;
  
  while (1)
  {
    value = ADC_Run(A3) * 1000 / 1023;

    PWM_SetA(value);
    UART_Dec(value);
    UART_Send('\r'); UART_Send('\n');
    SEG7_Int(SEG7_Int);
  }
}
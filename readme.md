


IDE for AVR

https://www.microchip.com/en-us/development-tools-tools-and-software/microchip-studio-for-avr-and-sam-devices





# Programator ISP/ASP

Niestety nasze kochane **AVR**-y nie otrzumują już takiego wsparcia jak dawniej. Procesory, programatory, dev-boardy są znacznie droższe w porównaniu z coraz bardziej polularnymi prockami **STM32**. Jednak w mojej opinii taka Atmega328P jest znacznie najlepszym procesorem na początek nauki.
- Mamy ją w obudowie DIP28 THT, więc możemy sobie na płytce stykowej wszystko sami poogarniać
- W sieci i literaturze przez 20 lat pojawiło się zatrzesienie przykładów i materiałów dotyczących mikrokontrolerów AVR, z których zdecydowana większość dotyczy scalaków Atmega8A, Atmega32A oraz Atmega328P
- Mała różnorodność wykorzystywanych układów oraz niewielka ilość peryferiów, która w rozwiązaniach rynkowych jest dużym ograniczenim, tutaj przekłada się na spójność przykładów. Jeden UART, niewielkie możliwości konfiguracji - wystarczy podłączyć i działa. 
Nic tylko programować... Ale, żeby do tego przejść trzeba mieć programator. Popularnym, a co ważniejsze tanim wyborem jest **ISPasp**. Nie jest on wspierany, więc trzeba uciekać się do konfiguracji niestandardowej, ale za 10zł nie ma co wybrzydzać.

```
-c usbasp -p m328p -U flash:w:$(TargetDir)$(TargetName).hex:i
```

http://winavr.sourceforge.net/

https://blog.zakkemble.net/avrdudess-a-gui-for-avrdude/

https://zadig.akeo.ie/

## Operacje binarne

...

## Migająca dioda LED

```cpp
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
  // init();
  DDRD |= 0xFF;

  while (1) {
    // loop();
    _delay_ms(200);
    PORTD |= (1 << 0);
    _delay_ms(200);
    PORTD &= ~(1 << 0);
  }
}
```

## Komunikacja UART

```cpp
#include <avr/io.h>
#include <avr/interrupt.h>
#include "lib/uart.h"

int main(void)
{
  UART_Init(9600, 8, 0, 1);
  sei();
  while(1);
}

ISR(USART_RX_vect)
{
  char data = UART_Read();
  if(((data > 65) && (data < 88)) || ((data > 96) && (data < 120))) { data += 3; }
  else if(((data > 87) && (data < 91)) || ((data > 119) && (data < 123))) { data -= 23; }
  UART_Send(data);
}
```
## Enkoder

W przykładzie należy połączyć oba wyprowadzenia enkodera oraz linie 7 diod

`PA[2] (INT0)` ⟶ `ECR1`

`PA[3]` ⟶ `ECR2`

`PB[0..7] (INT0)` ⟶ `LED[0..7]`

```cpp
#include <avr/io.h>
#include <avr/interrupt.h>

#define ECR_LEFT 1 // 01
#define ECR_RIGHT 2 // 10

uint8_t ecr_left_right;

int main(void)
{
  uint8_t value = 0;
  
  PORTD = 0x0C;
  PORTB = ~value; DDRB = 0xFF;
  
  EIMSK |= (1 << INT0); // External interrupt 0
  EICRA |= (1 << ISC01) || ( 1 << ISC00 ); // Falling & rising edge
  sei();
  
  while (1)
  {    
    if((ecr_left_right == ECR_LEFT) && (value != 0)) {
      value--;
      ecr_left_right = 0;
    } else if((ecr_left_right == ECR_RIGHT) && (value != 255)) {
      value++;
      ecr_left_right = 0;
    }
    PORTB = ~value;
  }
}

ISR(INT0_vect)
{
  uint8_t state = (~PIND >> 2) & 3;
  if((state == 1)||(state == 2)) { ecr_left_right = ECR_RIGHT; }
  else if ((state == 0)||(state == 3)) { ecr_left_right = ECR_LEFT; }
}
```


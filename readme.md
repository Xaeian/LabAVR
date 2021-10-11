---
Emilian Świtalski | es@sqrt.pl
TODO: switch, lcd, ir
---

Kurs programowania procesorów **AVR** na przykładzie mikrokontrolera **Atmega328P**.

## Dlaczego AVR?

Mikrokontrolery wydane przez firmę Atmel nie są już aż tak popularne jak kiedyś i są powolutku wypierane. Jednak w mojej opinii taka Atmega jest lepszym procesorem na początek samodzielnej nauki niż zaawansowany STM32.
- Mamy ją w obudowie **DIP28** THT, więc możemy sobie na płytce stykowej wszystko sami poogarniać
- W sieci i literaturze można znaleźć masę przykładów i materiałów dotyczących tych mikrokontrolerów, z których zdecydowana większość dotyczy scalaków Atmega8A, Atmega32A oraz Atmega328P
- Mała różnorodność wykorzystywanych układów oraz niewielka ilość peryferiów i ich prostota, która w rozwiązaniach rynkowych jest dużym ograniczeniem, tutaj przekłada się na spójność przykładów. Jeden UART, niewielkie możliwości konfiguracji - wystarczy podłączyć i działa.

## Zawartość REPO

W paczce znajdziemy m. in.
- `apps` - Niezbędne oprogramowanie:
  - [Microchip AVR Studio](https://www.microchip.com/en-us/development-tools-tools-and-software/) - IDE
  - [WinAVR](http://winavr.sourceforge.net/download.html) - Paczka zawierająca aplikację do wgrywania firmware przez programator  USB/ASP. Koniecznie trzeba zainstalować
  - [Zadig](https://zadig.akeo.ie/) - Program to aktualizacji programatorów USB/ASP
  - [Realterm](https://realterm.i2cchip.com/) - Terminal do komunikacji z PC
  - [CP210x](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers), [CH430](https://sparks.gogo.co.nz/ch340.html) - Sterowniki to kontrolerów USB
  - [AVRDudess](https://blog.zakkemble.net/avrdudess-a-gui-for-avrdude/) - Aplikacja do wgrywania wsadu oraz ustawiania fuse-bitów
- `template-ms` - Skonfigurowany projekt w **Microchip Studio**
- `template-vsc` - Skonfigurowany projekt w **Visual Studio Code**
- Przykładowe projekty zawierają bibliotekami do obsługi peryferiów mikrokontrolera i układów zewnętrznych:
  - `uart` - Interfejs komunikacyjny wykorzystywany m. in. do komunikacji USB
  - `pwm` - Układ generujący sygnał prostokątny
  - `adc` - Przetwornik analogowo-cyfrowy
  - `i2c` - Interfejs komunikacyjny wykorzystywany m. in. do komunikacji z czujnikami
  - `portx` - dodatkowe porty IO w tym wyświetlacze 7-segmentowe
  - `lcd` - Wyświetlacz ze sterownikiem HD44780

## Microchip Studio for AVR

Skonfigurowany projekt dla Microchip Studio znajduje się w folderze **template-ms**, jednak konieczna jest ustawienie prędkości pracy mikrokontrolera, gdyż jest ona ściśle związana z konfiguracją sprzętową _(fuse-bity / rezonator kwarcowy)_.

![fcpu](./images/fcpu.png)

Aby pracować z programatorem **USB/ASP** trzeba dodać urządzenie zewnętrzne, ponieważ ten programator nie jest oficjalnie wspierany.

![add-external-tool](./images/usbasp1.png)

W polu `Command` należy wybrać ścieżkę do `avrdude.exe`

W polu `Arguments` należy wpisać

```
-c usbasp -p m328p -U flash:w:$(TargetDir)$(TargetName).hex:i
```
![toolbar](./images/usbasp2.png)

Na pasku narzędzi powinno pojawić się `USBasp Atmega328P`

Jak po z**build**owaniu program się nie wgrywa, trzeba przeinstalować sterowniki programatora

![zadig](./images/usbasp3.png)

## Visual Studio Code

Z [Visual Studio Code](https://code.visualstudio.com/Download) sprawa wygląda prościej, gdyż konfiguracja programatora jest zawarta w projekcie **template-vcs**, a nie w IDE. Trzeba jedynie ustawić prędkość pracy jako definicję.

```cpp
#define F_CPU 16000000
```

# Speedrun AVR

Prezentacja obrazująca  [operacje binarne](http://sqrt.pl/avr.pdf) często wykorzystywane w programowaniu systemów wbudowanych.

Wykorzystując płytkę stykową i scalak w obudowie DIP28 przydatna jest ściągawka z wyprowadzeniami mikrokontrolera.

![atmega328p](./images/atmega328p.png)

## Migająca dioda LED

Wymagane połączenia
- `PD0` ⟶ `LED`

```cpp
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
  // init();
  DDRD |= 0xFF;

  while (1)
  {
    // loop();
    _delay_ms(200);
    PORTD |= (1 << 0);
    _delay_ms(200);
    PORTD &= ~(1 << 0);
  }
}
```

### Linijka LED

Wymagane połączenia
- `PD[0..7]` ⟶ `LED[0..7]`

```cpp
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
  uint8_t value = 1;
  DDRD = 0xFF;
  PORTD = ~value;
  
  while (1)
  {
    _delay_ms(30);
    value <<= 1;
    if(!value) {
       value = 1;
    }
    PORTD = ~value;
  }
}
```
Zadanie: zmusić linijkę, żeby poruszała się raz w jedną, a raz w drugą stronę.

## Komunikacja UART

Wymagane połączenia
- `PD0 (RX)` ⟶ `USB-TX`
- `PD1 (TX)` ⟶ `USB-RX`

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

## Biblioteka `portx`

Biblioteka zapewnia mam możliwość sterowania 8 dodatkowymi diodami `PINX`, przyciskami `PORTX`, a także 4 wyświetlaczami, do którego są przygotowane specjalne funkcje. Biblioteka w tle komunikuje się z rejestrami przesuwnymi za pomocą magistrali **SPI**.

Wymagane połączenia
- `PB5 (SCK)` ⟶ `SCK`
- `PB4 (MISO)` ⟶ `SO`
- `PB3 (MOSI)` ⟶ `SI`
- `PB2` ⟶ `CS`

```cpp
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
  uint8_t value = 0;
  PORT_Init();

  while(1)
  {
    _delay_ms(69);
    PORTY_Int(value);
    value++;
  }
}
```

## Przertownik ADC

Wymagane połączenia
- `PC0 (SCK)` ⟶ `POT` | `JOY` | `MIC` | `FT` | `...`

```cpp
#include <avr/io.h>

int main(void)
{
  uint16_t value = 0;
  ADC_Init();

  while(1)
  {
    _delay_ms(69);
    value = ADC_Run(0);
    // TODO: 'value' output
  }
}
```

## Enkoder

Enkoder wykorzystuje przerwanie zewnętrzne INT

Wymagane połączenia
- `PD2 (INT0)` ⟶ `ECR1`
- `PD3` ⟶ `ECR2`

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
  
  EIMSK |= (1 << INT0); // External interrupt 0
  EICRA |= (1 << ISC01) || ( 1 << ISC00 ); // Falling & rising edge
  sei();
  
  while(1)
  {
    if((ecr_left_right == ECR_LEFT) && (value != 0)) {
      value--;
      ecr_left_right = 0;
    } else if((ecr_left_right == ECR_RIGHT) && (value != 255)) {
      value++;
      ecr_left_right = 0;
    }
    // TODO: 'value' output
  }
}

ISR(INT0_vect)
{
  uint8_t state = (~PIND >> 2) & 3;
  if((state == 1)||(state == 2)) { ecr_left_right = ECR_RIGHT; }
  else if ((state == 0)||(state == 3)) { ecr_left_right = ECR_LEFT; }
}
```
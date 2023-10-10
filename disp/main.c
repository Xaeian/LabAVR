#include <stdio.h>
#include <stdint.h>

#define bin "\e[90m0b\e[36m%c%c%c%c\e[34m%c%c%c%c\e[39m"
#define byte2bin(byte)           \
  ((byte)&0x80 ? '1' : '0'),     \
      ((byte)&0x40 ? '1' : '0'), \
      ((byte)&0x20 ? '1' : '0'), \
      ((byte)&0x10 ? '1' : '0'), \
      ((byte)&0x08 ? '1' : '0'), \
      ((byte)&0x04 ? '1' : '0'), \
      ((byte)&0x02 ? '1' : '0'), \
      ((byte)&0x01 ? '1' : '0')

#define hex "\e[90m0x\e[32m%02X\e[39m"
#define pattern bin " " hex " \e[31m%d\e[39m"
#define disp(byte) byte2bin(byte), byte, byte

uint32_t display_n;

void display(uint32_t nbr32)
{
  uint8_t nbr8 = (uint8_t)nbr32;
  printf("%d: " pattern "\n", display_n, disp(nbr8));
  display_n++;
}

int main(int argc, char **argv[])
{
  // uint8_t DDRD = 0x23;
  // uint8_t PORTD = 0x00;

  // // printf("DDRD: "pattern"\n", disp(DDRD));
  // DDRD |= (1 << 7) | (1 << 3);
  // // printf("DDRD: "pattern"\n", disp(DDRD));
  // PORTD = (1 << 7);
  // //printf("PORTD: "pattern"\n", disp(PORTD));
  // PORTD |= (1 << 3);
  // printf("PORTD:     "pattern"\n", disp(PORTD));

  // printf("(1 << 7):  "pattern"\n", disp((1 << 7)));
  // printf("~(1 << 7): "pattern"\n", disp(~(1 << 7)));
  // PORTD &= ~(1 << 7);
  // printf("PORTD    : "pattern"\n", disp(PORTD));

  display(0x23);
  display(0b00011110);
  display(199);
  display(0x7E);
  display(0b10011101);
  display(59);
  display(227);
  display(0xAF);

  // 0xAF

  //     ;
  // printf("2: " pattern "\n", disp(0b00011110));
  // printf("3: " pattern "\n", disp(199));
  // printf("4: " pattern "\n", disp(0x7E));
  // printf("5: " pattern "\n", disp(0b10011101));
  // printf("6: " pattern "\n", disp(59));
  // printf("7: " pattern "\n", disp(227));
  // printf("8: " pattern "\n", disp(0xAF));

  // uint8_t a = ((3 << 3) | (10 / 3)) & ~0xF0;
  // printf("a: " pattern "\n", disp(a));

  // uint8_t b = (99 - 101) ^ 2;
  // printf("b: " pattern "\n", disp(b));

  // uint8_t c = ((uint16_t)101 + 303) >> 1;
  // printf("c: " pattern "\n", disp(c));
}

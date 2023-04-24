#include <stdio.h>
#include <stdint.h>

#define bin "\e[90m0b\e[36m%c%c%c%c\e[34m%c%c%c%c\e[39m"
#define byte2bin(byte)  \
  ((byte) & 0x80 ? '1' : '0'), \
  ((byte) & 0x40 ? '1' : '0'), \
  ((byte) & 0x20 ? '1' : '0'), \
  ((byte) & 0x10 ? '1' : '0'), \
  ((byte) & 0x08 ? '1' : '0'), \
  ((byte) & 0x04 ? '1' : '0'), \
  ((byte) & 0x02 ? '1' : '0'), \
  ((byte) & 0x01 ? '1' : '0')

#define hex "\e[90m0x\e[32m%02X\e[39m"
#define pattern bin" "hex" \e[31m%d\e[39m"
#define disp(byte) byte2bin(byte), byte, byte 

uint32_t display_n;

void display(uint32_t nbr32)
{
  uint8_t nbr8 = (uint8_t)nbr32;
  printf("x%d: "pattern"\n", display_n, disp(nbr8));
  display_n++;
}


int main(int argc, char **argv[])
{
  uint8_t DDRD = 0x23;
  uint8_t PORTD = 0x00;

  // printf("DDRD: "pattern"\n", disp(DDRD));
  DDRD |= (1 << 7) | (1 << 3);
  // printf("DDRD: "pattern"\n", disp(DDRD));
  PORTD = (1 << 7);
  //printf("PORTD: "pattern"\n", disp(PORTD));
  PORTD |= (1 << 3);
  printf("PORTD:     "pattern"\n", disp(PORTD));

  printf("(1 << 7):  "pattern"\n", disp((1 << 7)));
  printf("~(1 << 7): "pattern"\n", disp(~(1 << 7)));
  PORTD &= ~(1 << 7);
  printf("PORTD    : "pattern"\n", disp(PORTD));
}
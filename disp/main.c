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

int main(int argc, char **argv[])
{
  uint8_t DDRD = 0x23;
  printf("DDRD: "pattern"\n", disp(DDRD));





  
}
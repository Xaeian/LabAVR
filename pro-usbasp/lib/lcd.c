#include "main.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <stdlib.h>
#include "lcd.h"

static void LCD_DataOutput()
{
  #if(LCD_INTERFACE_BITS == 8)
    DDR(LCD_D0_PORT) |= (1 << LCD_D0_PIN);
    DDR(LCD_D1_PORT) |= (1 << LCD_D1_PIN);
    DDR(LCD_D2_PORT) |= (1 << LCD_D2_PIN);
    DDR(LCD_D3_PORT) |= (1 << LCD_D3_PIN);
  #endif
  DDR(LCD_D4_PORT) |= (1 << LCD_D4_PIN);
  DDR(LCD_D5_PORT) |= (1 << LCD_D5_PIN);
  DDR(LCD_D6_PORT) |= (1 << LCD_D6_PIN);
  DDR(LCD_D7_PORT) |= (1 << LCD_D7_PIN);
}

static void LCD_DataInput()
{
  #if(LCD_INTERFACE_BITS == 8)
    DDR(LCD_D0_PORT) &= ~(1 << LCD_D0_PIN);
    DDR(LCD_D1_PORT) &= ~(1 << LCD_D1_PIN);
    DDR(LCD_D2_PORT) &= ~(1 << LCD_D2_PIN);
    DDR(LCD_D3_PORT) &= ~(1 << LCD_D3_PIN);
    PORT(LCD_D0_PORT) &= ~(1 << LCD_D0_PIN);
    PORT(LCD_D1_PORT) &= ~(1 << LCD_D1_PIN);
    PORT(LCD_D2_PORT) &= ~(1 << LCD_D2_PIN);
    PORT(LCD_D3_PORT) &= ~(1 << LCD_D3_PIN);
  #endif
  DDR(LCD_D4_PORT) &= ~(1 << LCD_D4_PIN);
  DDR(LCD_D5_PORT) &= ~(1 << LCD_D5_PIN);
  DDR(LCD_D6_PORT) &= ~(1 << LCD_D6_PIN);
  DDR(LCD_D7_PORT) &= ~(1 << LCD_D7_PIN);
  PORT(LCD_D4_PORT) &= ~(1 << LCD_D4_PIN);
  PORT(LCD_D5_PORT) &= ~(1 << LCD_D5_PIN);
  PORT(LCD_D6_PORT) &= ~(1 << LCD_D6_PIN);
  PORT(LCD_D7_PORT) &= ~(1 << LCD_D7_PIN);
}

static void LCD_InterfaceSend(uint8_t data)
{
  #if(LCD_INTERFACE_BITS == 8)
    if (data & (1 << 0)) PORT(LCD_D0_PORT) |= (1 << LCD_D0_PIN);
    else PORT(LCD_D0_PORT) &= ~(1 << LCD_D0_PIN);
    if (data & (1 << 1)) PORT(LCD_D1_PORT) |= (1 << LCD_D1_PIN);
    else PORT(LCD_D1_PORT) &= ~(1 << LCD_D1_PIN);
    if (data & (1 << 2)) PORT(LCD_D2_PORT) |= (1 << LCD_D2_PIN);
    else PORT(LCD_D2_PORT) &= ~(1 << LCD_D2_PIN);
    if (data & (1 << 3)) PORT(LCD_D3_PORT) |= (1 << LCD_D3_PIN);
    else PORT(LCD_D3_PORT) &= ~(1 << LCD_D3_PIN);
    if (data & (1 << 4)) PORT(LCD_D4_PORT) |= (1 << LCD_D4_PIN);
    else PORT(LCD_D4_PORT) &= ~(1 << LCD_D4_PIN);
    if (data & (1 << 5)) PORT(LCD_D5_PORT) |= (1 << LCD_D5_PIN);
    else PORT(LCD_D5_PORT) &= ~(1 << LCD_D5_PIN);
    if (data & (1 << 6)) PORT(LCD_D6_PORT) |= (1 << LCD_D6_PIN);
    else PORT(LCD_D6_PORT) &= ~(1 << LCD_D6_PIN);
    if (data & (1 << 7)) PORT(LCD_D7_PORT) |= (1 << LCD_D7_PIN);
    else PORT(LCD_D7_PORT) &= ~(1 << LCD_D7_PIN);
  #elif
    if (data & (1<<0)) PORT(LCD_D4_PORT) |= (1 << LCD_D4_PIN);
    else PORT(D4_PORT) &= ~(1 << LCD_D4_PIN);
    if (data & (1<<1)) PORT(LCD_D5_PORT) |= (1 << LCD_D5_PIN);
    else PORT(D5_PORT) &= ~(1 << LCD_D5_PIN);
    if (data & (1<<2)) PORT(LCD_D6_PORT) |= (1 << LCD_D6_PIN);
    else PORT(D6_PORT) &= ~(1 << LCD_D6_PIN);
    if (data & (1<<3)) PORT(LCD_D7_PORT) |= (1 << LCD_D7_PIN);
    else PORT(D7_PORT) &= ~(1 << LCD_D7_PIN);
  #endif
}

static char LCD_InterfaceRead() {
  uint8_t data = 0;
  #if(LCD_INTERFACE_BITS == 8)
      if(PIN(LCD_D0_PORT) & (1 << LCD_D0_PIN)) data |= (1<<0);
      if(PIN(LCD_D1_PORT) & (1 << LCD_D1_PIN)) data |= (1<<1);
      if(PIN(LCD_D2_PORT) & (1 << LCD_D2_PIN)) data |= (1<<2);
      if(PIN(LCD_D3_PORT) & (1 << LCD_D3_PIN)) data |= (1<<3);
      if(PIN(LCD_D4_PORT) & (1 << LCD_D4_PIN)) data |= (1<<4);
      if(PIN(LCD_D5_PORT) & (1 << LCD_D5_PIN)) data |= (1<<5);
      if(PIN(LCD_D6_PORT) & (1 << LCD_D6_PIN)) data |= (1<<6);
      if(PIN(LCD_D7_PORT) & (1 << LCD_D7_PIN)) data |= (1<<7);
  #elif
    if(PIN(LCD_D4_PORT) & (1 << LCD_D4_PIN)) data |= (1<<0);
    if(PIN(LCD_D5_PORT) & (1 << LCD_D5_PIN)) data |= (1<<1);
    if(PIN(LCD_D6_PORT) & (1 << LCD_D6_PIN)) data |= (1<<2);
    if(PIN(LCD_D7_PORT) & (1 << LCD_D7_PIN)) data |= (1<<3);
  #endif
  return data;
}

static void LCD_CommandRS() { PORT(LCD_RS_PORT) &= ~(1 << LCD_RS_PIN); }
static void LCD_DataRS() { PORT(LCD_RS_PORT) |= (1 << LCD_RS_PIN); }
static void LCD_SendRW() { PORT(LCD_RW_PORT) &= ~(1 << LCD_RW_PIN); }
static void LCD_ReadRW() { PORT(LCD_RW_PORT) |= (1 << LCD_RW_PIN); }

static char LCD_Read()
{
  char byte = 0;
  #if(LCD_INTERFACE_BITS == 4)
    LCD_E_SET; byte = (LCD_InterfaceRead() << 4); LCD_E_CLR;
  #endif
  LCD_E_SET; byte |= (LCD_InterfaceRead()); LCD_E_CLR;
  return byte;
}

static char LCD_ReadCommand()
{
  LCD_ReadRW(); LCD_CommandRS(); LCD_DataInput();
  return LCD_Read();
}

static void LCD_Send(uint8_t data)
{
  char BF = 1;
  #if(LCD_INTERFACE_BITS == 4)
    LCD_E_SET; LCD_InterfaceSend(data >> 4); LCD_E_CLR;
  #endif
  LCD_E_SET; LCD_InterfaceSend(data); LCD_E_CLR;
  
  #if(LCD_IDLE_CONFIRM)
    while(BF) { BF = LCD_ReadCommand() & (1<<7); }
  #else 
    _delay_us(37);
  #endif
}

//---------------------------------------------------------------------------------------------------------------------

void LCD_SendCommand(uint8_t data)
{
  #if(LCD_IDLE_CONFIRM)
    LCD_SendRW();
  #endif
  LCD_CommandRS(); LCD_DataOutput();
  LCD_Send(data);
}

void LCD_SendData(uint8_t data)
{
  #if(LCD_IDLE_CONFIRM)
    LCD_SendRW();
  #endif
  LCD_DataRS(); LCD_DataOutput();
  LCD_Send(data);
}

void LCD_Init()
{
  #if(LCD_INTERFACE_BITS == 8)
    DDR(LCD_D0_PORT) |= (1 << LCD_D0_PIN);
    DDR(LCD_D1_PORT) |= (1 << LCD_D1_PIN);
    DDR(LCD_D2_PORT) |= (1 << LCD_D2_PIN);
    DDR(LCD_D3_PORT) |= (1 << LCD_D3_PIN);
  #endif
  DDR(LCD_D4_PORT) |= (1 << LCD_D4_PIN);
  DDR(LCD_D5_PORT) |= (1 << LCD_D5_PIN);
  DDR(LCD_D6_PORT) |= (1 << LCD_D6_PIN);
  DDR(LCD_D7_PORT) |= (1 << LCD_D7_PIN);
  
  #if(LCD_IDLE_CONFIRM)
    DDR(LCD_RW_PORT) |= (1 << LCD_RW_PIN);
  #endif
  
  DDR(LCD_RS_PORT) |= (1 << LCD_RS_PIN);
  DDR(LCD_E_PORT) |= (1 << LCD_E_PIN);

  _delay_ms(15); LCD_E_CLR;
  #if(LCD_IDLE_CONFIRM)
    LCD_SendRW();
  #endif
  LCD_CommandRS();
  
  #if(LCD_INTERFACE_BITS == 8)
    LCD_E_SET; LCD_InterfaceSend(0x96); LCD_E_CLR; _delay_ms(4.1);
    LCD_E_SET; LCD_InterfaceSend(0x96); LCD_E_CLR; _delay_us(100);
    LCD_E_SET; LCD_InterfaceSend(0x96); LCD_E_CLR; _delay_us(100);
    LCD_SendCommand(0x38);
  #else
    LCD_E_SET; LCD_InterfaceSend(0x03); LCD_E_CLR; _delay_ms(4.1);
    LCD_E_SET; LCD_InterfaceSend(0x03); LCD_E_CLR; _delay_us(100);
    LCD_E_SET; LCD_InterfaceSend(0x03); LCD_E_CLR; _delay_us(100);
    LCD_E_SET; LCD_InterfaceSend(0x02); LCD_E_CLR; _delay_us(100);
    LCD_SendCommand(0x28);
  #endif
  LCD_SendCommand(0x08);
  LCD_SendCommand(0x0C);
  LCD_SendCommand(0x06);
  LCD_SendCommand(0x01);
}

void LCD_Clear()
{
  LCD_SendCommand(0x01);
  #if BF_SPR == 0
  _delay_ms(1.52);
  #endif
}

void LCD_Home()
{
  LCD_SendCommand(0x03);
  #if BF_SPR == 0
  _delay_ms(1.52);
  #endif
}

void LCD_ModeCL() { LCD_SendCommand(0x04); }
void LCD_ModeCR() { LCD_SendCommand(0x06); }
void LCD_ModeDL() { LCD_SendCommand(0x05); }
void LCD_ModeDR() { LCD_SendCommand(0x07); }

void LCD_CursorOFF() { LCD_SendCommand(0x0C); }
void LCD_CursorON() { LCD_SendCommand(0x0E); }
void LCD_CursorBlink() { LCD_SendCommand(0x0F); }
  
void LCD_ShiftCL() { LCD_SendCommand(0x04 << 2); }
void LCD_ShiftCR() { LCD_SendCommand(0x06 << 2); }
void LCD_ShiftDL() { LCD_SendCommand(0x05 << 2); }
void LCD_ShiftDR() { LCD_SendCommand(0x07 << 2); }
  
void LCD_CursorPosition(uint8_t x, uint8_t y) // x <0;n>, y <0;1>
{
  LCD_SendCommand(128 + (y * 64) + x);
}

void LCD_String(char *tekst)
{
  char buffer = *(tekst++);
  while(buffer) {
    LCD_SendData((uint8_t)buffer);
    buffer = *(tekst++);
  }
}

void LCD_String_Const(const char *tekst)
{
  char buffer = pgm_read_byte(tekst++);
  while(buffer) {
    LCD_SendData((uint8_t)buffer);
    buffer = pgm_read_byte(tekst++);
  }    
}
void LCD_Dec(int32_t value)
{
  char buffer[16];
  LCD_String(itoa(value, buffer, 10));
}

void LCD_Hex(uint32_t value)
{
  char buffer[16];
  LCD_String(itoa(value, buffer, 16));
}

//---------------------------------------------------------------------------------------------------------------------
#if(LCD_CUSTOME_CHARS == 1)

void LCD_CustomeChars(uint8_t reg, char *data) // reg <0;7>
{
  LCD_SendCommand(0x40 | (reg << 3) );
  for(uint8_t i = 0; i < 8; i++)
    LCD_SendData(*(data++));
  LCD_SendCommand(0x80);
}

void LCD_CustomeChars_Const(uint8_t reg, const char *data) // reg <0;7>
{
  LCD_SendCommand(0x40 | (reg << 3));
  for(uint8_t i = 0; i < 8; i++)
    LCD_SendData(pgm_read_byte(data++));
  LCD_SendCommand(0x80);
}

#endif
//---------------------------------------------------------------------------------------------------------------------

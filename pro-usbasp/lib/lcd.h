#ifndef LCD_H_
#define LCD_H_

//---------------------------------------------------------------------------------------------------------------------

#define PINA _SFR_IO8(0x00)
#define DDRA _SFR_IO8(0x01)
#define PORTA _SFR_IO8(0x02)

#define PORT(x) SPORT(x)
#define SPORT(x) (PORT##x)
#define PIN(x) SPIN(x)
#define SPIN(x) (PIN##x)
#define DDR(x) SDDR(x)
#define SDDR(x) (DDR##x)

//---------------------------------------------------------------------------------------------------------------------

#define LCD_D0_PORT B
#define LCD_D0_PIN 0
#define LCD_D1_PORT B
#define LCD_D1_PIN 1
#define LCD_D2_PORT B
#define LCD_D2_PIN 2
#define LCD_D3_PORT B
#define LCD_D3_PIN 3
#define LCD_D4_PORT B
#define LCD_D4_PIN 4
#define LCD_D5_PORT B
#define LCD_D5_PIN 5
#define LCD_D6_PORT B
#define LCD_D6_PIN 6
#define LCD_D7_PORT B
#define LCD_D7_PIN 7

#define LCD_E_PORT A
#define LCD_E_PIN  0
#define LCD_RS_PORT A
#define LCD_RS_PIN 1
#define LCD_RW_PORT A
#define LCD_RW_PIN 2

//---------------------------------------------------------------------------------------------------------------------

#define LCD_E_SET  PORT(LCD_E_PORT) |= (1 << (LCD_E_PIN))
#define LCD_E_CLR  PORT(LCD_E_PORT) &= ~(1 << (LCD_E_PIN))

//--------------------------------------------------------------------------------------------------------------------- <--- Pre-compilation

#define LCD_IDLE_CONFIRM 1
#define LCD_INTERFACE_BITS 8 // { 4, 8 }
#define LCD_CUSTOME_CHARS  1

//---------------------------------------------------------------------------------------------------------------------

void LCD_SendCommand(uint8_t data);
void LCD_SendData(uint8_t data);
void LCD_Init();
void LCD_Clear();
void LCD_Home();

void LCD_ModeCL();
void LCD_ModeCR();
void LCD_ModeDL();
void LCD_ModeDR();
void LCD_CursorOFF();
void LCD_CursorON();
void LCD_CursorBlink();
void LCD_ShiftCL();
void LCD_ShiftCR();
void LCD_ShiftDL();
void LCD_ShiftDR();

void LCD_CursorPosition(uint8_t x, uint8_t y);
void LCD_String(char *tekst);
void LCD_String_Const(const char *tekst);
void LCD_Dec(int32_t value);
void LCD_Hex(uint32_t value);
#if(LCD_CUSTOME_CHARS == 1)
  void LCD_CustomeChars(uint8_t reg, char *data);
  void LCD_CustomeChars_Const(uint8_t reg, const char *data);
#endif

//-------------------------------------------------------------------------------------------------
#endif

/*
char tab[] = {...};
const char tab[] PROGMEM = {...};
  
LCD_Tekst("...");
LCD_Tekst_P(PSTR("..."));
*/
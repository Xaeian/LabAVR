#ifndef I2C_H_
#define I2C_H_

//---------------------------------------------------------------------------------------------------------------------

void I2C_Init(uint32_t frequency_khz);
static void I2C_Start(void);
static void I2C_Stop(void);
static void I2C_SendData(uint8_t data);
static uint8_t I2C_ReadData(uint8_t ack);
char I2C_Read(uint8_t device_addr, uint8_t register_addr);
void I2C_Send(uint8_t device_addr, uint8_t register_addr, uint8_t data);
void I2C_SetBits(uint8_t device_addr, uint8_t register_addr, uint8_t ones, uint8_t zeros);
void I2C_ReadBuffer(uint8_t device_addr, uint8_t register_addr, uint8_t count, uint8_t *buffer);
void I2C_SendBuffer(uint8_t device_addr, uint8_t register_addr, uint8_t count, uint8_t buffer[]);

//---------------------------------------------------------------------------------------------------------------------
#endif
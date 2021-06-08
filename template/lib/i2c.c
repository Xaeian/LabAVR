#include <avr/io.h>
#include <avr/interrupt.h>
#include "i2c.h"

//---------------------------------------------------------------------------------------------------------------------

void I2C_Init(uint32_t frequency) // kHz
{
	TWBR = (uint8_t)((float)F_CPU / 2000 / frequency)-7.5;
}

static void I2C_Start(void)
{
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTA);
	while (!(TWCR & (1 << TWINT)));
}

static void I2C_Stop(void)
{
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
	while((TWCR & (1 << TWSTO)));
}

static void I2C_SendData(uint8_t data)
{
	TWDR = data;
	TWCR = (1 << TWINT)|(1 << TWEN);
	while (!(TWCR & (1 << TWINT)));
}

static uint8_t I2C_ReadData(uint8_t ack)
{
	TWCR = (1<<TWINT)|(ack<<TWEA)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
	return TWDR;
}

//---------------------------------------------------------------------------------------------------------------------

char I2C_Read(uint8_t device_addr, uint8_t register_addr)
{
	uint8_t data;
	I2C_Start();
	I2C_SendData(device_addr);
	I2C_SendData(register_addr);
	I2C_Start();
	I2C_SendData(device_addr + 1);
	data = I2C_ReadData(0);
	I2C_Stop();
	return data;
}

void I2C_Send(uint8_t device_addr, uint8_t register_addr, uint8_t data)
{
	I2C_Start();
	I2C_SendData(device_addr);
	I2C_SendData(register_addr);
	I2C_SendData(data);
	I2C_Stop();
}

// ones: items on which we want to overwrite '1' must be equal to 1, and the remaining ones to 0
// if we want to overwrite all 0, ones = 0x00
// zeros: items on which we want to overwrite '0' must be 0 and the rest 1
// if we want to overwrite only 1, zeros = 0xFF

void I2C_SetBits(uint8_t device_addr, uint8_t register_addr, uint8_t ones, uint8_t zeros)
{
	uint8_t data;
	data = I2C_Read(device_addr, register_addr);
	data |= ones;
	data &= zeros;
	I2C_Send(device_addr, register_addr, data);
}

void I2C_ReadBuffer(uint8_t device_addr, uint8_t register_addr, uint8_t count, uint8_t *buffer)
{
	I2C_Start();
	I2C_SendData(device_addr);
	I2C_SendData(register_addr);
	I2C_Start();
	I2C_SendData(device_addr + 1);
	while(count > 1) {
    *buffer = I2C_ReadData(1);
    buffer += 1;
    count -= 1;
  }
	*buffer = I2C_ReadData(0);
	I2C_Stop();
}

void I2C_SendBuffer(uint8_t device_addr, uint8_t register_addr, uint8_t count, uint8_t buffer[])
{
	I2C_Start();
	I2C_SendData(device_addr);
	I2C_SendData(register_addr);
	for(uint8_t i = 0; i <= count; i++) I2C_SendData( buffer[i] );
	I2C_Stop();
}

//---------------------------------------------------------------------------------------------------------------------
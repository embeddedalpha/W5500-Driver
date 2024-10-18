/*
 * W5500.c
 *
 *  Created on: Oct 17, 2024
 *      Author: kunal
 */

#include "W5500.h"

extern bool W5500_Link_UP_Down;

static void Write_1_Byte(W5500_Config *config, uint16_t offset, uint8_t control_register, uint8_t data)
{
	SPI_NSS_Low(&config->SPI);
	SPI_TRX_Byte(&config->SPI, (0xFF00 & offset)>>8);
	SPI_TRX_Byte(&config->SPI, (0x00FF & offset)>>0);
	SPI_TRX_Byte(&config->SPI, (control_register<<3|(1<<2)|(1<<0)));
	SPI_TRX_Byte(&config->SPI, data);
	SPI_NSS_High(&config->SPI);
}

static void Write_2_Byte(W5500_Config *config, uint16_t offset, uint8_t control_register, uint8_t data[2])
{
	SPI_NSS_Low(&config->SPI);
	SPI_TRX_Byte(&config->SPI, (0xFF00 & offset)>>8);
	SPI_TRX_Byte(&config->SPI, (0x00FF & offset)>>0);
	SPI_TRX_Byte(&config->SPI, (control_register<<3|(1<<2)|(1<<0)));
	SPI_TRX_Byte(&config->SPI, data[0]);
	SPI_TRX_Byte(&config->SPI, data[1]);
	SPI_NSS_High(&config->SPI);
}


static void Write_4_Byte(W5500_Config *config, uint16_t offset, uint8_t control_register, uint8_t data[4])
{
	SPI_NSS_Low(w5500_spi);
	SPI_TRX_Byte(w5500_spi, (0xFF00 & offset)>>8);
	SPI_TRX_Byte(w5500_spi, (0x00FF & offset)>>0);
	SPI_TRX_Byte(w5500_spi, (control_register<<3|(1<<2)|(3<<0)));
	SPI_TRX_Byte(w5500_spi, data[0]);
	SPI_TRX_Byte(w5500_spi, data[1]);
	SPI_TRX_Byte(w5500_spi, data[2]);
	SPI_TRX_Byte(w5500_spi, data[3]);
	SPI_NSS_High(w5500_spi);
}

static void Write_Multiple_Bytes(W5500_Config *config, uint16_t offset, uint8_t control_register, uint8_t *data, uint16_t length)
{
	SPI_NSS_Low(&config->SPI);
	SPI_TRX_Byte(&config->SPI, (0xFF00 & offset)>>8);
	SPI_TRX_Byte(&config->SPI, (0x00FF & offset)>>0);
	SPI_TRX_Byte(&config->SPI, (control_register<<3|(1<<2)));
//	for(uint16_t i = 0; i < length; i++ )
//	{
//		SPI_TRX_Byte(w5500_spi, data[i]);
//	}
	SPI_NSS_High(&config->SPI);
}



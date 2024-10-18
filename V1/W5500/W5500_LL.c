/*
 * W5500_LL.c
 *
 *  Created on: Nov 15, 2023
 *      Author: kunal
 */

#include "W5500_LL.h"
#include "SPI.h"

void Write_1_Byte(W5500_Config *config,uint16_t offset, uint8_t control_register, uint8_t data)
{
	SPI_Config *w5500_spi = &config->SPI;
	SPI_NSS_Low(w5500_spi);
	SPI_TRX_Byte(w5500_spi, (0xFF00 & offset)>>8);
	SPI_TRX_Byte(w5500_spi, (0x00FF & offset)>>0);
	SPI_TRX_Byte(w5500_spi, (control_register<<3|(1<<2)|(1<<0)));
	SPI_TRX_Byte(w5500_spi, data);
	SPI_NSS_High(w5500_spi);
}

void Write_2_Byte(W5500_Config *config,uint16_t offset, uint8_t control_register, uint8_t data[2])
{
	SPI_Config *w5500_spi = &config->SPI;
	SPI_NSS_Low(w5500_spi);
	SPI_TRX_Byte(w5500_spi, (0xFF00 & offset)>>8);
	SPI_TRX_Byte(w5500_spi, (0x00FF & offset)>>0);
	SPI_TRX_Byte(w5500_spi, (control_register<<3|(1<<2)|(2<<0)));
	SPI_TRX_Byte(w5500_spi, data[0]);
	SPI_TRX_Byte(w5500_spi, data[1]);
	SPI_NSS_High(w5500_spi);
}

void Write_4_Byte(W5500_Config *config,uint16_t offset, uint8_t control_register, uint8_t data[4])
{
	SPI_Config *w5500_spi = &config->SPI;
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

void Write_Multiple_Bytes(W5500_Config *config,uint16_t offset, uint8_t control_register, uint8_t *data, uint16_t length)
{
	SPI_Config *w5500_spi = &config->SPI;
	SPI_NSS_Low(w5500_spi);
	SPI_TRX_Byte(w5500_spi, (0xFF00 & offset)>>8);
	SPI_TRX_Byte(w5500_spi, (0x00FF & offset)>>0);
	SPI_TRX_Byte(w5500_spi, (control_register<<3|(1<<2)));
	for(uint16_t i = 0; i < length; i++ )
	{
		SPI_TRX_Byte(w5500_spi, data[i]);
	}
	SPI_NSS_High(w5500_spi);

}



void Read_1_Byte(W5500_Config *config,uint16_t offset, uint8_t control_register, uint8_t *data)
{
	SPI_Config *w5500_spi = &config->SPI;
	SPI_NSS_Low(w5500_spi);
	SPI_TRX_Byte(w5500_spi, (0xFF00 & offset)>>8);
	SPI_TRX_Byte(w5500_spi, (0x00FF & offset)>>0);
	SPI_TRX_Byte(w5500_spi, (control_register<<3|(0<<2)|(1<<0)));
	*data = SPI_TRX_Byte(w5500_spi, 0xAA);
	SPI_NSS_High(w5500_spi);
}

void Read_2_Byte(W5500_Config *config,uint16_t offset, uint8_t control_register, uint8_t *data)
{
	SPI_Config *w5500_spi = &config->SPI;
	SPI_NSS_Low(w5500_spi);
	SPI_TRX_Byte(w5500_spi, (0xFF00 & offset)>>8);
	SPI_TRX_Byte(w5500_spi, (0x00FF & offset)>>0);
	SPI_TRX_Byte(w5500_spi, (control_register<<3|(0<<2)|(2<<0)));
	data[0] = SPI_TRX_Byte(w5500_spi, 0x00);
	data[1] = SPI_TRX_Byte(w5500_spi, 0x00);
	SPI_NSS_High(w5500_spi);
}


void Read_4_Byte(W5500_Config *config,uint16_t offset, uint8_t control_register, uint8_t *data1,uint8_t *data2,uint8_t *data3,uint8_t *data4)
{
	SPI_Config *w5500_spi = &config->SPI;
	SPI_NSS_Low(w5500_spi);
	SPI_TRX_Byte(w5500_spi, (0xFF00 & offset)>>8);
	SPI_TRX_Byte(w5500_spi, (0x00FF & offset)>>0);
	SPI_TRX_Byte(w5500_spi, (control_register<<3|(0<<2)|(3<<0)));
	*data1 = SPI_TRX_Byte(w5500_spi, 0x00);
	*data2 = SPI_TRX_Byte(w5500_spi, 0x00);
	*data3 = SPI_TRX_Byte(w5500_spi, 0x00);
	*data4 = SPI_TRX_Byte(w5500_spi, 0x00);
	SPI_NSS_High(w5500_spi);
}

void Read_Multiple_Bytes(W5500_Config *config,uint16_t offset, uint8_t control_register, uint8_t *data, uint16_t length)
{
	SPI_Config *w5500_spi = &config->SPI;
	SPI_NSS_Low(w5500_spi);
	SPI_TRX_Byte(w5500_spi, (0xFF00 & offset)>>8);
	SPI_TRX_Byte(w5500_spi, (0x00FF & offset)>>0);
	SPI_TRX_Byte(w5500_spi, (control_register<<3|(0<<2)));
	for(uint16_t i = 0; i < length; i++ )
	{
		data[i] = SPI_TRX_Byte(w5500_spi, 0x00);
	}
	SPI_NSS_High(w5500_spi);

}


void Read_Buffer(W5500_Config *config,uint16_t address, uint8_t *data, uint16_t length)
{
	SPI_Config *w5500_spi = &config->SPI;
	SPI_NSS_Low(w5500_spi);
	SPI_TRX_Byte(w5500_spi, (0xFF00 & address)>>8);
	SPI_TRX_Byte(w5500_spi, (0x00FF & address)>>0);
	SPI_TRX_Byte(w5500_spi, 0b00011000);
	for(uint16_t i = 0; i < length; i++ )
	{
		data[i] = (uint8_t)SPI_TRX_Byte(w5500_spi, 0x00);
	}
	SPI_NSS_High(w5500_spi);
}

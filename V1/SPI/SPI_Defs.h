/*
 * SPI_Defs.h
 *
 *  Created on: Nov 12, 2023
 *      Author: kunal
 */

#ifndef SPI_DEFS_H_
#define SPI_DEFS_H_

#include "main.h"



static const struct SPI_Mode
{
	uint8_t Full_Duplex_Master;
	uint8_t Full_Duplex_Slave;

	uint8_t Half_Duplex_Master;
	uint8_t Half_Duplex_Slave;

	uint8_t RX_Only_Master;
	uint8_t RX_Only_Slave;

	uint8_t TX_Only_Master;
	uint8_t TX_Only_Slave;

}SPI_Mode = {0,0, 1,2, 2,1, 1,2};

static const struct SPI_CRC
{
	uint16_t Enable;
	uint16_t Disable;
}SPI_CRC = {1 << 14, 0 << 14};

static const struct SPI_Data_Format
{
	uint16_t Bit8;
	uint16_t Bit16;
}SPI_Data_Format = {0 << 11, 1 << 11};

static const struct SPI_Frame_Format
{
	uint16_t MSB_First;
	uint16_t LSB_First;
}SPI_Frame_Format = {0 << 7, 1 << 7};

static const struct SPI_Clock_Phase
{
	uint16_t High_1;
	uint16_t Low_0;
}SPI_Clock_Phase = {1 << 0, 0 << 0};

static const struct SPI_Clock_Polarity
{
	uint16_t High_1;
	uint16_t Low_0;
}SPI_Clock_Polarity = {1 << 1, 0 << 1};

static const struct SPI_Type
{
	uint16_t Master;
	uint16_t Slave;
}SPI_Type = {1 << 2, 0 << 2};

static const struct SPI_Interrupt
{
	uint8_t Tx_Buffer_Empty;
	uint8_t RX_Buffer_not_Empty;
	uint8_t Error;
	uint8_t Disable;
}SPI_Interrupt={1,2,3,0};

static const struct SPI_DMA
{
	uint8_t TX_DMA_Enable;
	uint8_t TX_DMA_Disable;
	uint8_t RX_DMA_Enable;
	uint8_t RX_DMA_Disable;
}SPI_DMA={1<<1,0,1<<0,0};


static const struct SPI_DMA_Stream
{
	DMA_Stream_TypeDef *SPI3_RX_1;
	DMA_Stream_TypeDef *SPI3_RX_2;
	int SPI3_Channel;
	DMA_Stream_TypeDef *SPI3_TX_1;
	DMA_Stream_TypeDef *SPI3_TX_2;

	DMA_Stream_TypeDef *SPI2_RX;
	int SPI2_Channel;
	DMA_Stream_TypeDef *SPI2_TX;

	DMA_Stream_TypeDef *SPI1_RX_1;
	DMA_Stream_TypeDef *SPI1_RX_2;
	int SPI1_Channel;
	DMA_Stream_TypeDef *SPI1_TX_1;
	DMA_Stream_TypeDef *SPI1_TX_2;

}SPI_DMA_Stream = {
		DMA1_Stream0, DMA1_Stream2, 0, DMA1_Stream5, DMA1_Stream7,
		DMA1_Stream3, 0, DMA1_Stream4,
		DMA2_Stream0, DMA2_Stream2, 3, DMA2_Stream3, DMA2_Stream5,
};


static const struct SPI1_CLK
{
	uint16_t PA5;
	uint16_t PB3;
}SPI1_CLK={15,23};

static const struct SPI1_MISO
{
	uint16_t PA6;
	uint16_t PB4;

}SPI1_MISO={16,24};

static const struct SPI1_MOSI
{
	uint16_t PA7;
	uint16_t PB5;

}SPI1_MOSI ={17,25};

//

static const struct SPI2_MISO
{
	uint16_t PC2;
	uint16_t PB14;
}SPI2_MISO={32,214};

static const struct SPI2_MOSI
{
	uint16_t PC3;
	uint16_t PB15;

}SPI2_MOSI={33,215};

static const struct SPI2_CLK
{
	uint16_t PB10;
	uint16_t PB13;

}SPI2_CLK ={210,213};

//

static const struct SPI3_MISO
{
	uint16_t PC11;
	uint16_t PB4;
}SPI3_MISO={311,24};

static const struct SPI3_MOSI
{
	uint16_t PC12;
	uint16_t PB5;

}SPI3_MOSI={312,25};

static const struct SPI3_CLK
{
	uint16_t PC10;
	uint16_t PB3;
}SPI3_CLK ={310,23};

static const struct SPI_Prescaler
{
	uint16_t CLK_div_2;
	uint16_t CLK_div_4;
	uint16_t CLK_div_8;
	uint16_t CLK_div_16;
	uint16_t CLK_div_32;
	uint16_t CLK_div_64;
	uint16_t CLK_div_128;
	uint16_t CLK_div_256;
}SPI_Prescaler ={0,1,2,3,4,5,6,7};





#endif /* SPI_DEFS_H_ */

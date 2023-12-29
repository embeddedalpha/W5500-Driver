/*
 * SPI.h
 *
 *  Created on: Nov 12, 2023
 *      Author: kunal
 */

#ifndef SPI_H_
#define SPI_H_

#include "main.h"
#include "GPIO.h"
#include "SPI_Defs.h"


typedef struct SPI_Config
{
	SPI_TypeDef *Port;
	uint8_t clock_pin;
	uint8_t mosi_pin;
	uint8_t miso_pin;

	GPIO_TypeDef *NSS_Port;
	uint8_t NSS_Pin;

	uint16_t mode;
	uint16_t crc;
	uint16_t data_format;
	uint16_t frame_format;
	uint16_t prescaler;
	uint16_t type;
	uint16_t clock_polarity;
	uint16_t clock_phase;
	uint16_t interrupt;
	uint16_t dma;
	uint32_t speed;
}SPI_Config;



int8_t SPI_Clock_Enable(SPI_Config *config);
int8_t SPI_Clock_Disable(SPI_Config *config);

int8_t SPI_Config_Reset(SPI_Config *config);

void SPI_Init(SPI_Config *config);
void SPI_Enable(SPI_Config *config);
void SPI_DeInit(SPI_Config *config);

uint16_t SPI_TRX_Byte(SPI_Config *config,uint16_t tx_data);
void SPI_TRX_Buffer(SPI_Config *config, uint16_t *tx_buffer,uint16_t *rx_buffer, uint16_t length);

void SPI_NSS_High(SPI_Config *config);
void SPI_NSS_Low(SPI_Config *config);


#endif /* SPI_H_ */

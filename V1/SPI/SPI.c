/*
 * SPI.c
 *
 *  Created on: Nov 12, 2023
 *      Author: kunal
 */

#include "SPI.h"

//DMA_Config xDMA_TX;
//DMA_Config xDMA_RX;

int8_t SPI_Clock_Enable(SPI_Config *config)
{
	int8_t retval = 0;
	if(config ->Port == SPI1)RCC -> APB2ENR |= RCC_APB2ENR_SPI1EN;
	if(config ->Port == SPI2)RCC -> APB1ENR |= RCC_APB1ENR_SPI2EN;
	if(config ->Port == SPI3)RCC -> APB1ENR |= RCC_APB1ENR_SPI3EN;
	else
		retval = -1;
	return retval;
}

int8_t SPI_Clock_Disable(SPI_Config *config)
{
	int8_t retval = 0;
	if(config ->Port == SPI1)RCC -> APB2ENR &= ~RCC_APB2ENR_SPI1EN;
	if(config ->Port == SPI2)RCC -> APB1ENR &= ~RCC_APB1ENR_SPI2EN;
	if(config ->Port == SPI3)RCC -> APB1ENR &= ~RCC_APB1ENR_SPI3EN;
	else
		retval = -1;
	return retval;
}


int8_t SPI_Config_Reset(SPI_Config *config)
{
	int8_t retval = 0;
	if(config ->Port == SPI1)RCC -> APB2RSTR |= RCC_APB2RSTR_SPI1RST;
	if(config ->Port == SPI2)RCC -> APB1RSTR |= RCC_APB1RSTR_SPI2RST;
	if(config ->Port == SPI3)RCC -> APB1RSTR |= RCC_APB1RSTR_SPI3RST;
	else
		retval = -1;

	config->NSS_Port = GPIOA;
	config->NSS_Pin = 4;
	config->clock_phase = SPI_Clock_Phase.High_1;
	config->clock_polarity = SPI_Clock_Polarity.High_1;
	config->mode = SPI_Mode.Full_Duplex_Master;
	config->crc = SPI_CRC.Disable;
	config->data_format = SPI_Data_Format.Bit8;
	config->frame_format = SPI_Frame_Format.MSB_First;
	config->dma = SPI_DMA.TX_DMA_Disable | SPI_DMA.RX_DMA_Disable;
	config->interrupt = SPI_Interrupt.Disable;
	config->type = SPI_Type.Master;

	return retval;
}


static void SPI_Pin(SPI_Config *config)
{
	if(config -> Port == SPI1)
	{
		if(config->mode == 0)
		{
			if(config->clock_pin == SPI1_CLK.PA5) GPIO_Pin_Init(GPIOA, 5, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.SPI_1);
			if(config->clock_pin == SPI1_CLK.PB3) GPIO_Pin_Init(GPIOB, 3, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.SPI_1);

			if(config->miso_pin == SPI1_MISO.PA6) GPIO_Pin_Init(GPIOA, 6, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.SPI_1);
			if(config->miso_pin == SPI1_MISO.PB4) GPIO_Pin_Init(GPIOB, 4, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.SPI_1);

			if(config->mosi_pin == SPI1_MOSI.PA7) GPIO_Pin_Init(GPIOA, 7, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.SPI_1);
			if(config->mosi_pin == SPI1_MOSI.PB5) GPIO_Pin_Init(GPIOB, 5, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.SPI_1);

			config->Port -> CR1 &= ~SPI_CR1_BIDIMODE;
		}
		else if(config->mode == 1)
		{
			if(config->clock_pin == SPI1_CLK.PA5) GPIO_Pin_Init(GPIOA, 5, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.SPI_1);
			if(config->clock_pin == SPI1_CLK.PB3) GPIO_Pin_Init(GPIOB, 3, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.SPI_1);

			if(config->mosi_pin == SPI1_MOSI.PA7) GPIO_Pin_Init(GPIOA, 7, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.SPI_1);
			if(config->mosi_pin == SPI1_MOSI.PB5) GPIO_Pin_Init(GPIOB, 5, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.SPI_1);

			config->Port -> CR1 |= SPI_CR1_BIDIMODE;
			config->Port -> CR1 |= SPI_CR1_BIDIOE;
		}
		else if(config->mode == 2)
		{
			if(config->clock_pin == SPI1_CLK.PA5) GPIO_Pin_Init(GPIOA, 5, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.SPI_1);
			if(config->clock_pin == SPI1_CLK.PB3) GPIO_Pin_Init(GPIOB, 3, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.SPI_1);

			if(config->miso_pin == SPI1_MISO.PA6) GPIO_Pin_Init(GPIOA, 6, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.SPI_1);
			if(config->miso_pin == SPI1_MISO.PB4) GPIO_Pin_Init(GPIOB, 4, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.SPI_1);

			config->Port -> CR1 |= SPI_CR1_BIDIMODE;
			config->Port -> CR1 &= ~SPI_CR1_BIDIOE;
		}
	}
/***************************************************************************************************************************************************************************************************************/
	else if(config -> Port == SPI2)
	{
		if(config->mode == 0)
		{
			if(config->clock_pin == SPI2_CLK.PB10) GPIO_Pin_Init(GPIOB, 10, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.SPI_2);
			if(config->clock_pin == SPI2_CLK.PB13) GPIO_Pin_Init(GPIOB, 13, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.SPI_2);

			if(config->miso_pin == SPI2_MISO.PB14) GPIO_Pin_Init(GPIOB, 14, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.SPI_2);
			if(config->miso_pin == SPI2_MISO.PC2) GPIO_Pin_Init(GPIOC, 2, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.SPI_2);

			if(config->mosi_pin == SPI2_MOSI.PB15) GPIO_Pin_Init(GPIOB, 15, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.SPI_2);
			if(config->mosi_pin == SPI2_MOSI.PC3) GPIO_Pin_Init(GPIOC, 3, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.SPI_2);

			config->Port -> CR1 &= ~SPI_CR1_BIDIMODE;
		}
		else if(config->mode == 1)
		{
			if(config->clock_pin == SPI2_CLK.PB10) GPIO_Pin_Init(GPIOB, 10, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.SPI_2);
			if(config->clock_pin == SPI2_CLK.PB13) GPIO_Pin_Init(GPIOB, 13, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.SPI_2);

			if(config->clock_pin == SPI2_CLK.PB10) GPIO_Pin_Init(GPIOB, 10, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.SPI_2);
			if(config->clock_pin == SPI2_CLK.PB13) GPIO_Pin_Init(GPIOB, 13, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.SPI_2);

			config->Port -> CR1 |= SPI_CR1_BIDIMODE;
			config->Port -> CR1 |= SPI_CR1_BIDIOE;
		}
		else if(config->mode == 2)
		{
			if(config->clock_pin == SPI2_CLK.PB10) GPIO_Pin_Init(GPIOB, 10, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.SPI_2);
			if(config->clock_pin == SPI2_CLK.PB13) GPIO_Pin_Init(GPIOB, 13, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.SPI_2);

			if(config->miso_pin == SPI2_MISO.PB14) GPIO_Pin_Init(GPIOB, 14, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.SPI_2);
			if(config->miso_pin == SPI2_MISO.PC2) GPIO_Pin_Init(GPIOC, 2, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.SPI_2);

			config->Port -> CR1 |= SPI_CR1_BIDIMODE;
			config->Port -> CR1 &= ~SPI_CR1_BIDIOE;
		}
	}
/***************************************************************************************************************************************************************************************************************/
	else if(config -> Port == SPI3)
		{

		if(config->mode == 0)
		{
			if(config->clock_pin == SPI3_CLK.PB3) GPIO_Pin_Init(GPIOB, 3, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.SPI_3);
			if(config->clock_pin == SPI3_CLK.PC10) GPIO_Pin_Init(GPIOC, 10, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.SPI_3);

			if(config->miso_pin == SPI3_MISO.PB4) GPIO_Pin_Init(GPIOB, 4, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.SPI_3);
			if(config->miso_pin == SPI3_MISO.PC11) GPIO_Pin_Init(GPIOC,11, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.SPI_3);

			if(config->mosi_pin == SPI3_MOSI.PB5) GPIO_Pin_Init(GPIOB, 5, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.SPI_3);
			if(config->mosi_pin == SPI3_MOSI.PC12) GPIO_Pin_Init(GPIOC, 12, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.SPI_3);

			config->Port -> CR1 &= ~SPI_CR1_BIDIMODE;
		}
		else if(config->mode == 1)
		{


			if(config->clock_pin == SPI3_CLK.PB3) GPIO_Pin_Init(GPIOB, 3, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.SPI_3);
			if(config->clock_pin == SPI3_CLK.PC10) GPIO_Pin_Init(GPIOC, 10, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.SPI_3);

			if(config->miso_pin == SPI3_MISO.PB4) GPIO_Pin_Init(GPIOB, 4, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.SPI_3);
			if(config->miso_pin == SPI3_MISO.PC11) GPIO_Pin_Init(GPIOC,11, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.SPI_3);

			config->Port -> CR1 |= SPI_CR1_BIDIMODE;
			config->Port -> CR1 |= SPI_CR1_BIDIOE;
		}
		else if(config->mode == 2)
		{
			if(config->clock_pin == SPI3_CLK.PB3) GPIO_Pin_Init(GPIOB, 3, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.SPI_3);
			if(config->clock_pin == SPI3_CLK.PC10) GPIO_Pin_Init(GPIOC, 10, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.SPI_3);

			if(config->mosi_pin == SPI3_MOSI.PB5) GPIO_Pin_Init(GPIOB, 5, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.SPI_3);
			if(config->mosi_pin == SPI3_MOSI.PC12) GPIO_Pin_Init(GPIOC, 12, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.SPI_3);

			config->Port -> CR1 |= SPI_CR1_BIDIMODE;
			config->Port -> CR1 &= ~SPI_CR1_BIDIOE;
		}
	}
}


void SPI_Init(SPI_Config *config)
{
	if(config->type == SPI_Type.Master){
		GPIO_Pin_Init(config->NSS_Port, config->NSS_Pin, MODE.General_Purpose_Output, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.Pull_Up, Alternate_Functions.None);
	}
	if(config->type == SPI_Type.Slave){
		GPIO_Pin_Init(config->NSS_Port, config->NSS_Pin, MODE.Input, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.Pull_Up, Alternate_Functions.None);
	}

	SPI_Clock_Enable(config);
	SPI_Pin(config);

	config->Port->CR1 |= config->clock_phase | config->clock_polarity |
					config->type | config->frame_format |
					config->data_format | config->crc ;
	config->Port->CR2 |= config->dma | config->interrupt;

//	if(config->Port == SPI1)config->speed = (SystemCoreClock/2)/(2*2^(config->prescaler));
//	else config->speed = (SystemCoreClock/4)/(2*2^(config->prescaler));

	config -> Port -> CR1 |= config->prescaler << SPI_CR1_BR_Pos;
	config->Port -> CR1 &= ~SPI_CR1_SSM ;
	config->Port -> CR2 |=  SPI_CR2_SSOE ;


//	if(config->dma == SPI_DMA.RX_DMA_Enable)
//	{
//		if(config->Port == SPI1)
//		{
//			xDMA_RX.stream = SPI_DMA_Stream.SPI1_RX;
//			xDMA_RX.controller = DMA2;
//			xDMA_RX.channel = SPI_DMA_Stream.SPI1_DMA_Channel;
//			xDMA_RX.circular_mode = DMA_Circular_Mode.Disable;
//			xDMA_RX.flow_control = DMA_Flow_Control.Peripheral_Control;
//			xDMA_RX.priority_level = DMA_Priority_Level.Very_high;
//			xDMA_RX.memory_data_size = DMA_Memory_Data_Size.byte;
//			xDMA_RX.peripheral_data_size = DMA_Peripheral_Data_Size.byte;
//			xDMA_RX.transfer_direction = DMA_Transfer_Direction.Peripheral_to_memory;
//			xDMA_RX.interrupts =  DMA_Interrupts.Disable;
//			DMA_Init(&xDMA_RX);
//		}
//		else if(config->Port == SPI2)
//		{
//			xDMA_RX.stream = SPI_DMA_Stream.SPI2_RX;
//			xDMA_RX.controller = DMA1;
//			xDMA_RX.channel = SPI_DMA_Stream.SPI2_DMA_Channel;
//			xDMA_RX.circular_mode = DMA_Circular_Mode.Disable;
//			xDMA_RX.flow_control = DMA_Flow_Control.Peripheral_Control;
//			xDMA_RX.priority_level = DMA_Priority_Level.Very_high;
//			xDMA_RX.memory_data_size = DMA_Memory_Data_Size.byte;
//			xDMA_RX.peripheral_data_size = DMA_Peripheral_Data_Size.byte;
//			xDMA_RX.transfer_direction = DMA_Transfer_Direction.Peripheral_to_memory;
//			xDMA_RX.interrupts =  DMA_Interrupts.Disable;
//			DMA_Init(&xDMA_RX);
//		}
//		else if(config->Port == SPI3)
//		{
//			xDMA_RX.stream = SPI_DMA_Stream.SPI3_RX;
//			xDMA_RX.controller = DMA1;
//			xDMA_RX.channel = SPI_DMA_Stream.SPI3_DMA_Channel;
//			xDMA_RX.circular_mode = DMA_Circular_Mode.Disable;
//			xDMA_RX.flow_control = DMA_Flow_Control.Peripheral_Control;
//			xDMA_RX.priority_level = DMA_Priority_Level.Very_high;
//			xDMA_RX.memory_data_size = DMA_Memory_Data_Size.byte;
//			xDMA_RX.peripheral_data_size = DMA_Peripheral_Data_Size.byte;
//			xDMA_RX.transfer_direction = DMA_Transfer_Direction.Peripheral_to_memory;
//			xDMA_RX.interrupts =  DMA_Interrupts.Disable;
//			DMA_Init(&xDMA_RX);
//		}
//	}
//	if(config->dma == SPI_DMA.TX_DMA_Enable){
//		if(config->Port == SPI1)
//		{
//			xDMA_TX.stream = SPI_DMA_Stream.SPI1_TX;
//			xDMA_TX.controller = DMA2;
//			xDMA_TX.channel = SPI_DMA_Stream.SPI1_DMA_Channel;
//			xDMA_TX.circular_mode = DMA_Circular_Mode.Disable;
//			xDMA_TX.flow_control = DMA_Flow_Control.Peripheral_Control;
//			xDMA_TX.priority_level = DMA_Priority_Level.Very_high;
//			xDMA_TX.memory_data_size = DMA_Memory_Data_Size.byte;
//			xDMA_TX.peripheral_data_size = DMA_Peripheral_Data_Size.byte;
//			xDMA_TX.transfer_direction = DMA_Transfer_Direction.Peripheral_to_memory;
//			xDMA_TX.interrupts =  DMA_Interrupts.Disable;
//			DMA_Init(&xDMA_TX);
//		}
//		else if(config->Port == SPI2)
//		{
//			xDMA_TX.stream = SPI_DMA_Stream.SPI2_TX;
//			xDMA_TX.controller = DMA1;
//			xDMA_TX.channel = SPI_DMA_Stream.SPI2_DMA_Channel;
//			xDMA_TX.circular_mode = DMA_Circular_Mode.Disable;
//			xDMA_TX.flow_control = DMA_Flow_Control.Peripheral_Control;
//			xDMA_TX.priority_level = DMA_Priority_Level.Very_high;
//			xDMA_TX.memory_data_size = DMA_Memory_Data_Size.byte;
//			xDMA_TX.peripheral_data_size = DMA_Peripheral_Data_Size.byte;
//			xDMA_TX.transfer_direction = DMA_Transfer_Direction.Peripheral_to_memory;
//			xDMA_TX.interrupts =  DMA_Interrupts.Disable;
//			DMA_Init(&xDMA_TX);
//		}
//		else if(config->Port == SPI3)
//		{
//			xDMA_TX.stream = SPI_DMA_Stream.SPI3_TX;
//			xDMA_TX.controller = DMA1;
//			xDMA_TX.channel = SPI_DMA_Stream.SPI3_DMA_Channel;
//			xDMA_TX.circular_mode = DMA_Circular_Mode.Disable;
//			xDMA_TX.flow_control = DMA_Flow_Control.Peripheral_Control;
//			xDMA_TX.priority_level = DMA_Priority_Level.Very_high;
//			xDMA_TX.memory_data_size = DMA_Memory_Data_Size.byte;
//			xDMA_TX.peripheral_data_size = DMA_Peripheral_Data_Size.byte;
//			xDMA_TX.transfer_direction = DMA_Transfer_Direction.Peripheral_to_memory;
//			xDMA_TX.interrupts =  DMA_Interrupts.Disable;
//			DMA_Init(&xDMA_TX);
//		}
//	}
}

void SPI_Enable(SPI_Config *config)
{
	config->Port -> CR1 |= SPI_CR1_SPE;
}



void SPI_DeInit(SPI_Config *config)
{
	if(config ->Port == SPI1)RCC -> APB2RSTR |= RCC_APB2RSTR_SPI1RST;
	if(config ->Port == SPI2)RCC -> APB1RSTR |= RCC_APB1RSTR_SPI2RST;
	if(config ->Port == SPI3)RCC -> APB1RSTR |= RCC_APB1RSTR_SPI3RST;
}


uint16_t SPI_TRX_Byte(SPI_Config *config,uint16_t tx_data)
{
	volatile uint16_t temp = 0;
	while (!(config->Port->SR & SPI_SR_TXE));
	config->Port -> DR = tx_data;
	while (!(config->Port->SR & SPI_SR_RXNE));
	temp = config->Port -> DR;
	while (!(config->Port->SR & SPI_SR_TXE));
	while (config->Port->SR & SPI_SR_BSY);
	return temp;
}


//void SPI_TRX_Buffer(SPI_Config *config, uint16_t *tx_buffer,uint16_t *rx_buffer, uint16_t tx_length, uint16_t rx_length)
//{
////	if(config->dma || SPI_DMA.TX_DMA_Enable){
////		xDMA_TX.memory_address = (uint32_t)&tx_buffer[0];
////		xDMA_TX.peripheral_address = (uint32_t)&(config->Port->DR);
////		xDMA_TX.buffer_length = tx_length;
////		DMA_Set_Target(&xDMA_TX);
////		DMA_Trigger(&xDMA_TX);
////	}
//
////	if(config->dma || SPI_DMA.RX_DMA_Enable){
////		xDMA_TX.memory_address = (uint32_t)&rx_buffer[0];
////		xDMA_TX.peripheral_address = (uint32_t)&(config->Port->DR);
////		xDMA_TX.buffer_length = rx_length;
////		DMA_Set_Target(&xDMA_RX);
////		DMA_Trigger(&xDMA_RX);
////	}
//
//	SPI_Enable(config);
//
//	if(config->dma && SPI_DMA.TX_DMA_Disable)
//	{
//		for(int i = 0; i < tx_length; i++)
//		{
//			rx_buffer[i] = SPI_TRX_Byte(config,tx_buffer[i]);
//		}
//	}
//
//}

void SPI_NSS_High(SPI_Config *config)
{
	GPIO_Pin_High(config->NSS_Port, config->NSS_Pin);
}

void SPI_NSS_Low(SPI_Config *config)
{
	GPIO_Pin_Low(config->NSS_Port, config->NSS_Pin);
}

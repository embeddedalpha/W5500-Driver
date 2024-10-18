/*
 * USART_Defs.h
 *
 *  Created on: Oct 18, 2023
 *      Author: kunal
 */

#ifndef USART_DEFS_H_
#define USART_DEFS_H_


#include "main.h"




static const struct Frame_Length
{
	uint8_t Bit_8;
	uint8_t Bit_9;
}Frame_Length = {0,1};


static const struct Interrupt_Type
{
	int Disable;
	int Parity_Enable;
	int Transmit_Empty_Enable;
	int Transmission_Complete_Enable;
	int Receiver_Empty_Enable;
	int IDLE_Enable;
	int CTS_Enable;
	int Error_Enable;
}Interrupt_Type = {0,1<<8,1<<7,1<<6,1<<5,1<<4,1<<10,1<<0,};

static const struct USART_Mode
{

	uint8_t Disable;
	uint8_t Asynchronous;
	uint8_t Synchronous;
	uint8_t Single_Wire_Half_Duplex;
	uint8_t IrDA;
	uint8_t LIN;
	uint8_t SmartCard;
	uint8_t SmartCard_Clock;
}USART_Mode = {0,1,2,3,4,5,6,7};


static const struct DMA_Enable
{
	uint8_t TX_Enable;
	uint8_t TX_Disable;
	uint8_t RX_Enable;
	uint8_t RX_Disable;
}DMA_Enable={0,1,2,3};

static const struct Hardware_Flow
{
	uint8_t Disable;
	uint8_t CTS_Enable;
	uint8_t RTS_Enable;
	uint8_t CTS_RTS_Enable;
}Hardware_Flow={0,1,2,3};

static const struct Stop_Bits
{
	uint16_t Bit_1;
	uint16_t Bit_0_5;
	uint16_t Bit_2;
	uint16_t Bit_1_5;
}Stop_Bits={0,1<<12,2<<12,3<<12};




static const struct USART1_TX_Pin
{
	uint8_t PA9;
	uint8_t PB6;
}USART1_TX_Pin = {9,6};

static const struct USART1_RX_Pin
{
	uint8_t PA10;
	uint8_t PB7;
}USART1_RX_Pin = {10,7};

static const struct USART1_CLK_Pin
{
	uint8_t PA8;
}USART1_CLK_Pin = {8};

static const struct USART1_CTS_Pin
{
	uint8_t PA11;
}USART1_CTS_Pin = {11};

static const struct USART1_RTS_Pin
{
	uint8_t PA12;
}USART1_RTS_Pin = {12};


static const struct USART2_TX_Pin
{
	uint8_t PA2;
	uint8_t PD5;
}USART2_TX_Pin = {2,5};

static const struct USART2_RX_Pin
{
	uint8_t PA3;
	uint8_t PD6;
}USART2_RX_Pin = {3,6};

static const struct USART2_CLK_Pin
{
	uint8_t PA4;
	uint8_t PD7;
}USART2_CLK_Pin = {4,7};

static const struct USART2_CTS_Pin
{
	uint8_t PA0;
	uint8_t PD3;
}USART2_CTS_Pin = {0,3};

static const struct USART2_RTS_Pin
{
	uint8_t PA1;
	uint8_t PD4;
}USART2_RTS_Pin = {1,4};


static const struct USART3_TX_Pin
{
	uint8_t PB11;
	uint8_t PD8;
	uint8_t PC10;
}USART3_TX_Pin = {11,8,10};

static const struct USART3_RX_Pin
{
	uint8_t PB10;
	uint8_t PD0;
	uint8_t PC11;
}USART3_RX_Pin = {10,0,11};

static const struct USART3_CLK_Pin
{
	uint8_t PB12;
	uint8_t PD10;
}USART3_CLK_Pin = {12,10};

static const struct USART3_CTS_Pin
{
	uint8_t PB13;
	uint8_t PD11;
}USART3_CTS_Pin = {0,3};

static const struct USART3_RTS_Pin
{
	uint8_t PB14;
	uint8_t PD12;
}USART3_RTS_Pin = {1,4};


static const struct UART4_TX_Pin
{
	uint8_t PA0;
	uint8_t PC10;
}UART4_TX_Pin = {0,10};

static const struct UART4_RX_Pin
{
	uint8_t PA1;
	uint8_t PC11;
}UART4_RX_Pin = {1,11};


static const struct UART5_TX_Pin
{
	uint8_t PD2;
}UART5_TX_Pin = {2};

static const struct UART5_RX_Pin
{
	uint8_t PC12;
}UART5_RX_Pin = {12};


static const struct USART6_TX_Pin
{
	uint8_t PC6;
}USART6_TX_Pin = {6};

static const struct USART6_RX_Pin
{
	uint8_t PC7;
}USART6_RX_Pin = {7};

static const struct USART6_CLK_Pin
{
	uint8_t PC8;
}USART6_CLK_Pin = {8};

static const struct Low_Power_USART
{
	uint8_t Enable;
	uint8_t Disable;
}Low_Power_USART = {1,0};

static const struct USART_Parity
{
	uint16_t Enable;
	uint16_t Disable;
	uint16_t Even;
	uint16_t Odd;
}USART_Parity = {1 << 10, 0 << 0, 1 << 9, 0 << 9};




#endif /* USART_DEFS_H_ */

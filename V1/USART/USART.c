/*
 * USART.c
 *
 *  Created on: Oct 18, 2023
 *      Author: kunal
 */


#include "main.h"
#include "USART.h"



void USART_Config_Reset(USART_Config *config)
{
	config->mode = USART_Mode.Disable;
	config->hardware_flow = Hardware_Flow.Disable;
	config->low_power_uart = Low_Power_USART.Disable;
	config->baudrate = 9600;
	config->dma_enable = DMA_Enable.RX_Disable | DMA_Enable.TX_Disable;
	config->interrupt = Interrupt_Type.Disable;
}


int8_t USART_Clock_Enable(USART_Config *config)
{
	if(config->Port == USART1)
	{
		if(config->low_power_uart == Low_Power_USART.Enable) RCC -> APB2LPENR |= RCC_APB2LPENR_USART1LPEN;
		else RCC -> APB2ENR |= RCC_APB2ENR_USART1EN;
	}
	else if(config->Port == USART2)
	{
		if(config->low_power_uart == Low_Power_USART.Enable) RCC -> APB1LPENR |= RCC_APB1LPENR_USART2LPEN;
		else RCC -> APB1ENR |= RCC_APB1ENR_USART2EN;
	}
	else if(config->Port == USART3)
	{
		if(config->low_power_uart == Low_Power_USART.Enable) RCC -> APB1LPENR |= RCC_APB1LPENR_USART3LPEN;
		else RCC -> APB1ENR |= RCC_APB1ENR_USART3EN;
	}
	else if(config->Port == UART4)
	{
		if(config->low_power_uart == Low_Power_USART.Enable) return -1;
		else RCC -> APB1ENR |= RCC_APB1ENR_UART4EN;
	}
	else if(config->Port == UART5)
	{
		if(config->low_power_uart == Low_Power_USART.Enable) return -1;
		else RCC -> APB1ENR |= RCC_APB1ENR_UART5EN;
	}
	else if(config->Port == USART6)
	{
		if(config->low_power_uart == Low_Power_USART.Enable) RCC -> APB2LPENR |= RCC_APB2LPENR_USART6LPEN;
		else RCC -> APB2ENR |= RCC_APB2ENR_USART6EN;
	}
	else
	{
		return -1;
	}
	return 1;
}


int8_t USART_Clock_Disable(USART_Config *config)
{
	if(config->Port == USART1)
	{
		if(config->low_power_uart == Low_Power_USART.Disable) RCC -> APB2LPENR &= ~RCC_APB2LPENR_USART1LPEN;
		else RCC -> APB2ENR &= ~RCC_APB2ENR_USART1EN;
	}
	else if(config->Port == USART2)
	{
		if(config->low_power_uart == Low_Power_USART.Disable) RCC -> APB1LPENR &= ~RCC_APB1LPENR_USART2LPEN;
		else RCC -> APB1ENR &= ~RCC_APB1ENR_USART2EN;
	}
	else if(config->Port == USART3)
	{
		if(config->low_power_uart == Low_Power_USART.Disable) RCC -> APB1LPENR &= ~RCC_APB1LPENR_USART3LPEN;
		else RCC -> APB1ENR &= ~RCC_APB1ENR_USART3EN;
	}
	else if(config->Port == UART4)
	{
		if(config->low_power_uart == Low_Power_USART.Disable) return -1;
		else RCC -> APB1ENR &= ~RCC_APB1ENR_UART4EN;
	}
	else if(config->Port == UART5)
	{
		if(config->low_power_uart == Low_Power_USART.Disable) return -1;
		else RCC -> APB1ENR &= ~RCC_APB1ENR_UART5EN;
	}
	else if(config->Port == USART6)
	{
		if(config->low_power_uart == Low_Power_USART.Disable) RCC -> APB2LPENR &= ~RCC_APB2LPENR_USART6LPEN;
		else RCC -> APB2ENR &= ~RCC_APB2ENR_USART6EN;
	}
	else
	{
		return -1;
	}
	return 1;
}

static void PIN_Setup(USART_Config *config)
{
	if(config->Port == USART1)
	{
		if((config->mode == USART_Mode.Asynchronous) ||
		   (config->mode == USART_Mode.Synchronous) ||
		   (config->mode == USART_Mode.IrDA) ||
		   (config->mode == USART_Mode.LIN) )
		{
			if(config->TX_Pin == USART1_TX_Pin.PA9)GPIO_Pin_Init(GPIOA, USART1_TX_Pin.PA9, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.USART_1);
			else if(config->TX_Pin == USART1_TX_Pin.PB6)GPIO_Pin_Init(GPIOB, USART1_TX_Pin.PB6, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.USART_1);

			if(config->RX_Pin == USART1_RX_Pin.PA10){
				GPIO_Pin_Init(GPIOA, USART1_RX_Pin.PA10, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.USART_1);
			}
			else if(config->RX_Pin == USART1_RX_Pin.PB7)GPIO_Pin_Init(GPIOB, USART1_RX_Pin.PB7, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.USART_1);

			if((config->mode == USART_Mode.Synchronous))if(config->CLK_Pin == USART1_CLK_Pin.PA8)GPIO_Pin_Init(GPIOA, USART1_CLK_Pin.PA8, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.USART_1);

			if(config->hardware_flow != Hardware_Flow.Disable)
			{
				if(config->hardware_flow == Hardware_Flow.CTS_Enable)GPIO_Pin_Init(GPIOA, USART1_CTS_Pin.PA11, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.USART_1);
				if(config->hardware_flow == Hardware_Flow.RTS_Enable)GPIO_Pin_Init(GPIOA, USART1_RTS_Pin.PA12, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.USART_1);
				if(config->hardware_flow == Hardware_Flow.CTS_RTS_Enable)
				{
					GPIO_Pin_Init(GPIOA, USART1_CTS_Pin.PA11, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.USART_1);
					GPIO_Pin_Init(GPIOA, USART1_RTS_Pin.PA12, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.USART_1);
				}
		    }
		}
		else if((config->mode == USART_Mode.SmartCard) ||
		   (config->mode == USART_Mode.SmartCard_Clock) ||
		   (config->mode == USART_Mode.Single_Wire_Half_Duplex) )
		{
			if(config->TX_Pin == USART1_TX_Pin.PA9)GPIO_Pin_Init(GPIOA, USART1_TX_Pin.PA9, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.USART_1);
			if((config->mode == USART_Mode.SmartCard_Clock))GPIO_Pin_Init(GPIOA, USART1_CLK_Pin.PA8, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.USART_1);

		}
	}

	else if(config->Port == USART2)
	{
		if((config->mode == USART_Mode.Asynchronous) ||
		   (config->mode == USART_Mode.Synchronous) ||
		   (config->mode == USART_Mode.IrDA) ||
		   (config->mode == USART_Mode.LIN) )
		{
			if(config->TX_Pin == USART2_TX_Pin.PA2)GPIO_Pin_Init(GPIOA, USART2_TX_Pin.PA2, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.USART_2);
			else if(config->TX_Pin == USART2_TX_Pin.PD5)GPIO_Pin_Init(GPIOD, USART2_TX_Pin.PD5, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.USART_2);

			if(config->RX_Pin == USART2_RX_Pin.PA3)GPIO_Pin_Init(GPIOA, USART2_RX_Pin.PA3, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.USART_2);
			else if(config->RX_Pin == USART2_RX_Pin.PD6)GPIO_Pin_Init(GPIOD, USART2_RX_Pin.PD6, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.USART_2);

			if((config->mode == USART_Mode.Synchronous)){
				if(config->CLK_Pin == USART2_CLK_Pin.PA4)GPIO_Pin_Init(GPIOA, USART2_CLK_Pin.PA4, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.USART_2);
				else if(config->CLK_Pin == USART2_CLK_Pin.PD7)GPIO_Pin_Init(GPIOA, USART2_CLK_Pin.PD7, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.USART_2);
			}


			if((config->hardware_flow != Hardware_Flow.Disable) || (config->hardware_flow == Hardware_Flow.CTS_RTS_Enable))
			{
				if(config->hardware_flow == Hardware_Flow.CTS_Enable)
				{
					if(config->CLK_Pin == USART2_CTS_Pin.PA0)
					{
						GPIO_Pin_Init(GPIOA, USART2_CTS_Pin.PA0, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.USART_2);
					}
					else if(config->CLK_Pin == USART2_CTS_Pin.PD3)
					{
						GPIO_Pin_Init(GPIOD, USART2_CTS_Pin.PD3, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.USART_2);
					}
				}
				if((config->hardware_flow == Hardware_Flow.RTS_Enable) || (config->hardware_flow == Hardware_Flow.CTS_RTS_Enable))
				{
					if(config->CLK_Pin == USART2_RTS_Pin.PA1)
					{
						GPIO_Pin_Init(GPIOA, USART2_RTS_Pin.PA1, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.USART_2);
					}
					else if(config->CLK_Pin == USART2_RTS_Pin.PD4)
					{
						GPIO_Pin_Init(GPIOD, USART2_RTS_Pin.PD4, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.USART_2);
					}
				}

		    }
		}
		else if((config->mode == USART_Mode.SmartCard) ||
		   (config->mode == USART_Mode.SmartCard_Clock) ||
		   (config->mode == USART_Mode.Single_Wire_Half_Duplex))
		{
			if(config->TX_Pin == USART2_TX_Pin.PA2)
			{
				GPIO_Pin_Init(GPIOA, USART2_TX_Pin.PA2, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.USART_2);
			}
			else if(config->TX_Pin == USART2_TX_Pin.PD5)
			{
				GPIO_Pin_Init(GPIOD, USART2_TX_Pin.PD5, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.USART_2);
			}

			if((config->mode == USART_Mode.SmartCard_Clock))
			{
				if(config->CLK_Pin == USART2_CLK_Pin.PA4)
				{
					GPIO_Pin_Init(GPIOA, USART2_CLK_Pin.PA4, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.USART_2);
				}
				else if(config->CLK_Pin == USART2_CLK_Pin.PD7)
				{
					GPIO_Pin_Init(GPIOA, USART2_CLK_Pin.PD7, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.USART_2);
				}
			}
		}
	}

	else if(config->Port == USART3)
	{
		if((config->mode == USART_Mode.Asynchronous) ||
		   (config->mode == USART_Mode.Synchronous) ||
		   (config->mode == USART_Mode.IrDA) ||
		   (config->mode == USART_Mode.LIN) )
		{
			if(config->TX_Pin == USART3_TX_Pin.PB11)GPIO_Pin_Init(GPIOA, USART3_TX_Pin.PB11, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.USART_3);
			else if(config->TX_Pin == USART3_TX_Pin.PC10)GPIO_Pin_Init(GPIOB, USART3_TX_Pin.PC10, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.USART_3);
			else if(config->TX_Pin == USART3_TX_Pin.PD8)GPIO_Pin_Init(GPIOB, USART3_TX_Pin.PD8, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.USART_3);

			if(config->RX_Pin == USART3_RX_Pin.PB10)GPIO_Pin_Init(GPIOA, USART3_RX_Pin.PB10, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.USART_3);
			else if(config->RX_Pin == USART3_RX_Pin.PC11)GPIO_Pin_Init(GPIOB, USART3_RX_Pin.PC11, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.USART_3);
			else if(config->TX_Pin == USART3_TX_Pin.PD8)GPIO_Pin_Init(GPIOB, USART3_TX_Pin.PD8, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.USART_3);


			if((config->mode == USART_Mode.Synchronous))
			{
				if(config->CLK_Pin == USART3_CLK_Pin.PB12)GPIO_Pin_Init(GPIOB, USART3_CLK_Pin.PB12, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.USART_3);
				else if(config->CLK_Pin == USART3_CLK_Pin.PD10)GPIO_Pin_Init(GPIOD, USART3_CLK_Pin.PD10, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.USART_3);

			}

			if(config->hardware_flow != Hardware_Flow.Disable)
			{
				if((config->hardware_flow == Hardware_Flow.CTS_Enable) || (config->hardware_flow == Hardware_Flow.CTS_RTS_Enable))
				{
					if(config->CLK_Pin == USART3_CTS_Pin.PB13)GPIO_Pin_Init(GPIOB, USART3_CTS_Pin.PB13, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.USART_3);
					else if(config->CLK_Pin == USART3_CTS_Pin.PD11)GPIO_Pin_Init(GPIOD, USART3_CTS_Pin.PD11, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.USART_3);
				}
				if((config->hardware_flow == Hardware_Flow.RTS_Enable) || (config->hardware_flow == Hardware_Flow.CTS_RTS_Enable))
				{
					if(config->CLK_Pin == USART3_RTS_Pin.PB14)GPIO_Pin_Init(GPIOB, USART3_RTS_Pin.PB14, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.USART_3);
					else if(config->CLK_Pin == USART3_RTS_Pin.PD12)GPIO_Pin_Init(GPIOD, USART3_RTS_Pin.PD12, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.USART_3);
				}
		    }
		}
		else if((config->mode == USART_Mode.SmartCard) ||
		   (config->mode == USART_Mode.SmartCard_Clock) ||
		   (config->mode == USART_Mode.Single_Wire_Half_Duplex) )
		{
			if(config->TX_Pin == USART3_TX_Pin.PB11)GPIO_Pin_Init(GPIOA, USART3_TX_Pin.PB11, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.USART_3);
			else if(config->TX_Pin == USART3_TX_Pin.PC10)GPIO_Pin_Init(GPIOB, USART3_TX_Pin.PC10, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.USART_3);
			else if(config->TX_Pin == USART3_TX_Pin.PD8)GPIO_Pin_Init(GPIOB, USART3_TX_Pin.PD8, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.USART_3);
			if(config->CLK_Pin == USART3_CLK_Pin.PB12)GPIO_Pin_Init(GPIOB, USART3_CLK_Pin.PB12, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.USART_3);
			else if(config->CLK_Pin == USART3_CLK_Pin.PD10)GPIO_Pin_Init(GPIOD, USART3_CLK_Pin.PD10, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.USART_3);

		}
	}
//	else if(config->Port == UART4)
//	{
//		if((config->mode == USART_Mode.Asynchronous) ||
//		   (config->mode == USART_Mode.IrDA) ||
//		   (config->mode == USART_Mode.LIN) )
//		{
//			if(config->TX_Pin == UART4_TX_Pin.PA0)GPIO_Pin_Init(GPIOA, UART4_TX_Pin.PA0, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.USART_4);
//			else if(config->TX_Pin == UART4_TX_Pin.PC10)GPIO_Pin_Init(GPIOC, UART4_TX_Pin.PC10, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.USART_4);
//
//			if(config->RX_Pin == UART4_RX_Pin.PA1)GPIO_Pin_Init(GPIOA, UART4_RX_Pin.PA1, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.USART_4);
//			else if(config->RX_Pin == UART4_RX_Pin.PC11)GPIO_Pin_Init(GPIOC, UART4_RX_Pin.PC11, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.USART_4);
//		}
//		else if((config->mode == USART_Mode.SmartCard) ||
//		   (config->mode == USART_Mode.SmartCard_Clock) ||
//		   (config->mode == USART_Mode.Single_Wire_Half_Duplex) )
//		{
//			if(config->TX_Pin == UART4_TX_Pin.PA0)GPIO_Pin_Init(GPIOA, UART4_TX_Pin.PA0, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.USART_4);
//			if((config->mode == USART_Mode.SmartCard_Clock))GPIO_Pin_Init(GPIOA, USART3_CLK_Pin.PB12, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.USART_4);
//
//		}
//	}
//	else if(config->Port == USART6)
//	{
//		if((config->mode == USART_Mode.Asynchronous) ||
//		   (config->mode == USART_Mode.Synchronous) ||
//		   (config->mode == USART_Mode.IrDA) ||
//		   (config->mode == USART_Mode.LIN) )
//		{
//			if(config->TX_Pin == USART6_TX_Pin.PC6)GPIO_Pin_Init(GPIOC, USART6_TX_Pin.PC6, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.USART_6);
//			if(config->RX_Pin == USART6_RX_Pin.PC7)GPIO_Pin_Init(GPIOC, USART6_RX_Pin.PC7, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.USART_6);
//			if(config->CLK_Pin == USART6_CLK_Pin.PC8)GPIO_Pin_Init(GPIOC, USART6_CLK_Pin.PC8, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.USART_6);
//		}
//		else if((config->mode == USART_Mode.SmartCard) ||
//		   (config->mode == USART_Mode.SmartCard_Clock) ||
//		   (config->mode == USART_Mode.Single_Wire_Half_Duplex) )
//		{
//			if(config->TX_Pin == USART6_TX_Pin.PC6)GPIO_Pin_Init(GPIOA, USART6_TX_Pin.PC6, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.USART_6);
//			if((config->mode == USART_Mode.SmartCard_Clock))GPIO_Pin_Init(GPIOA, USART6_CLK_Pin.PC8, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.USART_6);
//
//		}
//	}


}

int8_t USART_Init(USART_Config *config)
{
	USART_Clock_Enable(config);
	PIN_Setup(config);

	config->Port->BRR = (int)(84000000 / (16 * config->baudrate)) << 4;
	config->Port->CR1 |= config->parity; //Parity
	config->Port->CR1 |= config->interrupt; //interrupt
	config->Port->CR2 |= config->stop_bits;
	config->Port ->CR1 |= USART_CR1_UE;
	config->Port ->CR1 |= USART_CR1_TE ;
	config->Port ->CR1 |= USART_CR1_RE | USART_CR1_RXNEIE;
	config->Port ->CR1 |= USART_CR1_UE;

//	if(config->mode == USART_Mode.Single_Wire_Half_Duplex) config -> Port -> CR3 |= USART_CR3_HDSEL;
//	if(config->mode == USART_Mode.LIN) config -> Port -> CR2 |= USART_CR2_LINEN;

	return 1;
}

void USART_TX_Buffer(USART_Config *config, uint8_t *tx_buffer, uint16_t length)
{
	if(config->dma_enable |= DMA_Enable.TX_Enable)
	{ //Won't take much time
		//Implement DMA
	}
	else
	{ //Will Take more time
		for(int i = 0; i <= length; i++)
		{
			config->Port->DR = tx_buffer[i];
			while(!(config->Port->SR & USART_SR_TXE));
		}
	}

}

void USART_RX_Buffer(USART_Config *config, uint8_t *rx_buffer, uint16_t length)
{
	if(config->dma_enable |= DMA_Enable.RX_Enable)
	{ //Won't take much time
		//Implement DMA
	}
	else
	{ //Will Take more time
		for(int i = 0; i <= length; i++)
		{
			rx_buffer[i] = config->Port->DR ;
			while(!(config->Port->SR & USART_SR_RXNE));
		}
	}

}

void USART_TX_Single_Byte(USART_Config *config, uint8_t data)
{
	config->Port->DR = data;
	while(!(config->Port->SR & USART_SR_TXE));
}

uint16_t USART_RX_Single_Byte(USART_Config *config)
{
	uint8_t data;
	while(!(config->Port->SR & USART_SR_RXNE));
	data = config->Port->DR ;
	return data;
}

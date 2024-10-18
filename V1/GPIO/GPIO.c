/*
 * GPIO.c
 *
 *  Created on: Nov 2, 2021
 *      Author: Kunal
 */


#include "GPIO.h"



void GPIO_Interrupt_Setup(int pin, int edge_select, uint32_t priority)
{
	EXTI ->IMR |= 1 << pin;
	switch (edge_select) {
		case 0:
			EXTI ->RTSR |= 1 << pin;
			break;
		case 1:
			EXTI ->FTSR |= 1 << pin;
			break;
		case 2:
			EXTI ->RTSR |= 1 << pin;
			EXTI ->FTSR |= 1 << pin;
			break;
	}

	if(pin == 0)
	{
		NVIC_SetPriority(EXTI0_IRQn,priority);
		NVIC_EnableIRQ(EXTI0_IRQn);
	}
	else if(pin == 1)
	{
		NVIC_SetPriority(EXTI1_IRQn,priority);
		NVIC_EnableIRQ(EXTI1_IRQn);
	}
	else if(pin == 2)
	{
		NVIC_SetPriority(EXTI2_IRQn,priority);
		NVIC_EnableIRQ(EXTI2_IRQn);
	}
	else if(pin == 3)
	{
		NVIC_SetPriority(EXTI3_IRQn,priority);
		NVIC_EnableIRQ(EXTI3_IRQn);
	}
	else if(pin == 4)
	{
		NVIC_SetPriority(EXTI4_IRQn,priority);
		NVIC_EnableIRQ(EXTI4_IRQn);
	}
	else if(pin >= 5 || pin <= 9)
	{
		NVIC_SetPriority(EXTI9_5_IRQn,priority);
		NVIC_EnableIRQ(EXTI9_5_IRQn);
	}
	else if(pin >= 10 || pin <= 15)
	{
		NVIC_SetPriority(EXTI15_10_IRQn,priority);
		NVIC_EnableIRQ(EXTI15_10_IRQn);
	}



}

void GPIO_Pin_High(GPIO_TypeDef *Port, int pin)
{
	Port -> ODR = 1 << pin;
}


void GPIO_Pin_Low(GPIO_TypeDef *Port, int pin)
{
	Port -> ODR &= ~(1 << pin);
}


int GPIO_Clock_Disable(GPIO_TypeDef *PORT)
{
	if(PORT == GPIOA)
	{
		RCC -> AHB1ENR   &= ~RCC_AHB1ENR_GPIOAEN;
	} else 	if(PORT == GPIOB)
	{
		RCC -> AHB1ENR   &= ~RCC_AHB1ENR_GPIOBEN;
	}else 	if(PORT == GPIOC)
	{
		RCC -> AHB1ENR   &= ~RCC_AHB1ENR_GPIOCEN;
	}else 	if(PORT == GPIOD)
	{
		RCC -> AHB1ENR   &= ~RCC_AHB1ENR_GPIODEN;
	}else 	if(PORT == GPIOE)
	{
		RCC -> AHB1ENR   &= ~RCC_AHB1ENR_GPIOEEN;
	}else 	if(PORT == GPIOH)
	{
		RCC -> AHB1ENR   &= ~RCC_AHB1ENR_GPIOHEN;
	}else
	{
		return -1;
	}

	return 1;
}

int GPIO_Clock_Enable(GPIO_TypeDef *PORT)
{
	if(PORT == GPIOA)
	{
		RCC -> AHB1ENR   |=  RCC_AHB1ENR_GPIOAEN;
	} else 	if(PORT == GPIOB)
	{
		RCC -> AHB1ENR   |=  RCC_AHB1ENR_GPIOBEN;
	}else 	if(PORT == GPIOC)
	{
		RCC -> AHB1ENR   |=  RCC_AHB1ENR_GPIOCEN;
	}else 	if(PORT == GPIOD)
	{
		RCC -> AHB1ENR   |=  RCC_AHB1ENR_GPIODEN;
	}else 	if(PORT == GPIOE)
	{
		RCC -> AHB1ENR   |=  RCC_AHB1ENR_GPIOEEN;
	}else 	if(PORT == GPIOH)
	{
		RCC -> AHB1ENR   |=  RCC_AHB1ENR_GPIOHEN;
	}else
	{
		return -1;
	}

	return 1;
}


void GPIO_Pin_Init(GPIO_TypeDef *Port, uint8_t pin, uint8_t mode, uint8_t output_type, uint8_t speed, uint8_t pull, uint8_t alternate_function)
{
	GPIO_Clock_Enable(Port);
	Port -> MODER &= ~(3 << (pin*2));
	Port -> MODER |= mode << (pin*2);
	Port -> OTYPER |= output_type << pin;
	Port -> OSPEEDR |= speed << (pin*2);
	Port -> PUPDR |= pull << (pin*2);
	if(pin < 8) Port -> AFR[0] |= alternate_function << (pin*4);
	else Port -> AFR[1] |= alternate_function << ((pin-8)*4);
}



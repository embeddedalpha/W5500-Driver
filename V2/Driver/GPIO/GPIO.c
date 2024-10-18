/**
 * @file GPIO.c
 * @brief GPIO Driver Implementation for STM32F407VGT6
 *
 * This file provides the implementation of the GPIO driver for the STM32F407VGT6 microcontroller.
 * It includes functions to initialize GPIO, handle GPIO interrupts.
 *
 * @version 1.0
 * @date 2024-08-21
 *
 * @author Your Name
 * @copyright Copyright (c) 2024
 */

#include "GPIO.h"



/**
 * @brief  Configures the interrupt for a specific pin.
 * @param  pin: Pin number to configure (0-15).
 * @param  edge_select: Interrupt edge selection (0: rising, 1: falling, 2: both).
 * @param  priority: Interrupt priority.
 */
void GPIO_Interrupt_Setup(int pin, int edge_select, uint32_t priority)
{
	// Enable interrupt mask register for the pin
	EXTI ->IMR |= 1 << pin;

	// Configure edge selection
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

	// Configure NVIC based on pin number
    // Configure NVIC based on pin number
    IRQn_Type irq;
    if (pin <= 4) {
        irq = (IRQn_Type)(EXTI0_IRQn + pin);
    } else if (pin <= 9) {
        irq = EXTI9_5_IRQn;
    } else {
        irq = EXTI15_10_IRQn;
    }
    NVIC_SetPriority(irq, priority);
    NVIC_EnableIRQ(irq);
}






/**
 * @brief  Disables the clock for a specific GPIO port.
 * @param  PORT: Pointer to GPIO port base address.
 * @retval 0 on success, -1 on failure.
 */
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

/**
 * @brief  Enables the clock for a specific GPIO port.
 * @param  PORT: Pointer to GPIO port base address.
 * @retval 0 on success, -1 on failure.
 */
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

/**
 * @brief  Initializes a specific pin with given parameters.
 * @param  Port: Pointer to GPIO port base address.
 * @param  pin: Pin number to initialize (0-15).
 * @param  mode: Pin mode (input, output, alternate function, analog).
 * @param  output_type: Output type (push-pull, open-drain).
 * @param  speed: Speed level (low, medium, high, very high).
 * @param  pull: Pull-up/pull-down configuration (none, pull-up, pull-down).
 * @param  alternate_function: Alternate function selection (0-15).
 */
void GPIO_Pin_Init(GPIO_TypeDef *Port, uint8_t pin, uint8_t mode, uint8_t output_type, uint8_t speed, uint8_t pull, uint8_t alternate_function)
{
	GPIO_Clock_Enable(Port);
	Port -> MODER |= mode << (pin*2);

	if(output_type != GPIO_Configuration.Output_Type.None) Port -> OTYPER |= output_type << pin;
	if(speed != GPIO_Configuration.Speed.None) Port -> OSPEEDR |= speed << (pin*2);
	if(pull != GPIO_Configuration.Pull.None) Port -> PUPDR |= pull << (pin*2);
	if(pin < 8) Port -> AFR[0] |= alternate_function << (pin*4);
	else Port -> AFR[1] |= alternate_function << ((pin-8)*4);
}



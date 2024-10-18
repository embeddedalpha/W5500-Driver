/*
 * GPIO.h
 *
 *  Created on: Nov 2, 2021
 *      Author: Kunal
 */

#ifndef GPIO_GPIO_H_
#define GPIO_GPIO_H_

#include "main.h"
#include "GPIO_Defs.h"


void GPIO_Pin_Init(GPIO_TypeDef *Port, uint8_t pin, uint8_t mode, uint8_t output_type, uint8_t speed, uint8_t pull, uint8_t alternate_function);
void GPIO_Interrupt_Setup(int pin, int edge_select, uint32_t priority);
void GPIO_Pin_High(GPIO_TypeDef *Port, int pin);
void GPIO_Pin_Low(GPIO_TypeDef *Port, int pin);
int GPIO_Clock_Disable(GPIO_TypeDef *PORT);
int GPIO_Clock_Enable(GPIO_TypeDef *PORT);
#endif /* GPIO_GPIO_H_ */










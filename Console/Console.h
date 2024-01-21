/*
 * Console.h
 *
 *  Created on: Dec 19, 2023
 *      Author: kunal
 */

#ifndef CONSOLE_H_
#define CONSOLE_H_

#include "main.h"
#include "GPIO.h"
#include "USART.h"



void Console_Init(USART_TypeDef *port,int baudrate);
 void printConsole(char *msg, ...);
 char readConsole(void);
 int readConsole_int(void);


#endif /* CONSOLE_H_ */

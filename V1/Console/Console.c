/*
 * Console.c
 *
 *  Created on: Dec 19, 2023
 *      Author: kunal
 */


#include "Console.h"

USART_Config serial;


 void Console_Init(USART_TypeDef *port,int baudrate)
{
	 USART_Config_Reset(&serial);
	 serial.Port = USART1;
	 serial.baudrate = baudrate;
	 serial.mode = USART_Mode.Asynchronous;
	 serial.stop_bits = Stop_Bits.Bit_1;
	 serial.TX_Pin = USART1_TX_Pin.PA9;
	 serial.RX_Pin = USART1_RX_Pin.PA10;
	 USART_Init(&serial);
}

 void printConsole(char *msg, ...)
{

char buff[10000];
//	#ifdef DEBUG_UART

	va_list args;
	va_start(args, msg);
	vsprintf(buff, msg, args);

	for(int i = 0; i<= strlen(buff)-1; i++)
	{
		serial.Port -> DR = buff[i];
		while (!(serial.Port -> SR & USART_SR_TXE));
	}
}

char readConsole(void)
{
	char retval = 0;
	while(!(serial.Port -> SR & USART_SR_RXNE));
	retval = serial.Port-> DR;

	return retval;
}

int readConsole_int(void)
{
	int retval = 0;
	while(!(serial.Port -> SR & USART_SR_RXNE));
	retval = serial.Port-> DR;

	return retval;
}


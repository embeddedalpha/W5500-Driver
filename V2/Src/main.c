/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
#include "main.h"
#include "IPv4.h"
#include "Logs/Logs.h"
#include "W5500_Middleware/W5500_MWL.h"

W5500_Config ip;

#define MODBUS_IP 0
#define BACNET_IP 1

int main(void)
{
	MCU_Clock_Setup();
	Delay_Config();






	for(;;)
	{

	}
}
